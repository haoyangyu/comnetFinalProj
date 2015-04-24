#ifndef CLICK_ELEMENTFORCONTENTCHANGE_HH
#define CLICK_ELEMENTFORCONTENTCHANGE_HH
#include <click/element.hh>


CLICK_DECLS

class elementForContentChange : public Element {

	public :
		elementForContentChange();
		~elementForContentChange();

		const char *class_name() const {return "elementForContentChange";}
		const char *port_count() const {return "1/1";}
		const char *processing() const {return PUSH;}
		int configure(Vector<String>&, ErrorHandler*);

		void push(int, Packet *);

	private :
		String stringForChange;
		uint32_t maxSize;


};

CLICK_ENDDECLS
#endif



