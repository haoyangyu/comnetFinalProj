require(library /home/comnetsii/elements/routerport.click);

//rp1 :: RouterPort(DEV veth2, IN_ADDR 192.168.1.2, OUT_ADDR 192.168.1.1, IN_PORT 10001, OUT_PORT 10000, IN_MAC 76:d3:fb:eb:e5:9b, OUT_MAC b2:55:7c:91:41:e9);

RatedSource (DATA "hello",RATE 1) ->elementForContentChange(1024, "morning")-> Print(Received, MAXLENGTH -1)->Discard;
