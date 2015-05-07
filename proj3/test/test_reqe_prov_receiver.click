

define($dev veth4)

FromDevice($dev) 
	->Print(Received)
	->Queue
	->Print(Sending)
	->ToDevice($dev)
