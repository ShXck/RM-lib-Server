#include "utility.hpp"

namespace util {

	bool is_int( const std::string& a ) {
		if( a.empty() || ( ( !std::isdigit( a[0] ) ) && ( a[0] != '-' ) && ( a[0] != '+' ) ) ) return false;

		char* _p;
		std::strtol( a.c_str(), &_p, 10 );

		return (*_p == 0);
	}

	bool is_float( const std::string& a ) {
		char* end_ptr = 0;
		std::strtod( a.c_str(), &end_ptr );

		if( *end_ptr != '\0' || end_ptr == a.c_str() ) return false;

		return true;
	}

	std::string itos( int i ) {
		return std::to_string( i );
	}

}


