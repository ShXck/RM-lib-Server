#ifndef MEMORY_H_MEMORYHANDLER_H_
#define MEMORY_H_MEMORYHANDLER_H_
#include "../data_structs/Map.h"
#include <iostream>
#include <string>
#include "../utility.hpp"
#include "../error_handler.hpp"
#include "../server_h/JSONHandler.h"

struct Ref_Container {
	int _size;
	std::string _value;
	int ref_counter;
	Ref_Container( int size, std::string value ) : _size( size ), _value( value ), ref_counter( 0 ) {}

	void add_ref() {
		ref_counter++;
	}

	friend std::ostream& operator << ( std::ostream& strm, const Ref_Container& container ) {
		strm << container._value;
		return strm;
	}
};

class Memory_Handler {
public:
	Memory_Handler();
	std::string store_value( std::string key, std::string value, int size );
	std::string find_value( std::string key );
	std::string delete_value( std::string key );
	virtual ~Memory_Handler();
private:
	bool is_valid( std::string key );
private:
	Map < std::string, Ref_Container* > memory_map;
};

#endif /* MEMORY_H_MEMORYHANDLER_H_ */
