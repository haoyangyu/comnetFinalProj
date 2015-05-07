rq::CrnRequester;
//pg::CrnPacketGen;

//requester
FromDevice(veth1)->Print(Received)
				->[0]rq;
rq->UDPIPEncap(192.168.1.1, 10000, 192.168.1.2, 10001)
	->EtherEncap(0x0800, e2:c7:0c:bc:c5:d7, ca:05:3e:fc:76:8c)->Print(Sending)->ToDevice(veth1)

	
