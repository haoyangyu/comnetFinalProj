#ifndef CLICK_MYCLASSIFIER_HH
#define CLICK_MYCLASSIFIER_HH

#include <click/element.hh>

CLICK_DECLS

class Myclassifier : public Element {
	
	public:
		Myclassifier();
		~Myclassifier();
	
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
