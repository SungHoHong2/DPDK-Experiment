package.path = package.path ..";?.lua;test/?.lua;app/?.lua;"
pktgen.screen("throughput measurement test\n");
pktgen.pause("test case 1\n", 2000);

pktgen.set("all", "count", 100000);
pktgen.set("all", "size", 256);
pktgen.set("all", "burst", 128);
pktgen.screen("on");

local seq_table = {
    ["eth_dst_addr"] = "00:1B:21:A6:D4:D5",
    ["pktSize"] = 128
  };
pktgen.seqTable(0, "all", seq_table );
pktgen.start("0");

pktgen.delay(5000);

pktgen.screen("done\n");
prints("pktgen.info", pktgen.info);
