//Sending the packets at the rate of 1 packet per second

define($src_ip 192.168.1.1)
define($dst_ip 192.168.1.2)

//src_mac&dst_mac addresses are needed to be changed
//if the virtual HWaddr changed
define($src_mac 9a:1b:2c:e4:e7:64)
define($dst_mac 5a:8f:26:a8:6a:1a)

//Define the device name
define($dev veth1)

RatedSource(DATA "hello", RATE 1, LIMIT -1) 
	->IPEncap(4, $src_ip, $dst_ip)
	->EtherEncap(0x0800, $src_mac, $dst_mac)
	->Print(Sending)
	->ToDevice($dev);

//Hear back from the device
FromDevice($dev) -> Queue->Print(Received, MAXLENGTH -1) ->Discard;
