#ifndef CLICK_CRNREQUESTER_HH
#define CLICK_CRNREQUESTER_HH

#include <click/element.hh>
#include <click/timer.hh>

CLICK_DECLS

class CrnRequester : public Element {

public:
	CrnRequester();
	~CrnRequester();

	const char *class_name() const { return "CrnRequester";}
	const char *port_count() const { return "1/1"; }
	const char *processing() const { return AGNOSTIC; }
	
	int configure(Vector<String>&, ErrorHandler*);
	void push(int, Packet *);
	Packet*  pull(int);
	int initialize(ErrorHandler *errh);
	void run_timer(Timer *timer);
	void sendRequest();
	
private:
	Timer _timer;
	int current_loop;
};

CLICK_ENDDECLS

#endif
