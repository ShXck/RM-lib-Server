#ifndef MEMORY_H_MEMORYHANDLER_H_
#define MEMORY_H_MEMORYHANDLER_H_
#define CACHE_CAPACITY 5
#define CACHE_PERIOD 120
#include "../data_structs/Map.h"
#include <iostream>
#include <string>
#include "../utility.hpp"
#include "../error_handler.hpp"
#include "../server_h/JSONHandler.h"
#include "../data_structs/LinkedList.h"
#include "Cache.h"
#include <chrono>
#include <thread>
#include <future>

struct RmRef_h {
	int _size;
	char* _value;
	int ref_counter;
	char* client_id;
	RmRef_h( int size, char* value, char* c_id ) : _size( size ), _value( value ), ref_counter( 4 ), client_id( c_id ) {}

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

	bool operator == ( const Unused_Ref& u_ref ) {
		if( u_ref._key == _key ) {
			return true;
		}
		return false;
	}

	bool operator != ( const Unused_Ref& u_ref ) {
		if( u_ref._key != _key ) {
			return true;
		}
		return false;
	}

	friend std::ostream& operator << ( std::ostream& strm, const Unused_Ref& u_ref ) {
		strm << u_ref._key;
		return strm;
	}
};

typedef std::string str;

class Memory_Handler {
public:
	Memory_Handler();
	str store_value( str key, char* value, char* c_id, int size );
	str find_value( str key );
	str find_value_set( char* data );
	str delete_value( str key );
	str replace_value( str key, char* new_val );
	void sync_data( str key, char* data, char* c_id, int size, int instruction );
	void delete_from( char* key );
	virtual ~Memory_Handler();
private:
	bool is_valid( str key );
	RmRef_h create_ref( int size, char* value, char* c_id );
	Unused_Ref create_unused( str key );
	void run_garbage_collector();
private:
	Map < str, RmRef_h > memory_map;
	Cache _cache;
	Linked_List < Unused_Ref > unused_resources;
	std::future< void > gbc_handler;
};

#endif /* MEMORY_H_MEMORYHANDLER_H_ */
