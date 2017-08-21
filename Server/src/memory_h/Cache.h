#ifndef MEMORY_H_CACHE_H_
#define MEMORY_H_CACHE_H_
#include "../data_structs/Map.h"
#include "../data_structs/LinkedList.h"
#include <string>

struct Cache_Resource_Container {
	unsigned int cache_counter;
	char* _value;
	Cache_Resource_Container( char* value ) : cache_counter( 0 ), _value( value ) {}

	friend std::ostream& operator << ( std::ostream& strm, const Cache_Resource_Container& container ) {
		strm << container._value;
		return strm;
	}
};

class Cache {
	typedef unsigned int u_int;
	typedef Linked_List< std::pair< std::string, char* > > list;
public:
	Cache( u_int capacity );
	void add( std::string key, char* value );
	void update();
	bool contains( std::string key );
	char* get( std::string key );
	void decrement_counters();
	void increment_counter ( std::string key );
	bool is_full();
	virtual ~Cache();
private:
	Cache_Resource_Container create_container( char* value );
private:
	u_int _capacity;
	Map< std::string, Cache_Resource_Container > cache_memory;
};

#endif /* MEMORY_H_CACHE_H_ */
