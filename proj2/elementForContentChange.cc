#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include "elementForContentChange.hh"

CLICK_DECLS

elementForContentChange::elementForContentChange(){}
elementForContentChange::~elementForContentChange(){}

int elementForContentChange::configure(Vector<String> &conf, ErrorHandler *errh) {

	if (cp_va_kparse(conf, this, errh, 
		"MAXPACKETSIZE", cpkM+cpkP, cpInteger, &maxSize,
		"changeTheContent", cpkM+cpkP, cpString, &stringForChange, cpEnd) < 0) return -1;
	return 0;

}

void elementForContentChange::push(int port, Packet *p){

        click_chatter("Got a packet size %d",p->length());
	if (p -> length() >maxSize) p->kill();
	WritablePacket *q= p->uniqueify();
	memcpy(q->data(), &stringForChange, sizeof(stringForChange));
	output(0).push(q);
}

CLICK_ENDDECLS
EXPORT_ELEMENT(elementForContentChange)


