require(library /home/comnetsii/elements/lossyrouterport.click);

define($loss 0.2);
define($delay 0.2);

rp1 :: RouterPort(DEV veth2, IN_ADDR 192.168.1.2, OUT_ADDR 192.168.1.1, IN_PORT 10001, OUT_PORT 10000, IN_MAC 76:d3:fb:eb:e5:9b, OUT_MAC b2:55:7c:91:41:e9, LOSS $loss, DELAY $delay);
rp2 :: RouterPort(DEV veth3, IN_ADDR 192.168.2.1, OUT_ADDR 192.168.2.2, IN_PORT 10002, OUT_PORT 10003, IN_MAC 42:57:78:1a:41:ca, OUT_MAC 3e:3c:25:0f:da:7f, LOSS $loss,DELAY $delay);

rp1 -> Print(Forward, MAXLENGTH -1) -> rp2;
rp2 -> rp1;
