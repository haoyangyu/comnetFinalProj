require(library /home/comnetsii/elements/routerport.click);

define($dev1 veth2)
define($dev2 veth3)

rp1 :: RouterPort(DEV veth2, IN_ADDR 192.168.1.2, OUT_ADDR 192.168.1.1, IN_PORT 10001, OUT_PORT 10000, IN_MAC aa:f9:9d:be:70:1a, OUT_MAC 46:a4:7a:f0:08:f7);
rp2 :: RouterPort(DEV veth3, IN_ADDR 192.168.2.1, OUT_ADDR 192.168.2.2, IN_PORT 10002, OUT_PORT 10003, IN_MAC 92:ed:dd:13:10:ca, OUT_MAC d2:32:be:c8:93:39);

rp1 -> Print(Changed, MAXLENGTH -1) -> rp2;
rp2 -> rp1;
