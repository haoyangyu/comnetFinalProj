#ifndef CLICK_CRN_ROUTING_HH
#define CLICK_CRN_ROUTING_HH


#include <click/element.hh>
#include <clicknet/udp.h>
#include <clicknet/ether.h>
#include <click/ipaddress.hh>

CLICK_DECLS

struct FTEntry
{
	uint_32t content_id;
	in_addr my_interface;
	uint_32t hopcount;
	
};

typedef std::vector<FTEntry> ForwardingTable;//The data structure to maintain the ForwardingTable


class CnrRouting : public Element{
	
	public:
		CnrRouting();
		~CnrRouting();
		
		const char *class_name() const {return "CrnRouting";}
		const char *port_count() const {return "1/1";}
		const char *processing() const {return PUSH;}
		
		
		int configure(Vector<String>&, ErrorHandler*);
		
		void push(int, Packet *);
		void UpdateTable(uint_32t, in_addr, uint_32t);
		void LookupTable(uint_32t);
	
	private:
	
	ForwardingTable forwardingtable;
	
}

CLICK_ENDDECLS
#endif