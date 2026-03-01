#ifndef JSON_C_SERIALIZER_H
#define JSON_C_SERIALIZER_H


#include <json.h>


typedef struct
{
	char* key;
	int   type;
	int   size;
	int   level;
} jcs_json_meta_t;


void jcs_hw();

int jcs_json_to_byte();
int jcs_byte_to_json();
int jcs_byte_to_struct();
int jcs_json_to_struct();


#endif // JSON_C_SERIALIZER_H