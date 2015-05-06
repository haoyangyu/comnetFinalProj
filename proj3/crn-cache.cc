#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include "crn-header.hh"
#include "crn-cache.hh"

CLICK_DECLS

Cache::Cache(){
	my_contentCacheTable.clear();
}
Cache::~Cache(){}

int Cache::configure(Vector<String> &conf, ErrorHandler *errh){
        return 0;
}

void Cache::push(int port, Packet *p){
	click_chatter("Classifier got a packet of size %d",p->length());
        CrnPacket *cp =(CrnPacket *)p->data();
	if (port!=0){
		click_chatter("ERROR: Got a packet on wrong port");
		return;
	}
	//For request packet
	if (cp->type ==0){
		//Check the Content Cache Table
		//If find the packet, send to SWITCH
		uint8_t temp_content_id = cp->content_id;
		if (isFoundContent(temp_content_id)){
			struct CCTEntry cctEntry=lookUpCCT(temp_content_id);
			//Initial the response packet
			int packetsize =sizeof(CrnPacket);
			WritablePacket *packet =Packet::make(packetsize);
			if (packet == 0 )
				return click_chatter ("cannot make packet!!");
			memset(packet ->data(),0, packet->length());
			CrnPacket *new_cp = (CrnPacket *) packet->data();
			new_cp->type=1;	
			new_cp->content_id=temp_content_id;
			new_cp->data=cctEntry.data;
			//Send the packet out
			WritablePacket *wp = p->uniqueify();
	                memcpy(wp->data(), new_cp, sizeof(*new_cp));
        	        output(1).push(wp);
			//Remember to kill the request packet
			wp->kill();		
		}else{
		//If not find sent to SRT
			output(0).push(p);
		}
	}else if (cp->type ==1){
	//For content packet
	//save the packet into vector 
		struct CCTEntry cctEntry;
		cctEntry.content_id=cp->content_id;
		cctEntry.data=cp->data;
		my_contentCacheTable.push_back(cctEntry);	
	}else{
		p->kill();
	}
}

bool Cache::isFoundContent(uint8_t id){
	for (contentCacheTable::iterator i=my_contentCacheTable.begin(); i!= my_contentCacheTable.end() ; i++){
		if (id == i->content_id)
			return true;
	}
	return false;
}

struct CCTEntry Cache::lookUpCCT(uint8_t id){
	struct CCTEntry cctEntry={
				0,
				0,
				};
	//We access the table only when we are sure that the data is in the Table
	for (contentCacheTable::iterator i=my_contentCacheTable.begin(); i!=my_contentCacheTable.end(); i++){
		if (id == i->content_id){
			cctEntry.content_id = i->content_id;
			cctEntry.data = i->data;
			return cctEntry;
		}else{
			click_chatter ("Cannot find data");
		}	
	}
}


CLICK_ENDDECLS
EXPORT_ELEMENT(Cache)
