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

std::string JSON_Handler::build_get_msg( c_char key, c_char value, int size ) {

	rapidjson::Document _doc;
	_doc.SetObject();
	Alloc _alloc = _doc.GetAllocator();

	{
		rapidjson::Value str_key;
		str_key.SetString( key, _alloc );
		_doc.AddMember( "key", str_key, _alloc );
	}

	{
		rapidjson::Value value_str;
		value_str.SetString( value, _alloc );
		_doc.AddMember( "value", value_str, _alloc );
	}

	_doc.AddMember( "size", size, _alloc );
	_doc.AddMember( "instruction", 2, _alloc );

	rapidjson::StringBuffer str_buffer;
	Writer _writer( str_buffer );
	_doc.Accept( _writer );

	return str_buffer.GetString();
}

std::string JSON_Handler::build_set_msg( Linked_List< char* > keys, Linked_List< char* > values ) {

	rapidjson::Document _doc;
	_doc.SetObject();
	Alloc _alloc = _doc.GetAllocator();

	rapidjson::Value val_array( rapidjson::kArrayType );

	for( int i = 0; i < keys.size(); i++ ) {
		rapidjson::Value _pair( rapidjson::kObjectType );

		rapidjson::Value str_key;
		str_key.SetString( keys.get( i ), _alloc );

		rapidjson::Value str_value;
		str_value.SetString( values.get( i ), _alloc );

		_pair.AddMember( "key", str_key, _alloc );
		_pair.AddMember( "value", str_value, _alloc );

		val_array.PushBack( _pair, _alloc );
	}
	_doc.AddMember( "value_set", val_array, _alloc );
	_doc.AddMember( "instruction", 4, _alloc );

	rapidjson::StringBuffer str_buffer;
	Writer _writer( str_buffer );
	_doc.Accept( _writer );

	return str_buffer.GetString();
}

std::string JSON_Handler::build_sync_data( c_char key, c_char data, c_char c_id, int size, int instruction ) {

	rapidjson::Document _doc;
	_doc.SetObject();
	Alloc _alloc = _doc.GetAllocator();

	{
		rapidjson::Value str_key;
		str_key.SetString( key, _alloc );
		_doc.AddMember( "key", str_key, _alloc );
	}

	{
		rapidjson::Value value_str;
		value_str.SetString( data, _alloc );
		_doc.AddMember( "value", value_str, _alloc );
	}

	{
		rapidjson::Value client_str;
		client_str.SetString( c_id, _alloc );
		_doc.AddMember( "client_id", client_str, _alloc );
	}

	_doc.AddMember( "instruction", instruction, _alloc );
	_doc.AddMember( "size", size, _alloc );

	rapidjson::StringBuffer str_buffer;
	Writer _writer( str_buffer );
	_doc.Accept( _writer );

	return str_buffer.GetString();
}

std::string JSON_Handler::build_check_msg() {

	rapidjson::Document _doc;
	_doc.SetObject();
	Alloc _alloc = _doc.GetAllocator();

	_doc.AddMember( "instruction", 8, _alloc );
	_doc.AddMember( "key", "NONE", _alloc );

	rapidjson::StringBuffer str_buffer;
	Writer _writer( str_buffer );
	_doc.Accept( _writer );

	return str_buffer.GetString();
}

rapidjson::Value& JSON_Handler::get_value( c_char json, c_char json_key ) {

	rapidjson::Document _doc;
	_doc.Parse( json );

	Alloc _alloc = _doc.GetAllocator();

	rapidjson::Value str_key;
	str_key.SetString( json_key, _alloc );

	rapidjson::Value& _val = _doc[ str_key ];

	return _val;
}

Linked_List < char* > JSON_Handler::process_array( c_char data, c_char arr_key ) {

	rapidjson::Document _doc;
	Alloc _alloc = _doc.GetAllocator();

	Linked_List< char* > keys_list;

	if( !(_doc.Parse<0>( data ).HasParseError() ) ) {
		rapidjson::Value str_key;
		str_key.SetString( arr_key, _alloc );
		const rapidjson::Value& _keys = _doc[ str_key ];

		for( rapidjson::SizeType i = 0; i < _keys.Size(); i++ ) {
			const rapidjson::Value& _key = _keys[ i ];
			keys_list.add( strdup( _key.GetString() ) );
		}
		return keys_list;
	}
	return keys_list;
}



JSON_Handler::~JSON_Handler() { }

