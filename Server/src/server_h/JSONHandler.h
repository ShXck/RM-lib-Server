#ifndef SERVER_H_JSONHANDLER_H_
#define SERVER_H_JSONHANDLER_H_
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include "../data_structs/LinkedList.h"
#include "../memory_h/MemoryHandler.h"

typedef rapidjson::Document::AllocatorType& Alloc;
typedef rapidjson::Writer<rapidjson::StringBuffer> Writer;
typedef const char* c_char;

class JSON_Handler {

public:
	JSON_Handler();
	/**
	 * Construye un JSON con un mensaje de error.
	 * @param error si hay error o no.
	 * @param msg el mensaje.
	 * @return el JSON con el mensaje.
	 */
	static std::string build_msg( bool error, std::string msg );
	/**
	 * Construye un JSON con la información del elemento requerido.
	 * @param key la llave del elemento.
	 * @param value el valor.
	 * @param size el tamaño del elemento.
	 * @return el JSON con el mensaje.
	 */
	static std::string process_deleted( c_char json );
	/**
	 * Construye un JSON con un conjunto de llaves.
	 * @param keys las llaves.
	 * @param values los valores.
	 * @return el JSON con el mensaje.
	 */
	static std::string build_get_msg( c_char key, c_char value, int size );
	/**
	 * Construye un JSON con un conjunto de llaves.
	 * @param keys las llaves.
	 * @param values los valores.
	 * @return el JSON con el mensaje.
	 */
	static std::string build_set_msg( Linked_List< char* > keys, Linked_List< char* > values );
	/**
	 * Construye un JSON con la información de sincronización.
	 * @param key la llave del elemento.
	 * @param data la información.
	 * @param c_id la id del usuario.
	 * @param size el tamaño del elemento.
	 * @param instruction la acción a realizar.
	 * @return
	 */
	static std::string build_sync_data( c_char key, c_char data, c_char c_id, int size, int instruction );
	/**
	 * Construye un mensaje de verificación.
	 * @return el JSON con el mensaje.
	 */
	static std::string build_check_msg();
	/**
	 * @param json el mensaje json.
	 * @param json_key la llave que se quiere acceder.
	 * @return el valor de la llave.
	 */
	static rapidjson::Value& get_value( c_char json, c_char json_key );
	/**
	 * Procesa un conjunto de JSONArrays.
	 * @param data la información.
	 * @param arr_key el arreglo de llaves.
	 * @return una lista con la información.
	 */
	static Linked_List < char* > process_array( c_char data, c_char arr_key );
	virtual ~JSON_Handler();
};

#endif /* SERVER_H_JSONHANDLER_H_ */
