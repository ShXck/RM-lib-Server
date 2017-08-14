#ifndef SERVER_H_JSONHANDLER_H_
#define SERVER_H_JSONHANDLER_H_

#define KEY_ERR "Key is already in use"
#define NEW_SUCCS "New value created successfully"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>

class JSON_Handler {
	typedef rapidjson::Document::AllocatorType& Alloc;
	typedef rapidjson::Writer<rapidjson::StringBuffer> Writer;
public:
	JSON_Handler();
	static std::string build_msg( bool error, std::string msg );
	static std::string process_deleted( const char* json );
	static std::string build_get_msg( const char* key, std::string value, int size );
	static rapidjson::Value& get_value( const char* json, const char* json_key );
	virtual ~JSON_Handler();
};

#endif /* SERVER_H_JSONHANDLER_H_ */
