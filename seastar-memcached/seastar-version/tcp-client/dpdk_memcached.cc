#include "md5.hh"
#include "dpdk_memcached.hh"
#include "dpdk_basic.hh"
#include "dpdk_error.hh"
#include <sys/time.h>

#define memcached_is_auto_eject_hosts(__object) ((__object)->flags.auto_eject_hosts)

#define util_literal_param(X) (X), (static_cast<size_t>((sizeof(X) - 1)))
#define memcached_literal_param util_literal_param

#define util_literal_param_size(X) static_cast<size_t>(sizeof(X) - 1)
#define memcached_literal_param_size util_literal_param_size
#define memcached_is_weighted_ketama(__object) ((__object)->ketama.weighted_)


static inline void *libmemcached_realloc(const memcached_st *self, void *mem, size_t nmemb,  const size_t size)
{
    if (self)
    {
        return self->allocators.realloc(self, mem, nmemb * size, self->allocators.context);
    }

#ifdef __cplusplus
    return std::realloc(mem, size);
#else
    return realloc(mem, size);
#endif
}

#define libmemcached_xrealloc(__memcachd_st, __mem, __nelem, __type) ((__type *)libmemcached_realloc((__memcachd_st), (__mem), (__nelem), sizeof(__type)))

bool _is_auto_eject_host(const memcached_st *ptr)
{
    return ptr->flags.auto_eject_hosts;
}


struct memcached_instance_st {
    in_port_t port() const
    {
        return port_;
    }

    void port(in_port_t arg)
    {
        port_= arg;
    }

    void mark_server_as_clean()
    {
        server_failure_counter= 0;
        server_timeout_counter= 0;
        next_retry= 0;
    }

    void disable()
    {
    }

    void enable()
    {
    }

    bool valid() const;

    bool is_shutting_down() const;

    void start_close_socket();
    void close_socket();
    void reset_socket();

    uint32_t response_count() const
    {
        return cursor_active_;
    }

    struct {
        bool is_allocated;
        bool is_initialized;
        bool is_shutting_down;
        bool is_dead;
        bool ready;
    } options;

    short _events;
    short _revents;

    short events(void)
    {
        return _events;
    }

    short revents(void)
    {
        return _revents;
    }

    const char* hostname()
    {
        return _hostname;
    }

    void hostname(const memcached_string_t& hostname_)
    {
        if (hostname_.size)
        {
            memcpy(_hostname, hostname_.c_str, hostname_.size);
            _hostname[hostname_.size]= 0;
        }
        else
        {
            memcpy(_hostname, memcached_literal_param("localhost"));
            _hostname[memcached_literal_param_size("localhost")]= 0;
        }
    }

    void events(short);
    void revents(short);

    uint32_t cursor_active_;
    in_port_t port_;
    memcached_socket_t fd;
    uint32_t io_bytes_sent; /* # bytes sent since last read */
    uint32_t request_id;
    uint32_t server_failure_counter;
    uint64_t server_failure_counter_query_id;
    uint32_t server_timeout_counter;
    uint32_t server_timeout_counter_query_id;
    uint32_t weight;
    uint32_t version;
    enum memcached_server_state_t state;
    struct {
        uint32_t read;
        uint32_t write;
        uint32_t timeouts;
        size_t _bytes_read;
    } io_wait_count;
    uint8_t major_version; // Default definition of UINT8_MAX means that it has not been set.
    uint8_t micro_version; // ditto, and note that this is the third, not second version bit
    uint8_t minor_version; // ditto
    memcached_connection_t type;
    char *read_ptr;
    size_t read_buffer_length;
    size_t read_data_length;
    size_t write_buffer_offset;
    struct addrinfo *address_info;
    struct addrinfo *address_info_next;
    time_t next_retry;
    struct memcached_st *root;
    uint64_t limit_maxbytes;
    struct memcached_error_t *error_messages;
    char read_buffer[MEMCACHED_MAX_BUFFER];
    char write_buffer[MEMCACHED_MAX_BUFFER];
    char _hostname[MEMCACHED_NI_MAXHOST];

    void clear_addrinfo()
    {
        if (address_info)
        {
            freeaddrinfo(address_info);
            address_info= NULL;
            address_info_next= NULL;
        }
    }
};



/* string value */
struct memcached_continuum_item_st
{
    uint32_t index;
    uint32_t value;
};

struct bucket_t {
    uint32_t master;
    uint32_t forward;
};


struct memcached_virtual_bucket_t {
    bool has_forward;
    uint32_t size;
    uint32_t replicas;
    struct bucket_t buckets[];
};


uint32_t memcached_server_count(const memcached_st *self)
{
    if (self == NULL)
        return 0;

    return self->number_of_hosts;
}

memcached_instance_st* memcached_instance_list(const memcached_st *shell)
{
    const Memcached* memc= memcached2Memcached(shell);
    if (memc)
    {
        return (memcached_instance_st*)memc->servers;
    }

    return NULL;
}


static int compare_servers(const void *p1, const void *p2)
{
    const memcached_instance_st * a= (const memcached_instance_st *)p1;
    const memcached_instance_st * b= (const memcached_instance_st *)p2;

    int return_value= strcmp(a->_hostname, b->_hostname);

    if (return_value == 0)
    {
        return_value= int(a->port() - b->port());
    }

    return return_value;
}


static uint32_t ketama_server_hash(const char *key, size_t key_length, uint32_t alignment)
{
    unsigned char results[16];

    libhashkit_md5_signature((unsigned char*)key, key_length, results);

    return ((uint32_t) (results[3 + alignment * 4] & 0xFF) << 24)
           | ((uint32_t) (results[2 + alignment * 4] & 0xFF) << 16)
           | ((uint32_t) (results[1 + alignment * 4] & 0xFF) << 8)
           | (results[0 + alignment * 4] & 0xFF);
}



static void MD5Init (MD5_CTX *context)      /* context */
{
    context->count[0] = context->count[1] = 0;
    /* Load magic initialization constants.
  */
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
}

static void MD5Update (
        MD5_CTX *context,                                        /* context */
        const unsigned char *input,                              /* input block */
        unsigned int inputLen)                     /* length of input block */
{
    unsigned int i, idx, partLen;

    /* Compute number of bytes mod 64 */
    idx = (unsigned int)((context->count[0] >> 3) & 0x3F);


    /* Update number of bits */
    if ((context->count[0] += ((UINT4)inputLen << 3))
        < ((UINT4)inputLen << 3))
        context->count[1]++;
    context->count[1] += ((UINT4)inputLen >> 29);

    partLen = 64 - idx;

    /* Transform as many times as possible.
  */
    if (inputLen >= partLen) {
        memcpy((POINTER)&context->buffer[idx], (CONST_POINTER)input, partLen);
        MD5Transform(context->state, context->buffer);

        for (i = partLen; i + 63 < inputLen; i += 64)
            MD5Transform (context->state, (CONST_POINTER)&input[i]);

        idx = 0;
    }
    else
        i = 0;

    /* Buffer remaining input */
    memcpy((POINTER)&context->buffer[idx], (CONST_POINTER)&input[i],
           inputLen-i);
}


void md5_signature(const unsigned char *key, unsigned int length, unsigned char *result)
{
    MD5_CTX my_md5;

    MD5Init(&my_md5);
    (void)MD5Update(&my_md5, key, length);
    MD5Final(result, &my_md5);
}


void libhashkit_md5_signature(const unsigned char *key, size_t length, unsigned char *result)
{
    md5_signature(key, (uint32_t)length, result);
}


static memcached_return_t update_continuum(Memcached *ptr)
{
    uint32_t continuum_index= 0;
    uint32_t pointer_counter= 0;
    uint32_t pointer_per_server= MEMCACHED_POINTS_PER_SERVER;
    uint32_t pointer_per_hash= 1;
    uint32_t live_servers= 0;
    struct timeval now;

    memcached_instance_st* list= memcached_instance_list(ptr);

    /* count live servers (those without a retry delay set) */
    bool is_auto_ejecting= _is_auto_eject_host(ptr);
    if (is_auto_ejecting)
    {
        live_servers= 0;
        ptr->ketama.next_distribution_rebuild= 0;
        for (uint32_t host_index= 0; host_index < memcached_server_count(ptr); ++host_index)
        {
            if (list[host_index].next_retry <= now.tv_sec)
            {
                live_servers++;
            }
            else
            {
                if (ptr->ketama.next_distribution_rebuild == 0 or list[host_index].next_retry < ptr->ketama.next_distribution_rebuild)
                {
                    ptr->ketama.next_distribution_rebuild= list[host_index].next_retry;
                }
            }
        }
    }
    else
    {
        live_servers= memcached_server_count(ptr);
    }

    uint32_t points_per_server= (uint32_t) (memcached_is_weighted_ketama(ptr) ? MEMCACHED_POINTS_PER_SERVER_KETAMA : MEMCACHED_POINTS_PER_SERVER);

    if (live_servers == 0)
    {
        return MEMCACHED_SUCCESS;
    }

    if (live_servers > ptr->ketama.continuum_count)
    {
        memcached_continuum_item_st *new_ptr;

        new_ptr= libmemcached_xrealloc(ptr, ptr->ketama.continuum, (live_servers + MEMCACHED_CONTINUUM_ADDITION) * points_per_server, memcached_continuum_item_st);

        if (new_ptr == 0)
        {
            return MEMCACHED_MEMORY_ALLOCATION_FAILURE;
        }

        ptr->ketama.continuum= new_ptr;
        ptr->ketama.continuum_count= live_servers + MEMCACHED_CONTINUUM_ADDITION;
    }

    uint64_t total_weight= 0;
    if (memcached_is_weighted_ketama(ptr))
    {
        for (uint32_t host_index = 0; host_index < memcached_server_count(ptr); ++host_index)
        {
            if (is_auto_ejecting == false or list[host_index].next_retry <= now.tv_sec)
            {
                total_weight += list[host_index].weight;
            }
        }
    }

    for (uint32_t host_index= 0; host_index < memcached_server_count(ptr); ++host_index) {
        if (is_auto_ejecting and list[host_index].next_retry > now.tv_sec) {
            continue;
        }

        if (memcached_is_weighted_ketama(ptr)) {
            float pct = (float) list[host_index].weight / (float) total_weight;
            pointer_per_server = (uint32_t)((::floor(
                    (float) (pct * MEMCACHED_POINTS_PER_SERVER_KETAMA / 4 * (float) live_servers + 0.0000000001))) * 4);
            pointer_per_hash = 4;
        }


        if (ptr->distribution == MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA_SPY) {
            for (uint32_t pointer_index = 0;
                 pointer_index < pointer_per_server / pointer_per_hash;
                 pointer_index++) {
                char sort_host[1 + MEMCACHED_NI_MAXHOST + 1 + MEMCACHED_NI_MAXSERV + 1 + MEMCACHED_NI_MAXSERV] = "";
                int sort_host_length;

                // Spymemcached ketema key format is: hostname/ip:port-index
                // If hostname is not available then: /ip:port-index
                sort_host_length = snprintf(sort_host, sizeof(sort_host),
                                            "/%s:%u-%u",
                                            list[host_index]._hostname,
                                            (uint32_t) list[host_index].port(),
                                            pointer_index);

                if (memcached_is_weighted_ketama(ptr)) {
                    for (uint32_t x = 0; x < pointer_per_hash; x++) {
                        uint32_t value = ketama_server_hash(sort_host, (size_t) sort_host_length, x);
                        ptr->ketama.continuum[continuum_index].index = host_index;
                        ptr->ketama.continuum[continuum_index++].value = value;
                    }
                } else {
                    uint32_t value = hashkit_digest(&ptr->hashkit, sort_host, (size_t) sort_host_length);
                    ptr->ketama.continuum[continuum_index].index = host_index;
                    ptr->ketama.continuum[continuum_index++].value = value;
                }
            }
        }
    }
//        else
//        {
//            for (uint32_t pointer_index= 1;
//                 pointer_index <= pointer_per_server / pointer_per_hash;
//                 pointer_index++)
//            {
//                char sort_host[MEMCACHED_NI_MAXHOST +1 +MEMCACHED_NI_MAXSERV +1 +MEMCACHED_NI_MAXSERV]= "";
//                int sort_host_length;
//
//                if (list[host_index].port() == MEMCACHED_DEFAULT_PORT)
//                {
//                    sort_host_length= snprintf(sort_host, sizeof(sort_host),
//                                               "%s-%u",
//                                               list[host_index]._hostname,
//                                               pointer_index - 1);
//                }
//                else
//                {
//                    sort_host_length= snprintf(sort_host, sizeof(sort_host),
//                                               "%s:%u-%u",
//                                               list[host_index]._hostname,
//                                               (uint32_t)list[host_index].port(),
//                                               pointer_index - 1);
//                }
//
//                if (size_t(sort_host_length) >= sizeof(sort_host) or sort_host_length < 0)
//                {
//                    return memcached_set_error(*ptr, MEMCACHED_MEMORY_ALLOCATION_FAILURE, MEMCACHED_AT,
//                                               memcached_literal_param("snprintf(sizeof(sort_host)))"));
//                }
//
//                if (memcached_is_weighted_ketama(ptr))
//                {
//                    for (uint32_t x = 0; x < pointer_per_hash; x++)
//                    {
//                        uint32_t value= ketama_server_hash(sort_host, (size_t)sort_host_length, x);
//                        ptr->ketama.continuum[continuum_index].index= host_index;
//                        ptr->ketama.continuum[continuum_index++].value= value;
//                    }
//                }
//                else
//                {
//                    uint32_t value= hashkit_digest(&ptr->hashkit, sort_host, (size_t)sort_host_length);
//                    ptr->ketama.continuum[continuum_index].index= host_index;
//                    ptr->ketama.continuum[continuum_index++].value= value;
//                }
//            }
//        }
//
//        pointer_counter+= pointer_per_server;
//    }
//
//    assert_msg(ptr, "Programmer Error, no valid ptr");
//    assert_msg(ptr->ketama.continuum, "Programmer Error, empty ketama continuum");
//    assert_msg(memcached_server_count(ptr) * MEMCACHED_POINTS_PER_SERVER <= MEMCACHED_CONTINUUM_SIZE, "invalid size information being given to qsort()");
//    ptr->ketama.continuum_points_counter= pointer_counter;
//    qsort(ptr->ketama.continuum, ptr->ketama.continuum_points_counter, sizeof(memcached_continuum_item_st), continuum_item_cmp);
//
//    if (DEBUG)
//    {
//        for (uint32_t pointer_index= 0; memcached_server_count(ptr) && pointer_index < ((live_servers * MEMCACHED_POINTS_PER_SERVER) - 1); pointer_index++)
//        {
//            WATCHPOINT_ASSERT(ptr->ketama.continuum[pointer_index].value <= ptr->ketama.continuum[pointer_index + 1].value);
//        }
//    }

    return MEMCACHED_SUCCESS;
}

static void sort_hosts(Memcached *ptr)
{
    if (memcached_server_count(ptr))
    {
        qsort(memcached_instance_list(ptr), memcached_server_count(ptr), sizeof(memcached_instance_st), compare_servers);
    }
}

memcached_return_t run_distribution(Memcached *ptr)
{
    if (ptr->flags.use_sort_hosts)
    {
        sort_hosts(ptr);
    }

    switch (ptr->distribution)
    {
        case MEMCACHED_DISTRIBUTION_CONSISTENT:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA_SPY:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_WEIGHTED:
            return update_continuum(ptr);

        case MEMCACHED_DISTRIBUTION_VIRTUAL_BUCKET:
        case MEMCACHED_DISTRIBUTION_MODULA:
            break;

        case MEMCACHED_DISTRIBUTION_RANDOM:
            srandom((uint32_t) time(NULL));
            break;

        case MEMCACHED_DISTRIBUTION_CONSISTENT_MAX:
        default:
            std::cout << "howdy" << std::endl;
    }

    return MEMCACHED_SUCCESS;
}


uint32_t memcached_virtual_bucket_get(const memcached_st *self, uint32_t digest)
{
    if (self)
    {
        if (self->virtual_bucket)
        {
            uint32_t result= (uint32_t) (digest & (self->virtual_bucket->size -1));
            return self->virtual_bucket->buckets[result].master;
        }

        return (uint32_t) (digest & (self->number_of_hosts -1));
    }

    return 0;
}

memcached_return_t initialize_query(Memcached *self, bool increment_query_id)
{
    if (self == NULL)
    {
        return MEMCACHED_INVALID_ARGUMENTS;
    }

    if (increment_query_id)
    {
        self->query_id++;
    }

    if (self->state.is_time_for_rebuild)
    {
        memcached_reset(self);
    }

    memcached_error_free(*self);
    memcached_result_reset(&self->result);

    return MEMCACHED_SUCCESS;
}

struct memcached_array_st
{
    Memcached *root;
    size_t size;
    char c_str[];
};

size_t memcached_array_size(memcached_array_st *array)
{
    if (array)
    {
        return array->size;
    }

    return 0;
}

const char *memcached_array_string(memcached_array_st *array)
{
    if (array)
    {
        return array->c_str;
    }

    return NULL;
}

static inline void _regen_for_auto_eject(Memcached *ptr)
{
    if (_is_auto_eject_host(ptr) && ptr->ketama.next_distribution_rebuild)
    {
        struct timeval now;

        if (gettimeofday(&now, NULL) == 0 and
            now.tv_sec > ptr->ketama.next_distribution_rebuild)
        {
            run_distribution(ptr);
        }
    }
}


static uint32_t dispatch_host(const Memcached *ptr, uint32_t hash)
{
    switch (ptr->distribution)
    {
        case MEMCACHED_DISTRIBUTION_CONSISTENT:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_WEIGHTED:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA_SPY:
        {
            uint32_t num= ptr->ketama.continuum_points_counter;

            memcached_continuum_item_st *begin, *end, *left, *right, *middle;
            begin= left= ptr->ketama.continuum;
            end= right= ptr->ketama.continuum + num;

            while (left < right)
            {
                middle= left + (right - left) / 2;
                if (middle->value < hash)
                    left= middle + 1;
                else
                    right= middle;
            }
            if (right == end)
                right= begin;
            return right->index;
        }
        case MEMCACHED_DISTRIBUTION_MODULA:
            return hash % memcached_server_count(ptr);
        case MEMCACHED_DISTRIBUTION_RANDOM:
            return (uint32_t) random() % memcached_server_count(ptr);
        case MEMCACHED_DISTRIBUTION_VIRTUAL_BUCKET:
        {
            return memcached_virtual_bucket_get(ptr, hash);
        }
        default:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_MAX:
            return hash % memcached_server_count(ptr);
    }
    /* NOTREACHED */
}


uint32_t hashkit_digest(const hashkit_st *self, const char *key, size_t key_length)
{
    return self->base_hash.function(key, key_length, self->base_hash.context);
}


static inline uint32_t generate_hash(const Memcached *ptr, const char *key, size_t key_length)
{
    return hashkit_digest(&ptr->hashkit, key, key_length);
}



static inline uint32_t _generate_hash_wrapper(const Memcached *ptr, const char *key, size_t key_length)
{
    if (memcached_server_count(ptr) == 1)
        return 0;

    if (ptr->flags.hash_with_namespace)
    {
        size_t temp_length= memcached_array_size(ptr->_namespace) + key_length;
        char temp[MEMCACHED_MAX_KEY];

        if (temp_length > MEMCACHED_MAX_KEY -1)
            return 0;

        strncpy(temp, memcached_array_string(ptr->_namespace), memcached_array_size(ptr->_namespace));
        strncpy(temp + memcached_array_size(ptr->_namespace), key, key_length);

        return generate_hash(ptr, temp, temp_length);
    }
    else
    {
        return generate_hash(ptr, key, key_length);
    }
}

uint32_t memcached_generate_hash_with_redistribution(memcached_st *ptr, const char *key, size_t key_length)
{
    uint32_t hash= _generate_hash_wrapper(ptr, key, key_length);

    _regen_for_auto_eject(ptr);

    return dispatch_host(ptr, hash);
}



static inline memcached_return_t memcached_send(memcached_st *shell,
                                                const char *group_key, size_t group_key_length,
                                                const char *key, size_t key_length,
                                                const char *value, size_t value_length,
                                                const time_t expiration,
                                                const uint32_t flags,
                                                const uint64_t cas,
                                                memcached_storage_action_t verb)
{
    Memcached* ptr= memcached2Memcached(shell);
    memcached_return_t rc;
    if (memcached_failed(rc= initialize_query(ptr, true)))
    {
        return rc;
    }

    uint32_t server_key= memcached_generate_hash_with_redistribution(ptr, group_key, group_key_length);
//    memcached_instance_st* instance= memcached_instance_fetch(ptr, server_key);
//
//    WATCHPOINT_SET(instance->io_wait_count.read= 0);
//    WATCHPOINT_SET(instance->io_wait_count.write= 0);
//
//    bool flush= true;
//    if (memcached_is_buffering(instance->root) and verb == SET_OP)
//    {
//        flush= false;
//    }
//
//    bool reply= memcached_is_replying(ptr);
//
//    hashkit_string_st* destination= NULL;
//
//    if (memcached_is_encrypted(ptr))
//    {
//        if (can_by_encrypted(verb) == false)
//        {
//            return memcached_set_error(*ptr, MEMCACHED_NOT_SUPPORTED, MEMCACHED_AT,
//                                       memcached_literal_param("Operation not allowed while encyrption is enabled"));
//        }
//
//        if ((destination= hashkit_encrypt(&ptr->hashkit, value, value_length)) == NULL)
//        {
//            return rc;
//        }
//        value= hashkit_string_c_str(destination);
//        value_length= hashkit_string_length(destination);
//    }
//
//    if (memcached_is_binary(ptr))
//    {
//        rc= memcached_send_binary(ptr, instance, server_key,
//                                  key, key_length,
//                                  value, value_length, expiration,
//                                  flags, cas, flush, reply, verb);
//    }
//    else
//    {
//        rc= memcached_send_ascii(ptr, instance,
//                                 key, key_length,
//                                 value, value_length, expiration,
//                                 flags, cas, flush, reply, verb);
//    }
//
//    hashkit_string_free(destination);

    return rc;
}



memcached_return_t dpdk_memcached_set(memcached_st *ptr, const char *key, size_t key_length,
                                 const char *value, size_t value_length,
                                 time_t expiration,
                                 uint32_t flags)
{
    std::cout << "dpdk_memcached_set BEGIN" << std::endl;
    memcached_return_t rc;
    LIBMEMCACHED_MEMCACHED_SET_START();
    rc= memcached_send(ptr, key, key_length,
                       key, key_length, value, value_length,
                       expiration, flags, 0, SET_OP);
    LIBMEMCACHED_MEMCACHED_SET_END();

    std::cout << "dpdk_memcached_set END" << std::endl;
    return rc;
}

