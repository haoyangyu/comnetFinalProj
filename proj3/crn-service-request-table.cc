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
	
	
	CrnPacket *cp = (CrnPacket *) (p->data());
	if (port == 0 && cp->type == 0){//this is a request packet, insert the entry and push to Routing
		
		InsertEntry(cp->in_interface, cp->content_id);
		output(0).push(cp);
		
	}else if (port == 1 && cp->type == 1){//this is a content packet, remove the entry and push to Cache
		
		RemoveEntry(cp->content_id);
		output(1).push(cp);
		
	}
	
}

void CrnServiceRequestTable :: InsertEntry(in_addr in_interface, uint8_t content_id){
	
	int found_flag = 0;
	for (uint32_t i = 0; i<my_srt.size(); i++){
		
		if(content_id == my_srt[i] && in_interface == my_srt.in_interface){
		
			found_flag = 1;
			click_chatter("CrnServiceRequestTable::InsertEntry: Entry found, discard");
			
		}
		
	}
	if (found_flag == 0){//Entry not found, insert it.
		
		SRTEntry  temp_srtentry;
		temp_srtentry.in_interface = in_interface;
		temp_srtentry.content_id = content_id;
		my_srt.push_back(temp_srtentry);
		
	}
	
}

void CrnServiceRequestTable :: RemoveEntry(uint8_t content_id){
	
	 for(uint32_t i=0; i<my_srt.size(); i++){
		 
		 if(content_id ==  my_srt[i].content_id){
			 
			my_srt.erase(my_srt.begin()+i);
			break;
			 
		 }
		 
	 }
	
}



CLICK_ENDDECLS
EXPORT_ELEMENT(CrnServiceRequestTable )