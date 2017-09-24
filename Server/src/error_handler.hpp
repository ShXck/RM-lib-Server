#ifndef ERROR_HANDLER_HPP_
#define ERROR_HANDLER_HPP_
#include <string>

namespace error {

	/**
	 * @return mensaje de llave utilizada.
	 */
	std::string key_used_err();
	/**
	 * @return mensaje de llave no encontrada.
	 */
	std::string key_not_found_err();
	/**
	 * @return mensaje de llave válida.
	 */
	std::string key_is_valid();
	/**
	 * @return mensaje de llave encontrada.
	 */
	std::string key_found();
	/**
	 * @return mensaje de error de parseo de archivo.
	 */
	std::string doc_parse_err();
}



#endif /* ERROR_HANDLER_HPP_ */
