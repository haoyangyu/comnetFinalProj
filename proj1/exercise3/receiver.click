
define($dev veth2)

//Receive packets sent from veth1 to veth2
FromDevice($dev) 
	->Print(Received)
	->Queue
	->Print(Sending)
	->ToDevice($dev)

