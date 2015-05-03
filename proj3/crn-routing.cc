#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include "simplechangeelement.hh"
#include "crn-header.hh"

CLICK_DECLS

CrnRouting::CrnRouting(){};
CrnRouting::~CrnRouting(){};


int CrnRouting::configure(Vector<String> &conf, ErrorHandler *errh){
	return 0;
}

void CrnRouting::push(int port, Packet *p){
	
	clickchatter("Switch gets packet size %d", p->length);
	CrnPacket *cp = (CrnPacket *) (p->data());
	if(port == 2 && cp->type == 2){//the packet is a update packet and coming from port 2

		UpdateTable(cp->content_id, cp->my_interface, cp->hopcount);
		
	}else if(port == 0 && cp->type == 0){//the packet is a request packet and coming from port 0
		
		
		
	}
	
}
void CrnRouting::UpdateTable(Packet *p){
	
	
	
	
	
}

CLICK_ENDDECLS
EXPORT_ELEMENT(CrnRouting)