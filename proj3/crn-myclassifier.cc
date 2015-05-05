#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include "crn-header.hh"
#include "crn-myclassifier.hh"

CLICK_DECLS

Myclassifier::Myclassifier(){}
Myclassifier::~Myclassifier(){}

int Myclassifier::configure(Vector<String> &conf, ErrorHandler *errh){
	return 0;
}
//Implement push function 

void Myclassifier::push(int port, Packet *p){
	click_chatter("Classifier got a packet of size %d",p->length());
	if (port != 0){
		click_chatter("ERROR: Got a packet on wrong port");
	}	
	
	CrnPacket *cp =(CrnPacket *)p->data();
	
	//If packet is a request packet, we define it come from port 0
	if (cp->type ==0){
		//Through output 0 to CACHE element 
		output(0).push(p);		
	}else if (cp -> type ==1){	
	//If packet is a content packet, we define it come from port 1
		//We need to save them in cache
		output(0).push(p);
		//Send the content out based on switch, define the output port 1 
		output(1).push(p);
	}else if (cp ->type ==2){
		//We need to send out the update packet through output port 2
		output(2).push(p);
	}else{
		p->kill();
	}
}

CLICK_ENDDECLS
EXPORT_ELEMENT(Myclassifier)


