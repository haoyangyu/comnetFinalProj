require(library /home/comnetsii/elements/routerport.click);

mc :: Myclassifier;
ca :: Cache;
srt:: CrnServiceRequestTable;
rt :: CrnRouting;
rq::CrnRequester;



rp1 :: RouterPort(DEV veth2, IN_ADDR 192.168.1.2, OUT_ADDR 192.168.1.1, IN_PORT 10001, OUT_PORT 10000, IN_MAC ca:05:3e:fc:76:8c, OUT_MAC e2:c7:0c:bc:c5:d7);
rp2 :: RouterPort(DEV veth3, IN_ADDR 192.168.2.1, OUT_ADDR 192.168.2.2, IN_PORT 10002, OUT_PORT 10003, IN_MAC de:cb:b2:f0:57:6e, OUT_MAC a6:59:b6:dd:76:d0);

//rp3 :: RouterPort(DEV veth2, IN_ADDR 192.168.1.2, OUT_ADDR 192.168.1.1, IN_PORT 10001, OUT_PORT 10000, IN_MAC ca:05:3e:fc:76:8c, OUT_MAC e2:c7:0c:bc:c5:d7);
//rp4 :: RouterPort(DEV veth3, IN_ADDR 192.168.2.1, OUT_ADDR 192.168.2.2, IN_PORT 10002, OUT_PORT 10003, IN_MAC de:cb:b2:f0:57:6e, OUT_MAC a6:59:b6:dd:76:d0);




//request path
rp1 ->Print(Received)-> mc;
mc[0] -> Print("mc::Request Processed") -> ca;
ca[1] ->Print("ca::Cache Return") ->rp1;

srt[0] ->rt;
rt[0]->Print("rt::Request Processed")->rp2;


//content path
rp2 -> mc;
mc[1] -> Print("mc::Response Processed") -> ca;
ca[0] -> Print("ca::Response Processed")-> srt;
srt[1] -> Print("srt::Response Processed")-> rp1;


//update path
mc[2] -> Print("mc::Update Processed") -> rt;
rt[1] -> Print("rt::Update Processed")-> rp1;

rt[2] -> Discard;

//requester
FromDevice(veth1)->rq;
rq->rp1;
//UDPIPEncap(192.168.1.1, 10000, 192.168.1.2, 10001)
//	->EtherEncap(0x0800, e2:c7:0c:bc:c5:d7, ca:05:3e:fc:76:8c)->Print(Sending)->rp1;

				
				


