#ifndef CLICK_CRN_ROUTING_HH
#define CLICK_CRN_ROUTING_HH


#include <click/element.hh>
#include <clicknet/udp.h>
#include <clicknet/ether.h>
#include <click/ipaddress.hh>
//#include <stdint.h>
#include <click/vector.hh>
//#include <std.h>
CLICK_DECLS

struct FTEntry
{
	uint8_t content_id;
	in_addr my_interface;
	uint8_t hopcount;
	
};

typedef Vector<FTEntry> ForwardingTable;//The data structure to maintain the ForwardingTable


class CrnRouting : public Element {
	
	public:
		CrnRouting();
		~CrnRouting();
		
		const char *class_name() const {return "CrnRouting";}
		const char *port_count() const {return "3/3";}
		const char *processing() const {return PUSH;}
		
		
		int configure(Vector<String>&, ErrorHandler*);
		
		void push(int, Packet *);
		void UpdateTable(uint8_t, in_addr, uint8_t);
		FTEntry LookupTable(uint8_t);
	
	private:
	
	ForwardingTable my_forwardingtable;
	
};

CLICK_ENDDECLS
#endif
