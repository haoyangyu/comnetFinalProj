#ifndef CLICK_CRN_ROUTING_HH
#define CLICK_CRN_ROUTING_HH


#include <click/element.hh>
#include <clicknet/udp.h>
#include <clicknet/ether.h>
#include <click/ipaddress.hh>
#include <click/vector.hh>
CLICK_DECLS

struct FTEntry
{
	uint32_t content_id;
	in_addr out_interface;
	uint32_t hopcount;
	
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
		void UpdateTable(uint32_t, in_addr, uint32_t);
		FTEntry LookupTable(uint32_t);
	
	private:
	
	ForwardingTable my_forwardingtable;
	
};

CLICK_ENDDECLS
#endif