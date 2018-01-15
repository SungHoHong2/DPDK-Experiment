
```
# visasu
sudo ./server --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.34 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp 1
wget -qO- http://10.218.111.253:10000 | sed -e 's/<[^>]*>//g'


# TCP seastar
./server --host-ipv4-addr 10.218.111.252 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2
wget -qO- http://10.218.111.252:10000 | sed -e 's/<[^>]*>//g'

sudo ./server -l 0-3 -n 4 -- -q 8 -p 0x2 -T 1 //dpdk is working fine
httpd works so I need something to add in the makefile
```


apps = [
    'apps/httpd/httpd',
    'apps/seawreck/seawreck',
    'apps/io_tester/io_tester',
    'apps/memcached/memcached',
    'apps/iotune/iotune',
    'tests/scheduling_group_demo',
    ]

all_artifacts = apps + tests + ['libseastar.a', 'seastar.pc']


arg_parser.add_argument('--with', dest='artifacts', action='append', choices=all_artifacts, default=[])
args = arg_parser.parse_args()


'apps/httpd/httpd': ['apps/httpd/demo.json', 'apps/httpd/main.cc'] + http + libnet + core,
