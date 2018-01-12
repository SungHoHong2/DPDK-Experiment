#include "core/reactor.hh"
#include "core/app-template.hh"
#include "core/temporary_buffer.hh"
#include "core/distributed.hh"
#include <vector>
#include <iostream>
#include <core/app-template.hh>
#include "net/api.hh"

#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

bool g_is_debug = false;
#define DEBUG_PRINT(msg) do { if (g_is_debug) std::cout << msg << std::endl; } while (0)

struct rp_alias
{
   ipv4_addr m_external_addr;
   ipv4_addr m_internal_addr;

   ipv4_addr m_web_server_addr;

    rp_alias(ipv4_addr external_addr, ipv4_addr internal_addr, ipv4_addr web_server_addr):
       m_external_addr(external_addr),
       m_internal_addr(internal_addr),
       m_web_server_addr(web_server_addr)
   {}

    rp_alias(){}
};


class reverse_proxy_listener
{
public:
   server_socket m_listening_socket;
   struct rp_alias m_alias;
   reverse_proxy_listener(ipv4_addr external_addr, ipv4_addr internal_addr, ipv4_addr web_server_addr):
        m_alias(external_addr, internal_addr, web_server_addr){}

    reverse_proxy_listener(){}

    reverse_proxy_listener(reverse_proxy_listener&& other_listener)
   {
       m_listening_socket = std::move(other_listener.m_listening_socket);
       m_alias = other_listener.m_alias;
   }
};


struct config
{
   std::vector<reverse_proxy_listener> listener_vec;
} g_config;


bool read_config()
{
   boost::property_tree::ptree pt;
   boost::property_tree::ini_parser::read_ini("config.ini", pt);

    std::cout << "Loading configuration" << std::endl;

    g_is_debug = pt.get<bool>("debug_print");
    g_is_debug ? (std::cout << "Debug prints are enabled!" << std::endl) : (std::cout << "Debug prints are disabled!" << std::endl);

    int aliasNum = pt.get<int>("Global.alias_num");

    std::cout << "Loading " << aliasNum << " aliases" << std::endl;

    // read all aliases
   for (int i = 1; i <= aliasNum; ++i)
   {
       struct reverse_proxy_listener listener;

        // find the section of the i-th alias in the config file
       std::string sectionName = std::string("Alias") + boost::lexical_cast<std::string>(i);

        // external address
       std::string external_addr = pt.get<std::string>(sectionName + ".external_ip") + ":" + pt.get<std::string>(sectionName + ".external_port");
       listener.m_alias.m_external_addr = ipv4_addr(external_addr);

        // internal address
       std::string internal_addr = pt.get<std::string>(sectionName + ".internal_ip");
       listener.m_alias.m_internal_addr = ipv4_addr(internal_addr);

        // web server address
       std::string web_server_addr = pt.get<std::string>(sectionName + ".web_server_ip") + ":" + pt.get<std::string>(sectionName + ".web_server_port");
       listener.m_alias.m_web_server_addr = ipv4_addr(web_server_addr);

        std::cout
            << "Alias " << i << ": "
            << "Client"
           << " <-> "
           << "GW (" << listener.m_alias.m_external_addr
            << " <-> "
            << listener.m_alias.m_internal_addr << ")"
           << " <-> "
           << "WEB Server (" << listener.m_alias.m_web_server_addr << ")" << std::endl;

        g_config.listener_vec.push_back(std::move(listener));
   }

    return true;
}


class pipe_connection;


// a connection (either ingoing or outgoing) based on a file descriptor, with I/O buffers
class connection
{
   connected_socket _fd;

    // I/O buffers - point to the I/O buffers of the connected socket
   input_stream<char> _read_buf;
   output_stream<char> _write_buf;
   bool _is_closed;
   connection* _peer_connection; // connection to which we forward everything we read

public:
   pipe_connection* container;
   using unconsumed_remainder = std::experimental::optional<temporary_buffer<char>>;

    connection(connected_socket&& fd) :
       _fd(std::move(fd)),
       _read_buf(_fd.input()),
       _write_buf(_fd.output()),
        _is_closed(false),
       _peer_connection(nullptr)
   {}

   void set_peer_connection(connection* peer) {
       _peer_connection = peer;
   }

    void close() {
       _fd.shutdown_input();
       _fd.shutdown_output();
       _is_closed = true;
   }

    bool is_closed() {
       return _is_closed;
   }

    // consume traffic from this connection and apply logic on it (in our case - forward the traffic to the peer connection)
   future<> process_traffic() {
       return _read_buf.consume(*this).then([]() {
           return make_ready_future();
       });
   }

    // allow writing to this connection from outside
   future<unconsumed_remainder> write(temporary_buffer<char> buf) {
       _write_buf.write(buf.get()).then([this] {
            return _write_buf.flush();
       });

        return make_ready_future<unconsumed_remainder>();
   }

   // In order to use the 'consume' interface, we need to implement operator() which dictates what we do
    // when we read the buffer's contents. Then our class (connection) will be used as a functor.
   future<unconsumed_remainder> operator()(temporary_buffer<char> buf) {
       DEBUG_PRINT("consume called");

        // Forward the buffer we just read to the peer connection
       return _peer_connection->write(std::move(buf));
   }
};


// end to end connection which contain the connection from the client to the reverse proxy + the
// corresponding connection from the reverse proxy to the web server
class pipe_connection
{
   bool m_is_disconnected; // on either of the sides
   promise<> m_client_terminated_promise;
   promise<> m_server_terminated_promise;
   connection* m_ingoing_connection;
   connection* m_outgoing_connection;
   ipv4_addr m_client_address;
   ipv4_addr m_server_address;

public:
   pipe_connection():
       m_is_disconnected(false),
       m_ingoing_connection(nullptr),
       m_outgoing_connection(nullptr)
   {}

    ipv4_addr& get_server_address() {
       return m_server_address;
   }

    future<> process_traffic() {
       m_ingoing_connection->process_traffic().then([&]() {
           DEBUG_PRINT("ingoing connection terminated!");
           if (!m_is_disconnected) {
               m_is_disconnected = true;
               DEBUG_PRINT("closing outgoing connection...");
               m_outgoing_connection->close();
           }
           m_client_terminated_promise.set_value();
       });

       m_outgoing_connection->process_traffic().then([&]() {
           DEBUG_PRINT("outgoing connection terminated!");
           if (!m_is_disconnected) {
               m_is_disconnected = true;
               DEBUG_PRINT("closing ingoing connection...");
               m_ingoing_connection->close();
           }
           m_server_terminated_promise.set_value();
       });

        return when_all(m_client_terminated_promise.get_future(), m_server_terminated_promise.get_future()).then([&](std::tuple<future<>, future<>> joined) {
           DEBUG_PRINT("Connection from " << m_client_address << " to " << m_server_address << " has terminated!");
           delete m_ingoing_connection;
           delete m_outgoing_connection;

            return make_ready_future<>();
       });
   }

    void interconnect_client_and_server() {
       m_ingoing_connection->set_peer_connection(m_outgoing_connection);
       m_outgoing_connection->set_peer_connection(m_ingoing_connection);
   }

    void set_ingoing(connected_socket& ingoing_fd) {
       m_ingoing_connection = new connection(std::move(ingoing_fd));
       m_ingoing_connection->container = this;
   }

    void set_outgoing(connected_socket& outgoing_fd) {
       m_outgoing_connection = new connection(std::move(outgoing_fd));
       m_outgoing_connection->container = this;
   }

    void set_client_addr(ipv4_addr& client_address) {
       m_client_address = client_address;
   }

    void set_server_addr(ipv4_addr& server_address) {
       m_server_address = server_address;
   }
};


void connect_complete(connected_socket& outgoing_fd, pipe_connection* client_server_conn) {
   client_server_conn->set_outgoing(outgoing_fd);

    // set a pipe from the ingoing connection to the outgoing connection and vice versa
   client_server_conn->interconnect_client_and_server();

   // handle traffic in the pipe
   client_server_conn->process_traffic().then([client_server_conn]() {
       delete client_server_conn;
       DEBUG_PRINT("Connection deleted");
   });
}


void accept_complete(connected_socket& ingoing_fd, socket_address& client_addr, reverse_proxy_listener& listener) {
   pipe_connection* client_server_conn = new pipe_connection;
   ipv4_addr client_addr_ipv4 = ipv4_addr(client_addr);

    client_server_conn->set_client_addr(client_addr_ipv4);
   client_server_conn->set_server_addr(listener.m_alias.m_web_server_addr);

    // based on the new fd, create a connection with input/output buffers so we can read & write
   client_server_conn->set_ingoing(ingoing_fd);

    // connect to the web server
   DEBUG_PRINT("Trying to connect to address: " << listener.m_alias.m_web_server_addr);

    // binding to local ip is commented out because seastar's native stack doesn't support multiple ips
   engine().net().connect(make_ipv4_address(listener.m_alias.m_web_server_addr), make_ipv4_address(listener.m_alias.m_internal_addr)).then([client_server_conn] (connected_socket outgoing_fd) {
       DEBUG_PRINT("We have connected to address: " << client_server_conn->get_server_address());
       connect_complete(outgoing_fd, client_server_conn);
   });
}


void do_accept(reverse_proxy_listener& listener) {
   DEBUG_PRINT("do_accept called!");

   // When accept is done, we'll have a new fd to read from and an address of the client which connected. These two,
   // which together form a 2-tuple future, will be the input to the lambda expression
   listener.m_listening_socket.accept().then([&listener](connected_socket ingoing_fd, socket_address client_addr) {
       DEBUG_PRINT("We have accepted a connection from ip: " << ipv4_addr(client_addr));

       // handle the incoming connection, open a connection towards the server
       accept_complete(ingoing_fd, client_addr, listener);

        // call accept again, in order to handle subsequent incoming connections
       do_accept(listener);
   });

    DEBUG_PRINT("do_accept ended!");
}


void rp_listen(reverse_proxy_listener& listener)
{
   listen_options lo;
   lo.reuse_address = true;

   // listen on the external address
   listener.m_listening_socket = engine().listen(make_ipv4_address(listener.m_alias.m_external_addr), lo);
   std::cout << "RP started listening on address: " << listener.m_alias.m_external_addr <<std::endl;

    do_accept(listener);
}


int main(int ac, char** av)
{
   // read the listeners configuration
   read_config();

    app_template app;

    return app.run(ac, av, [] {
       // listen on all the listeners
       for (size_t i = 0; i < g_config.listener_vec.size(); ++i)
        {
           rp_listen(g_config.listener_vec[i]);
       }

       engine().at_exit([] {
           DEBUG_PRINT("exiting...");
       });
   });
}
