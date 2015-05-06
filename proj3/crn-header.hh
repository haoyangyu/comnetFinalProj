#ifndef CLICK_CRN_HEADER_HH
#define CLICK_CRN_HEADER_HH

#include "click/ipaddress.hh"

CLICK_DECLS

struct CrnPacket{
	
	uint8_t type;//0 for request, 1 for content and 2 for update 
	uint8_t hopcount;
	uint8_t content_id;
	in_addr in_interface;
	in_addr out_interface;
	const unsigned char* data;
	
};

CLICK_ENDDECLS
#endif
