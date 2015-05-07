#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
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
	WritablePacket *packet = Packet::make(sizeof(CrnPacket));
	CrnPacket *header = (CrnPacket *)packet->data();
	header->type = 0;
	//header->in_interface="0.0.0.0";
	header->content_id = 0;
	output(0).push(packet);
}

void CrnRequester::push(int port, Packet *p) {
	click_chatter("ERROR: this should not happen");
	return;
}

CLICK_ENDDECLS
EXPORT_ELEMENT(CrnRequester)
