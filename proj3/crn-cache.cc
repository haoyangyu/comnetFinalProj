#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include "crn-header.hh"
#include "crn-header.hh"
#include "crn-cache.hh"

CLICK_DECLS

Cache::Cache(){}
Cache::~Cache(){}

int Cache::configure(Vector<String> &conf, ErrorHandler *errh){
        return 0;
}

void Cache::push(int port, Packet *p){
	click_chatter("Classifier got a packet of size %d",p->length());
        CrnPacket *cp =(CrnPacket *)p->data();

	//For input 0 : request packet
	if (port ==0 && cp->type ==0){
		//Check the Content Cache Table
		//If find the packet, send to SWITCH
		uint8_t temp_content_id = cp->content_id;
		if (isFoundContent(temp_content_id)){
			struct CCTEntry *cctEntry=lookUpCCT(temp_content_id);
			//Send out the packet
			
		}else{
		//If not find sent to SRT
		
		}
	}
}

bool Cache::isFoundContent(uint8_t id){
	
}

CCTEntry Cache::lookUpCCT(uint8_t id){

}
