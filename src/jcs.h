#ifndef JSON_C_SERIALIZER_H
#define JSON_C_SERIALIZER_H


#include <json.h>


#ifndef JCS_ENDIAN_LIL
#define JCS_ENDIAN_LIL 0
#endif

#ifndef JCS_ENDIAN_BIG
#define JCS_ENDIAN_BIG 1
#endif


typedef enum
{
    JCS_OK = 0,
    JCS_ERR_TO_BYTE_BAD_TOK,
    JCS_ERR_TO_BYTE_BAD_JSON,
    JCS_ERR_TO_BYTE_TOK_PARSE,
    JCS_ERR_TO_BYTE_HDL_OBJ_BAD_KEY,
    JCS_ERR_TO_BYTE_HDL_TYP_BAD_TYPE,
    JCS_ERR_TO_BYTE_HDL_ARR_BAD_TYPE,
    JCS_ERR_TO_BYTE_MEMCPY_LEN_ARG,
    JCS_ERR_TO_BYTE_MEMCPY_LEN_DBL,
    JCS_ERR_TO_BYTE_MEMCPY_LEN_INT,
    JCS_ERR_TO_JSON_HDL_OBJ_BYTE_LIM,
    JCS_ERR_TO_JSON_HDL_ARR_BAD_TYPE,
    JCS_ERR_TO_JSON_MEMCPY_LEN_ARG,
    JCS_ERR_TO_JSON_MEMCPY_LEN_DBL,
    JCS_ERR_TO_JSON_MEMCPY_LEN_INT,

} jcs_ret_t;

typedef struct
{
    const char* key;
    const int   type;
    const int   size;
    const int   level;
} jcs_meta_t;

typedef struct
{
    const jcs_meta_t* meta;     // meta data array for json object
    const int         meta_lim; // meta data array count/limit
    int               meta_i;   // meta data array index
    uint8_t*          byte;     // byte array of serialized json object
    int               byte_lim; // byte array count/limit
    int               byte_i;   // byte array index
    char*             json;     // json object string
    const int         end_sys;  // system endianess
    const int         end_byte; // byte array endianess
} jcs_arg_t;


int jcs_json_to_byte( jcs_arg_t* arg );
int jcs_byte_to_json( jcs_arg_t* arg );
int jcs_byte_to_struct();
int jcs_json_to_struct();


#endif // JSON_C_SERIALIZER_H