#ifndef MEMORY_H_MEMORYHANDLER_H_
#define MEMORY_H_MEMORYHANDLER_H_
#define CACHE_CAPACITY 5
#include "../data_structs/Map.h"
#include <iostream>
#include <string>
#include "../utility.hpp"
#include "../error_handler.hpp"
#include "../server_h/JSONHandler.h"
#include "../data_structs/LinkedList.h"
#include "Cache.h"

struct RmRef_h {
	int _size;
	char* _value;
	int ref_counter;
	char* client_id;
	RmRef_h( int size, char* value, char* c_id ) : _size( size ), _value( value ), ref_counter( 1 ), client_id( c_id ) {}

	void add_ref() {
		ref_counter++;
	}

	friend std::ostream& operator << ( std::ostream& strm, const RmRef_h& container ) {
		strm << container._value;
		return strm;
	}
};

struct Unused_Ref {
	unsigned int tmp_counter;
	std::string _key;
	Unused_Ref( std::string key ) : tmp_counter( 0 ), _key( key ) {}

	bool operator == ( const Unused_Ref& u_1, const Unused_Ref& u_2 ) {
		if( u_1._key == u_2._key ) {
			return true;
		}
		return false;
	}

	bool operator != ( const Unused_Ref& u_1, const Unused_Ref& u_2 ) {
		if( u_1._key != u_2._key ) {
			return true;
		}
		return false;
	}
}

class Memory_Handler {
public:
	Memory_Handler();
	std::string store_value( std::string key, char* value, char* c_id, int size );
	std::string find_value( std::string key );
	std::string find_value_set( char* data );
	std::string delete_value( std::string key );
	std::string replace_value( std::string key, char* new_val );
	void delete_from( char* key );
	virtual ~Memory_Handler();
private:
	bool is_valid( std::string key );
	RmRef_h create_ref( int size, char* value, char* c_id );
	Unused_Ref create_unused( std::string key );
	void run_garbage_collector();
private:
	Map < std::string, RmRef_h > memory_map;
	Cache _cache;
	Linked_List < Unused_Ref > unused_resources;
};

#endif /* MEMORY_H_MEMORYHANDLER_H_ */
