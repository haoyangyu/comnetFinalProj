#ifndef CLICK_CACHE_HH
#define CLICK_CACHE_HH

#include <click/element.hh>
#include <click/vector.hh>
#include <click/ipaddress.hh>
CLICK_DECLS

//Simplify the CCT as the table contains Content name and real contents
struct CCTEntry{
        uint8_t content_id;
	const unsigned char * data;
};

//Define the data structure to maintain the Content Cache Table
typedef Vector<CCTEntry> contentCacheTable;

class Cache : public Element {

        public:
                Cache();
                ~Cache();

                const char *class_name() const {return "Cache";}
		/*Input 0 -> request or content
		  Output 0 -> request to SRT, 1 -> content back to front R/H*/
                const char *port_count() const {return "1/2";}
                const char *processing() const {return PUSH;}

                int configure(Vector<String>&, ErrorHandler*);

                void push(int, Packet *);
		//Self-defined functions
		bool isFoundContent(uint8_t);
		struct CCTEntry lookUpCCT(uint8_t);
	
	private:
		contentCacheTable my_contentCacheTable;
};

CLICK_ENDDECLS
#endif
