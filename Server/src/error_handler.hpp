#ifndef ERROR_HANDLER_HPP_
#define ERROR_HANDLER_HPP_
#include <string>

namespace error {

	std::string key_used_err();
	std::string key_not_found_err();
	std::string key_is_valid();
	std::string key_found();
	std::string doc_parse_err();
}



#endif /* ERROR_HANDLER_HPP_ */
