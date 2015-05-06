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
		if (isFoundContent(temp_content_id)>=0){
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

uint8_t Cache::isFoundContent(uint8_t id){
	uint8_t rows=sizeof(my_contentCacheTable);
	for (uint8_t i=0; i<rows; ++i){
		if (id == my_contentCacheTable[i].content_id)
			return i;
	}
	return -1;
}

struct CCTEntry Cache::lookUpCCT(uint8_t id){
	uint8_t indexContent=isFoundContent(id);
	struct CCTEntry cctEntry={
				0,
				0,
				};
	if (indexContent>=0){
		cctEntry.content_id=my_contentCacheTable[indexContent].content_id;
		cctEntry.data=my_contentCacheTable[indexContent].data;
		return cctEntry;
	}else{
		click_chatter("EROOR: Cannot find Entry");
	}
}


CLICK_ENDDECLS
EXPORT_ELEMENT(Cache)