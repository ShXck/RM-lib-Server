#ifndef UTILITY_HPP_
#define UTILITY_HPP_
#include <string>
#include <iostream>
#include <sstream>

namespace util {
	bool is_int( const std::string& a );
	bool is_float( const std::string& a );
	std::string itos( int i );
}



#endif /* UTILITY_HPP_ */
