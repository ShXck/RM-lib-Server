#ifndef UTILITY_HPP_
#define UTILITY_HPP_
#include <string>
#include <iostream>
#include <sstream>

namespace util {
	/**
	 * Verifica si el string puede ser entero.
	 * @param a el string.
	 * @return si es entero.
	 */
	bool is_int( const std::string& a );
	/**
	 * Verifica si un string puede ser float.
	 * @param a el string.
	 * @return si es float.
	 */
	bool is_float( const std::string& a );
	/**
	 * Transforma un entero a string.
	 * @param i el entero.
	 * @return el string.
	 */
	std::string itos( int i );
}



#endif /* UTILITY_HPP_ */
