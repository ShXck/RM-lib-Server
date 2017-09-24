#include "MemoryHandler.h"

Memory_Handler::Memory_Handler() : _cache( CACHE_CAPACITY ), memory_allocated( 0 ), _monitor( memory_allocated, _cache.to_string() ) {
	gbc_handler = std::async( std::launch::async, &Memory_Handler::run_garbage_collector, this );
	_monitor.run();
}

bool Memory_Handler::is_valid( str key ) {
	if( memory_map.contains( key ) ) {
		return false;
	}
	return true;
}

RmRef_h Memory_Handler::create_ref( int size, char* value, char* c_id ) {
	RmRef_h new_ref( size, value, c_id );
	return new_ref;
}

Unused_Ref Memory_Handler::create_unused( str key ) {
	Unused_Ref _unused( key );
	return _unused;
}

str Memory_Handler::store_value( str key, char* value, char* c_id,  int size ) {

	if( is_valid( key ) ) {

		RmRef_h new_ref = create_ref( size, value, c_id );

		memory_map.add( key, new_ref );

		if( !_cache.is_full() ) {
			_cache.add( key, value, new_ref.ref_counter );
			_monitor.update( 1, _cache.to_string() );
		}

		memory_map.display();

		memory_allocated += memory_map.node_size();
		_monitor.update( 0, std::to_string( memory_allocated ) );

		return JSON_Handler::build_msg( false, error::key_is_valid() );
	}
	return JSON_Handler::build_msg( true, error::key_used_err() );
}

str Memory_Handler::find_value( str key ) {
	if( _cache.contains( key ) ) {
		RmRef_h& _container = memory_map.get( key );
		_container.ref_counter++;
		_cache.increment_counter( key );
		return JSON_Handler::build_get_msg( key.c_str(), _cache.get( key ), _container._size );
	}
	if( memory_map.contains( key ) ) {
		RmRef_h& _container = memory_map.get( key );
		_container.ref_counter++;
		return JSON_Handler::build_get_msg( key.c_str(), _container._value, _container._size );
	}
	return JSON_Handler::build_msg( true, error::key_not_found_err() );
}

str Memory_Handler::find_value_set( char* data ) {

	Linked_List< char* > keys_list = JSON_Handler::process_array( data, "keys" );
	Linked_List < char* > value_list;

	for( int i = 0; i < keys_list.size(); i++ ) {
		RmRef_h& _ref = memory_map.get( keys_list.get( i ) );
		value_list.add( _ref._value );
		_ref.ref_counter++;
	}
	return JSON_Handler::build_set_msg( keys_list, value_list );
}

str Memory_Handler::delete_value( str key ) {
	if( memory_map.contains( key ) ) {
		memory_map.remove( key );
		memory_map.display();
		memory_allocated -= memory_map.node_size();
		_monitor.update( 0, std::to_string( memory_allocated ) );
		return JSON_Handler::build_msg( false, error::key_is_valid() );
	}
	return JSON_Handler::build_msg( true, error::key_not_found_err() );
}

str Memory_Handler::replace_value( str key, char* new_val ) {
	if( _cache.contains( key ) ) {
		_cache.update_value( key, new_val );
		RmRef_h& r = memory_map.get( key );
		r._value = new_val;
		r.ref_counter++;
		_monitor.update( 1, _cache.to_string() );
		return JSON_Handler::build_msg( false, error::key_is_valid() );
	}
	if( memory_map.contains( key ) ) {
		RmRef_h& _ref = memory_map.get( key );
		_ref._value = new_val;
		_ref.ref_counter++;
		memory_map.display();
		return JSON_Handler::build_msg( false, error::key_is_valid() );
	}
	return JSON_Handler::build_msg( true, error::key_not_found_err() );
}

void Memory_Handler::sync_data( str key, char* data, char* c_id, int size, int instruction ) {
	switch ( instruction ) {
		case 1: {
			store_value( key, data, c_id, size );
			break;
		}
		case 3: {
			delete_value( key );
			break;
		}
		case 5: {
			replace_value( key, data );
			break;
		}
		case 6: {
			delete_from( c_id );
			break;
		}
		default: {
			std::cout << "SYNCHRONIZATION NOT ALLOWED FOR THIS ACTION" << std::endl;
			break;
		}
	}
}

void Memory_Handler::delete_from( char* key ) {
	Node< str, RmRef_h >* _current = memory_map.head();
	while( _current != nullptr ) {
		if( strcmp( _current->_data.client_id, key) == 0 ) {
			memory_map.remove( _current->_key );
			memory_allocated -= memory_map.node_size();
			_monitor.update( 0, std::to_string( memory_allocated ) );
		}
		_current = _current->_next;
	}
	memory_map.display();
}

void Memory_Handler::run_garbage_collector() {

	while( true ) {

		std::this_thread::sleep_for( std::chrono::seconds( CACHE_PERIOD ) );

		std::cout << "GBC Started" << std::endl;

		_cache.update();

		for( int i = 0; i < memory_map.size(); i++ ) {
			RmRef_h& _ref = memory_map.get( i );
			if( _ref.ref_counter > 0 ) _ref.ref_counter--;
		}

		Node< str, RmRef_h >* curr_ref = memory_map.head();

		while( curr_ref != nullptr ) {
			Unused_Ref u_ref = create_unused( curr_ref->_key );
			if( unused_resources.contains( u_ref ) ) {
				if( memory_map.get( u_ref._key ).ref_counter > 0 ) unused_resources.remove( u_ref );
				else {
					Unused_Ref& _ref = unused_resources.get( unused_resources.get_index_of( u_ref ) );
					if( _ref.tmp_counter >= 3 ) {
						memory_map.remove( u_ref._key );
						unused_resources.remove( u_ref );
					} else {
						_ref.tmp_counter++;
					}
				}
			} else if( curr_ref->_data.ref_counter == 0 && !unused_resources.contains( u_ref ) ) {
				unused_resources.add( u_ref );
			} else {
				if( (!_cache.is_full() ) && ( curr_ref->_data.ref_counter >= 5 ) && ( !_cache.contains( curr_ref->_key ) ) ) {
					_cache.add( curr_ref->_key, curr_ref->_data._value, curr_ref->_data.ref_counter );
				}
			}
			curr_ref = curr_ref->_next;
		}

		_monitor.update( 1, _cache.to_string() );
	}
}

Memory_Handler::~Memory_Handler() { }

