#include "Cache.h"

Cache::Cache( u_int capacity ): _capacity( capacity ) { }

void Cache::add( std::string key, char* value ) {
	cache_memory.add( key, create_container( value ) );
	cache_memory.display();
}

void Cache::update( ) {

	decrement_counters();

	Node< std::string, Cache_Resource_Container >* _current = cache_memory.head();

	while( _current != nullptr ) {
		if( _current->_data.cache_counter == 0 ) {
			cache_memory.remove( _current->_key );
		}
		_current = _current->_next;
	}
}

void Cache::decrement_counters() {
	for( u_int i = 0; i < cache_memory.size(); i++) {
		Cache_Resource_Container _current = cache_memory.get( i );
		if( _current.cache_counter > 0 ) _current.cache_counter--;
	}
}

void Cache::increment_counter( std::string key ) {
	Cache_Resource_Container _container = cache_memory.get( key );
	_container.cache_counter++;
}

bool Cache::contains( std::string key ) {
	if( cache_memory.contains( key ) ) {
		return true;
	}
	return false;
}

Cache_Resource_Container Cache::create_container( char* value ) {
	Cache_Resource_Container new_container( value );
	return new_container;
}

char* Cache::get( std::string key ) {
	return cache_memory.get( key );
}

bool Cache::is_full() {
	return cache_memory.size() == _capacity;
}

Cache::~Cache() { }

