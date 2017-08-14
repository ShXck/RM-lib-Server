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

RmRef_h Memory_Handler::create_ref( int size, std::string value ) {
	RmRef_h new_ref( size, value );
	return new_ref;
}

std::string Memory_Handler::store_value( std::string key, std::string value, int size ) {

	if( is_valid( key ) ) {

		RmRef_h new_ref = create_ref( size, value );

		memory_map.add( key, new_ref );

		memory_map.display();

		return JSON_Handler::build_msg( false, error::key_is_valid() );
	}
	return JSON_Handler::build_msg( true, error::key_used_err() );
}

std::string Memory_Handler::find_value( std::string key ) {
	if( memory_map.contains( key ) ) {
		RmRef_h _container = memory_map.get( key );
		_container.add_ref();
		return JSON_Handler::build_get_msg( key.c_str(), _container._value, _container._size );
	}
	return JSON_Handler::build_msg( true, error::key_not_found_err() );
}

std::string Memory_Handler::find_value_set( std::string data ) {

	Linked_List< std::string > keys_list = JSON_Handler::process_array( data.c_str(), "keys" );
	Linked_List < std::string > value_list;

	for( int i = 0; i < keys_list.size(); i++ ) {
		value_list.add( memory_map.get( keys_list.get( i ) )._value );
	}
	return JSON_Handler::build_set_msg( keys_list, value_list );
}

std::string Memory_Handler::delete_value( std::string key ) {
	if( memory_map.contains( key ) ) {
		memory_map.remove( key );
		return JSON_Handler::build_msg( false, error::key_is_valid() );
	}
	return JSON_Handler::build_msg( true, error::key_not_found_err() );
}

Memory_Handler::~Memory_Handler() { }

