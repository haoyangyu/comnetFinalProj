#ifndef CLICK_CRNPROVIDER_HH
#define CLICK_CRNPROVIDER_HH

#include <click/element.hh>
#include <click/timer.hh>
CLICK_DECLS

class CrnProvider : public Element {

public:
	CrnProvider();
	~CrnProvider();

	const char *class_name() const { return "CrnProvider";}
	// 1 input only accept request packet
	// 2 output, 0 for response packet; 1 for update packet
	const char *port_count() const { return "1/2"; }
	const char *processing() const { return PUSH; }
	
	int configure(Vector<String>&, ErrorHandler*);
	void push(int, Packet *);
	int initialize(ErrorHandler *errh);
	void run_timer(Timer *timer);
	void sendResponse();
	void sendUpdate();
	
private:
	Timer _timer;
	int current_loop;
};

CLICK_ENDDECLS

#endif
