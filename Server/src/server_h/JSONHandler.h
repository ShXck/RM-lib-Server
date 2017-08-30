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
	static std::string build_msg( bool error, std::string msg );
	static std::string process_deleted( c_char json );
	static std::string build_get_msg( c_char key, c_char value, int size );
	static std::string build_set_msg( Linked_List< char* > keys, Linked_List< char* > values );
	static std::string build_sync_data( c_char key, c_char data, c_char c_id, int size, int instruction );
	static std::string build_check_msg();
	static rapidjson::Value& get_value( c_char json, c_char json_key );
	static Linked_List < char* > process_array( c_char data, c_char arr_key );
	virtual ~JSON_Handler();
};

#endif /* SERVER_H_JSONHANDLER_H_ */
