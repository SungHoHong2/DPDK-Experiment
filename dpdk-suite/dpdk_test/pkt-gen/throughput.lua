package.path = package.path ..";?.lua;test/?.lua;app/?.lua;"
pktgen.screen("throughput measurement test\n");
pktgen.pause("test case 1\n", 2000);

pktgen.set("all", "count", 100000);
pktgen.set("all", "size", 256);
pktgen.set("all", "burst", 128);
pktgen.screen("on");

pktgen.dst_mac("1", "start", "00:1B:21:A6:D4:D5");
pktgen.start("1");

-- pause
pktgen.cls();
pktgen.screen("off");
pktgen.clear("all");
pktgen.reset("all");
-- pause

pktgen.screen("throughput measurement test\n");
pktgen.pause("test case 2\n", 2000);

pktgen.set("all", "count", 100000);
pktgen.set("all", "size", 256);
pktgen.set("all", "burst", 128);
pktgen.screen("on");

pktgen.dst_mac("1", "start", "00:1B:21:A6:D4:D5");
pktgen.start("1");
pktgen.delay(5000);
