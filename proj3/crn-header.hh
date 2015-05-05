#ifndef CLICK_CRN_HEADER_HH
#define CLICK_CRN_HEADER_HH

CLICK_DECLS

struct CrnPacket{
	
	uint8_t type;//0 for request, 1 for content and 2 for update 
	uint32_t hopcount;
	uint32_t content_id;
	in_addr my_interface;
	const unsigned char* data;
	
};

CLICK_ENDDECLS
#endif