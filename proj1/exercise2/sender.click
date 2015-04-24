//Sending the packets at the rate of 1 packet per second

define($src_ip 192.168.1.1)
define($dst_ip 192.168.1.2)
define($src_mac 5e:1c:a8:43:71:f9)
define($dst_mac ba:e4:d7:06:8c:4b)
define($dev veth1)

RatedSource(DATA "hello", RATE 1, LIMIT -1) 
	->IPEncap(4, $src_ip, $dst_ip)
	->EtherEncap(0x0800, $src_mac, $dst_mac)
	->Print(Sending)
	->ToDevice($dev)
