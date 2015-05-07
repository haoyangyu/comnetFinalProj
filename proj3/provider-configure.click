
pv::CrnProvider;

//provider
pv[0]->UDPIPEncap(192.168.2.2, 10003, 192.168.2.1, 10002)
	->EtherEncap(0x0800, a6:59:b6:dd:76:d0, de:cb:b2:f0:57:6e)
	->ToDevice(veth4)
	
FromDevice(veth4)->Print(Received)
				->pv;