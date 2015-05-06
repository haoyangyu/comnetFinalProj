#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
#include "crn-packet-generator.hh"
#include "crn-header.hh"

CLICK_DECLS

CrnPacketGen::CrnPacketGen() : _timer(this), current_loop(0) {}
CrnPacketGen::~CrnPacketGen(){}

int CrnPacketGen::configure(Vector<String> &conf, ErrorHandler *errh) {
	return 0;
}

int CrnPacketGen::initialize(ErrorHandler *) {
	_timer.initialize(this);   // Initialize timer object (mandatory).
	_timer.schedule_after_sec(2);
	return 0;
}

void CrnPacketGen::run_timer(Timer *timer) {
	// This function is called when the timer fires.
	Timestamp now = Timestamp::now();
	click_chatter("%s: %{timestamp}: timer fired!\n",
               declaration().c_str(), &now);
	if(current_loop == 0) {
		this->sendRequest();
	} else if (current_loop == 1) {
		this->sendResponse();
	} else {
		this->sendUpdate();
	}
	current_loop++;
	if(current_loop < 3 ){
		_timer.reschedule_after_sec(2);
	}
}

void CrnPacketGen::sendRequest() {
	click_chatter("Sending request");
	WritablePacket *packet = Packet::make(sizeof(CrnPacket));
	CrnPacket *header = (CrnPacket *)packet->data();
	header->type = 0;
	header->in_interface="0.0.0.0";
	header->content_id = 0;
	output(0).push(packet);
}

void CrnPacketGen::sendResponse() {
	click_chatter("Sending response");
	//Creating space for content of size 10
	WritablePacket *packet = Packet::make(sizeof(CrnPacket));
	CrnPacket *header = (CrnPacket *)packet->data();
	header->type = 1;
	header->in_interface="0.0.0.0";
	header->content_id = 0;
	header->data=0;
	output(0).push(packet);
}

void CrnPacketGen::sendUpdate() {
	click_chatter("Sending update");
	WritablePacket *packet = Packet::make(sizeof(CrnPacket));
	CrnPacket *header = (CrnPacket *)packet->data();
	header->type = 2;
	header->in_interface="0.0.0.0";
	header->content_id = 0;
	output(0).push(packet);
}

void CrnPacketGen::push(int port, Packet *p) {
	click_chatter("ERROR: this should not happen");
	return;
}

CLICK_ENDDECLS
EXPORT_ELEMENT(CrnPacketGen)
