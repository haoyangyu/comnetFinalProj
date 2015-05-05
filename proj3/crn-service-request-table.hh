#ifndef CLICK_CRN_SRT_HH
#define CLICK_CRN_SRT_HH


#include <click/element.hh>
#include <clicknet/udp.h>
#include <clicknet/ether.h>
#include <click/ipaddress.hh>
#include <click/vector.hh>
CLICK_DECLS
struct SRTEntry {
	in_addr in_interface;
	uint8_t content_id;
};  

typedef Vector<SRTEntry> SRT; //data structure to store the content
class CrnServiceRequestTable : public Element {
	
	public:
		CrnServiceRequestTable();
		~CrnServiceRequestTable();
		
		const char *class_name() const {return "CrnServiceRequestTable";}
		const char *port_count() const {return "2/2";}
		const char *processing() const {return PUSH;}
		
		int configure(Vector<String>&, ErrorHandler*);
		void push(int, Packet *);
		
		void InsertEntry(in_addr, uint8_t);
		void RemoveEntry(uint8_t);
		
	private:
		
		SRT my_srt;
	
	
};


CLICK_ENDDECLS
#endif