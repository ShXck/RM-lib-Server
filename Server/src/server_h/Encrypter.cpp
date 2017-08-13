#include "Encrypter.h"

Encrypter::Encrypter() { }

std::string Encrypter::apply( std::string data ) {
	char _key[3] = { 'S', 'K', 'F' };
	std::string _result = data;

	for( int i = 0; i < data.size(); i++ ) {
		_result[ i ] = data[ i ] ^ _key[ i % ( sizeof( _key ) / sizeof( char ) )];
	}
	return _result;
}

Encrypter::~Encrypter() { }

