#ifndef CLICK_CRNPACKETGEN_HH
#define CLICK_CRNPACKETGEN_HH

#include <click/element.hh>
#include <click/timer.hh>

CLICK_DECLS

class CrnRequester : public Element {

public:
	CrnRequester();
	~CrnRequester();

	const char *class_name() const { return "CrnRequester";}
	const char *port_count() const { return "1/1"; }
	const char *processing() const { return PUSH; }
	
	int configure(Vector<String>&, ErrorHandler*);
	void push(int, Packet *);
	int initialize(ErrorHandler *errh);
	void sendRequest();
	
private:
};

CLICK_ENDDECLS

#endif
