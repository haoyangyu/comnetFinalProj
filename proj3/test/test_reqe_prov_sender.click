define($src_ip 192.168.1.1)
define($dst_ip 192.168.1.2)

//src_mac&dst_mac addresses are needed to be changed
//if the virtual HWaddr changed
define($src_mac 46:a4:7a:f0:08:f7)
define($dst_mac aa:f9:9d:be:70:1a)

//Define the device name
define($dev veth1)

CrnRequester
	->IPEncap(4, $src_ip, $dst_ip)
	->EtherEncap(0x0800, $src_mac, $dst_mac)
	->Print(Sending)
	->ToDevice($dev);

//Hear back from the device
FromDevice($dev) -> Queue ->CrnRequester->Print(Received) ->Discard;
