#ifndef CLICK_CLASSIFIER_HH
#define CLICK_CLASSIFIER_HH

#include <click/element.hh>
#include <click/vector.hh>
CLICK_DECLS

struct CCTEntry{
        uint8_t content_id;
		content_address;
};

//Define the data structure to maintain the Content Cache Table
typedef Vector<CCTEntry> contentCacheTable;

class Cache : public Element {

        public:
                Cache();
                ~Cache();

                const char *class_name() const {return "cache";}
		/*Input 0 -> request, 1 -> content
		  Output 0 -> request to SRT, 1 -> content back to front R/H*/
                const char *port_count() const {return "2/2";}
                const char *processing() const {return PUSH;}

                int configure(Vector<String>&, ErrorHandler*);

                void push(int, Packet *);
		//Self-defined functions
		bool isFoundContent(uint8_t);
		struct CCTEntry lookUpCCT(uint8_t);
};

CLICK_ENDDECLS
#endif
