#ifndef CLICK_CLASSIFIER_HH
#define CLICK_CLASSIFIER_HH

#include <click/element.hh>

CLICK_DECLS

class Classifier : public Element {
	
	public:
		Classifier();
		~Classifier();
	
		const char *class_name() const {return "classifier";}
		const char *port_count() const {return "1/3";}
		const char *processing() const {return PUSH;}
		
		int configure(Vector<String>&, ErrorHandler*);
		
		//Pass the packet into function to identify this packet
		void push(int, Packet *);
		
		//void classifyPacket(Packet *);
	private:

};

CLICK_ENDDECLS
#endif
