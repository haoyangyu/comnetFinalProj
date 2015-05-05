#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include "crn-header.hh"
#include "crn-classifier.hh"

CLICK_DECLS

Classifier::Classifier(){}
Classifier::~Classifier(){}

int Classifier::configure(Vector<String> &conf, ErrorHandler *errh){
	return 0;
}
//Implement push function 

void Classifier::push(int port, Packet *p){
	click_chatter("Classifier got a packet of size %d",p->length());
	CrnPacket *cp =(CrnPacket *)p->data();
	
	//If packet is a request packet, we define it come from port 0
	if (port ==0 && cp->type ==0){
		//Through output 0 to CACHE element 
		output(0).push(cp);		
	}
	
	//If packet is a content packet, we define it come from port 1
	if (port ==1 && cp->type ==1){
		//We need to save them in cache
		output(0).push(cp);
		//Question: how to send content back to host
		//Send the content out based on switch, define the output port 1 
		output(1).push(cp);
	}
	
	if (port ==2 && cp->type ==2){
		//We need to send out the update packet through output port 2
		output(2).push(cp);
	}
}

CLICK_ENDDECLS
EXPORT_ELEMENT(Classifier)


