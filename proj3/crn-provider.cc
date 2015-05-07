#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
#include "crn-provider.hh"
#include "crn-header.hh"

CLICK_DECLS

CrnProvider::CrnProvider(): _timer(this), current_loop(0){}
CrnProvider::~CrnProvider(){}

int CrnProvider::configure(Vector<String> &conf, ErrorHandler *errh) {
	return 0;
}

int CrnProvider::initialize(ErrorHandler *) {
	_timer.initialize(this);   // Initialize timer object (mandatory).
	_timer.schedule_after_sec(2);
	return 0;
}

void CrnProvider::run_timer(Timer *timer) {
	// This function is called when the timer fires.
	Timestamp now = Timestamp::now();
	click_chatter("CrnProvider: %s: %{timestamp}: timer fired!\n",
               declaration().c_str(), &now);
	if (current_loop ==2) {
		this->sendUpdate();
	}
	current_loop++;
	if(current_loop < 3 ){
		_timer.reschedule_after_sec(2);
	}
}

void CrnProvider::sendResponse() {
	click_chatter("CrnProvider: Sending response back");
	//Creating space for content of size 10
	WritablePacket *packet = Packet::make(sizeof(CrnPacket));
	CrnPacket *header = (CrnPacket *)packet->data();
	header->type = 1;
	//header->in_interface="0.0.0.0";
	header->content_id = 0;
	header->data=0;
	output(0).push(packet);
}

void CrnProvider::sendUpdate() {
	click_chatter("CrnProvider: Sending update");
	WritablePacket *packet = Packet::make(sizeof(CrnPacket));
	CrnPacket *header = (CrnPacket *)packet->data();
	header->type = 2;
	//header->in_interface="0.0.0.0";
	header->content_id = 0;
	output(1).push(packet);
}

void CrnProvider::push(int port, Packet *p) {
	click_chatter("CrnProvider: Process request packet");
	//We assume the privider has the content with content_id
	sendResponse();
	return;
}

CLICK_ENDDECLS
EXPORT_ELEMENT(CrnProvider)
