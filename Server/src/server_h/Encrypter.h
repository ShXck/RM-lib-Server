#ifndef SERVER_H_ENCRYPTER_H_
#define SERVER_H_ENCRYPTER_H_
#include <string>
#include <iostream>

class Encrypter {
public:
	Encrypter();
	/**
	 * Encripta y desencripta información.
	 * @param data
	 * @return el mensaje encriptado/desencriptado
	 */
	std::string apply( std::string data );
	virtual ~Encrypter();
};

#endif /* SERVER_H_ENCRYPTER_H_ */
