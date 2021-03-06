#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include "crn-header.hh"
#include "crn-service-request-table.hh"

CLICK_DECLS

CrnServiceRequestTable :: CrnServiceRequestTable (){
	
	my_srt.clear();
	
}

CrnServiceRequestTable :: ~CrnServiceRequestTable (){}


int CrnServiceRequestTable :: configure(Vector<String> &conf, ErrorHandler *errh){
	return 0;
}
void CrnServiceRequestTable :: push(int port, Packet *p){
	
	click_chatter("SRT gets packet size %d", p->length());
	CrnPacket *cp = (CrnPacket *) (p->data());
	if (cp->type == 0){//this is a request packet, insert the entry and push to Routing
		
		InsertEntry(cp->in_interface, cp->content_id);
		WritablePacket *wp = p->uniqueify();
		memcpy(wp->data(), cp, sizeof(*cp));
		output(0).push(wp);
		
	}else if (cp->type == 1){//this is a content packet, remove the entry and push to Cache
		
		RemoveEntry(cp->content_id);
		WritablePacket *wp = p->uniqueify();
		memcpy(wp->data(), cp, sizeof(*cp));
		output(1).push(wp);
		
	}
	
}

void CrnServiceRequestTable :: InsertEntry(in_addr in_interface, uint8_t content_id){
	
	
	int found_flag = 0;
	for(SRT::iterator i=my_srt.begin(); i!=my_srt.end(); i++){
		
		if(content_id == i->content_id && in_interface == i->in_interface){
		
			found_flag = 1;
			click_chatter("CrnServiceRequestTable::InsertEntry: Entry found, discard");
			
		}
		
	}
	if (found_flag == 0){//Entry not found, insert it.
		
		SRTEntry  temp_srtentry;
		temp_srtentry.in_interface = in_interface;
		temp_srtentry.content_id = content_id;
		my_srt.push_back(temp_srtentry);
		click_chatter("CrnServiceRequestTable :: InsertEntry: Insert an entry");
	}
	
}

void CrnServiceRequestTable :: RemoveEntry(uint8_t content_id){
	click_chatter("CrnServiceRequestTable :: RemoveEntry: entry removed");
	 for(SRT::iterator i=my_srt.begin(); i!=my_srt.end(); i++){
		 
		 if(content_id ==  i->content_id){
			 
			my_srt.erase(i);
			break;
			 
		 }
		 
	 }
	click_chatter("CrnServiceRequestTable::RemoveEntry: Entry removed");
}



CLICK_ENDDECLS
EXPORT_ELEMENT(CrnServiceRequestTable )
