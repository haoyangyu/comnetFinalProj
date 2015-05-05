#ifndef CLICK_CLASSIFIER_HH
#define CLICK_CLASSIFIER_HH

#include <click/element.hh>

CLICK_DECLS

class classifier : public Element {
	
	public:
		classifier();
		~classifier();
	
		const char *class_name() const {return "classifier";}
		const char *port_count() const {return "1/2";}
		const char *processing() const {return PUSH;}
		
		int configure(Vector<String>&, ErrorHandler*);
		
		void push(int, Packet *);
		
		//	
		void classifyPacket(Packet *);

}
