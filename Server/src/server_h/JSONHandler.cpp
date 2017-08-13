#include "JSONHandler.h"

JSON_Handler::JSON_Handler() { }

std::string JSON_Handler::build_msg( bool error, std::string msg ) {

	rapidjson::Document _doc;
	_doc.SetObject();

	Alloc _alloc = _doc.GetAllocator();

	if( error ) {
		_doc.AddMember( "error", true, _alloc );
	} else  {
		_doc.AddMember( "error", false, _alloc );
	}

	{
		rapidjson::Value str_msg;
		str_msg.SetString( msg.c_str(), _alloc );
		_doc.AddMember( "msg", str_msg, _alloc );
	}

	_doc.AddMember( "instruction", 0, _alloc );

	rapidjson::StringBuffer str_buffer;
	Writer _writer( str_buffer );
	_doc.Accept( _writer );

	return str_buffer.GetString();

}

std::string JSON_Handler::build_get_msg( const char* key, std::string value, int size ) {

	rapidjson::Document _doc;
	_doc.SetObject();
	Alloc _alloc = _doc.GetAllocator();

	//std::string* casted_str = static_cast< std::string* > ( value );

	{
		rapidjson::Value str_key;
		str_key.SetString( key, _alloc );
		_doc.AddMember( "key", str_key, _alloc );
	}

	{
		rapidjson::Value value_str;
		value_str.SetString( value.c_str(), _alloc );
		_doc.AddMember( "value", value_str, _alloc );
	}

	_doc.AddMember( "size", size, _alloc );
	_doc.AddMember( "instruction", 2, _alloc );

	rapidjson::StringBuffer str_buffer;
	Writer _writer( str_buffer );
	_doc.Accept( _writer );

	return str_buffer.GetString();
}

rapidjson::Value& JSON_Handler::get_value( const char* json, const char* json_key ) {

	rapidjson::Document _doc;
	_doc.Parse( json );

	Alloc _alloc = _doc.GetAllocator();

	rapidjson::Value str_key;
	str_key.SetString( json_key, _alloc );

	rapidjson::Value& _val = _doc[ str_key ];

	return _val;
}

JSON_Handler::~JSON_Handler() { }

