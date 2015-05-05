#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include "simplechangeelement.hh"
#include "crn-header.hh"
#include "crn-routing.hh"

CLICK_DECLS

CrnRouting::CrnRouting()
{
	my_forwardingtable.clear();
};
CrnRouting::~CrnRouting(){};


int CrnRouting::configure(Vector<String> &conf, ErrorHandler *errh){
	return 0;
}

void CrnRouting::push(int port, Packet *p){
	
	click_chatter("Switch gets packet size %d", p->length());
	CrnPacket *cp = (CrnPacket *) (p->data());
	if(port == 2 && cp->type == 2){//the packet is a update packet and coming from port 2

		UpdateTable(cp->content_id, cp->my_interface, cp->hopcount);
		
	}else if(port == 0 && cp->type == 0){//the packet is a request packet and coming from port 0
		FTEntry temp_FTEntry;
		temp_FTEntry = LookupTable(cp->content_id);
		cp->my_interface = temp_FTEntry.my_interface;
		
	}
	
	WritablePacket *wp = p->uniqueify();
	memcpy(wp->data(), cp, sizeof(*cp));
	output(1).push(wp);
	
}
void CrnRouting::UpdateTable(uint8_t content_id, in_addr my_interface, uint8_t hopcount){
	
	
	FTEntry ftentry;
	int found_flag = 0;
	//for(ForwardingTable::iterator i=my_forwardingtable.begin(); i!=my_forwardingtable.end(); i++){
	for(uint32_t i = 0; i < sizeof(my_forwardingtable); i++){
		if (content_id == my_forwardingtable[i].content_id){
			click_chatter("CrnRouting::UpdateTable: Entry found, discard the update");
			found_flag = 1;
		}
			
					
	}
	if(found_flag==0){
		click_chatter("CrnRouting::UpdateTable: Can not find duplicate entry, insert it!");
		ftentry.content_id = content_id;
		ftentry.my_interface = my_interface;
		ftentry.hopcount = hopcount;
		my_forwardingtable.push_back(ftentry);
	}
	
	
}

FTEntry CrnRouting::LookupTable(uint32_t content_id){
	
	FTEntry ftentry={
		0,//content_id
		0,//my_interface
		0,//hopcount
	};
	int found_flag = 0;
	for(uint32_t i = 0; i < sizeof(my_forwardingtable); i++){
		if (content_id == my_forwardingtable[i].content_id){
			click_chatter("CrnRouting::LookupTable: Entry found");
			ftentry.content_id = my_forwardingtable[i].content_id;
			ftentry.my_interface = my_forwardingtable[i].my_interface;
			ftentry.hopcount = my_forwardingtable[i].hopcount;
		}
						
	}
	
	return ftentry;
}

CLICK_ENDDECLS
EXPORT_ELEMENT(CrnRouting)
