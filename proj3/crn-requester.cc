#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
#include <clicknet/ip.h>
#include <clicknet/udp.h>
#include <clicknet/ether.h>
#include "crn-requester.hh"
#include "crn-header.hh"

CLICK_DECLS

CrnRequester::CrnRequester(): _timer(this), current_loop(0){}
CrnRequester::~CrnRequester(){}

int CrnRequester::configure(Vector<String> &conf, ErrorHandler *errh) {
	return 0;
}

int CrnRequester::initialize(ErrorHandler *){
	_timer.initialize(this);
	_timer.schedule_after_sec(2);
	return 0;
}

void CrnRequester::run_timer(Timer *timer){
	// This function is called when the timer fires.
	Timestamp now = Timestamp::now();
	click_chatter("%s: %{timestamp}: timer fired!\n",
               declaration().c_str(), &now);
	if(current_loop == 0) {
		this->sendRequest();
	}else{
		return;
	}
	current_loop++;
	if(current_loop < 3 ){
		_timer.reschedule_after_sec(2);
	}	

}
void CrnRequester::sendRequest() {
	click_chatter("Sending request");
	//int headroom = sizeof(click_ip)+sizeof(click_udp)+sizeof(click_ether);
	int headroom = 0;
	WritablePacket *packet = Packet::make(headroom,0,sizeof(CrnPacket),0);
	CrnPacket *header = (CrnPacket *)packet->data();
	header->type = 0;
	//header->in_interface="0.0.0.0";
	header->content_id = 0;
	output(0).push(packet);
}

void CrnRequester::push(int port, Packet *p) {
	
	CrnPacket *cp = (CrnPacket *) (p->data());
	if(cp->type==1){
		click_chatter("CrnRequester::This is a response packet!");
	}else if(cp->type==2){
		click_chatter("CrnRequester::This is a update packet");
		
	}else{
		
		p->kill();
	}
	return;
}
Packet* CrnRequester::pull(int){
	
	return 0;
}

CLICK_ENDDECLS
EXPORT_ELEMENT(CrnRequester)
