#include "MemoryHandler.h"

Memory_Handler::Memory_Handler() {
	// TODO Auto-generated constructor stub

}

bool Memory_Handler::is_valid( std::string key ) {
	if( memory_map.contains( key ) ) {
		return false;
	}
	return true;
}

std::string Memory_Handler::store_value( std::string key, std::string value, int size ) {

	if( is_valid( key ) ) {

		Ref_Container *new_container = new Ref_Container( size, value );

		memory_map.add( key, new_container );

		memory_map.display();

		return JSON_Handler::build_msg( false, error::key_is_valid() );
	}
	return JSON_Handler::build_msg( true, error::key_used_err() );
}

std::string Memory_Handler::find_value( std::string key ) {
	if( memory_map.contains( key ) ) {
		Ref_Container* _container = memory_map.get( key );
		return JSON_Handler::build_get_msg( key.c_str(), _container->_value, _container->_size );
	}
	return JSON_Handler::build_msg( true, error::key_not_found_err() );
}

std::string Memory_Handler::delete_value( std::string key ) {
	if( memory_map.contains( key ) ) {
		memory_map.remove( key );
		memory_map.display();
		return JSON_Handler::build_msg( false, error::key_is_valid() );
	}
	return JSON_Handler::build_msg( true, error::key_not_found_err() );
}

Memory_Handler::~Memory_Handler() { }

