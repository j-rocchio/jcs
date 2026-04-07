#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "jcs.h"
#include "config.h"


static int jcs_json_to_byte_hdl_obj ( jcs_arg_t* arg, json_object* obj, bool nullify );
static int jcs_json_to_byte_hdl_arr ( jcs_arg_t* arg, json_object* obj, bool nullify );
static int jcs_json_to_byte_hdl_type( jcs_arg_t* arg, json_object* obj, bool nullify );

static int jcs_byte_to_json_hdl_obj ( jcs_arg_t* arg, json_object* obj );
static int jcs_byte_to_json_hdl_arr ( jcs_arg_t* arg, json_object* obj );
static int jcs_byte_to_json_hdl_type( jcs_arg_t* arg, json_object* obj );

static void jcs_swap( void* val );

static int jcs_copy_to_byte( jcs_arg_t* arg, void*      src, int len );
static int jcs_copy_to_json( void*      dst, jcs_arg_t* arg, int len );


int jcs_json_to_byte( jcs_arg_t* arg )
{
    int ret = 0;
    json_object*  obj = NULL;
    json_tokener* tok = json_tokener_new();

    if( tok == NULL ) return -JCS_ERR_TO_BYTE_BAD_TOK;

    if( arg->json != NULL ) obj = json_tokener_parse_ex( tok, arg->json, strlen(arg->json) );
    else return -JCS_ERR_TO_BYTE_BAD_JSON;

    if( obj != NULL ) ret = jcs_json_to_byte_hdl_obj( arg, obj, false );
    else return -JCS_ERR_TO_BYTE_TOK_PARSE;

    return ret;
}

int jcs_json_to_byte_hdl_obj( jcs_arg_t* arg, json_object* obj, bool nullify )
{
    int ret = 0;

    arg->meta_i++;

    json_object_object_foreach( obj, key, val )
    {
        printf( "meta[%d].key is: \"%s\"; key is: \"%s\"; ", arg->meta_i, arg->meta[arg->meta_i].key, key );

        if( strcmp( key, arg->meta[arg->meta_i].key ) == 0 ) ret = jcs_json_to_byte_hdl_type( arg, val, nullify );
        else return -JCS_ERR_TO_BYTE_HDL_OBJ_BAD_KEY;

        if( ret != JCS_OK ) return ret;
    }

    return ret;
}

int jcs_json_to_byte_hdl_arr( jcs_arg_t* arg, json_object* obj, bool nullify )
{
    int ret = 0;
    uint64_t len = 0;

    // get array length
    if( nullify == false ) len  = json_object_array_length( obj );

    // copy array length to byte array
    jcs_copy_to_byte( arg, &len, arg->meta[arg->meta_i].size );
    arg->meta_i--;

    // save the array heirarchy level
    int arr_level = arg->meta[arg->meta_i].level;

    if( nullify == false )
    {
        for( int i = 0; i < (int)len; i++ )
        {
            int meta_i_arr = arg->meta_i;

            arg->meta_i++;

            json_object* elm = json_object_array_get_idx( obj, i );

            // printf( "arg->meta_i is %d \n", arg->meta_i );
            // printf( "arg->meta[arg->meta_i].type is %d \n", arg->meta[arg->meta_i].type );
            // printf( "json_object_get_type( elm ) is %d \n", json_object_get_type( elm ) );

            if( (int)json_object_get_type( elm ) != arg->meta[arg->meta_i].type ) return -JCS_ERR_TO_BYTE_HDL_ARR_BAD_TYPE;

            ret = jcs_json_to_byte_hdl_type( arg, elm, nullify );
            if( ret != JCS_OK ) return ret;

            arg->meta_i = meta_i_arr;

            // printf( "arg->meta_i is %d \n", arg->meta_i );
        }
    }

    // printf( "done parsing array \n" );

    // handle nested arrays by moving meta data index to parent array
    if( arg->meta[arg->meta_i-1].type == json_type_array )
    {
        // printf( "going backward \n" );
        arg->meta_i--;
    }
    // done parsing array/nested array; find next meta data index by check the level
    else
    {
        // printf( "going forward \n" );
        arg->meta_i++;

        for( ; arg->meta_i < arg->meta_lim; arg->meta_i++ )
        {
            // printf( "arg->meta_i is %d \n", arg->meta_i ); fflush( stdout );
            if( arg->meta[arg->meta_i].level == arr_level ) break;
        }
    }

    return ret;
}

int jcs_json_to_byte_hdl_type( jcs_arg_t* arg, json_object* obj, bool nullify )
{
    int ret = 0;
    int type = json_object_get_type( obj );

    if( type != arg->meta[arg->meta_i].type
    &&  type != json_type_null ) return -JCS_ERR_TO_BYTE_HDL_TYP_BAD_TYPE;

    if( nullify == true ) type = json_type_null;

    switch( type )
    {
        case json_type_null:
        {
            switch( arg->meta[arg->meta_i].type )
            {
                case json_type_array:
                {
                    printf( "type is: \"null array\" \n" );

                    ret = jcs_json_to_byte_hdl_arr( arg, obj, true );
                }
                break;
                case json_type_object:
                {
                    printf( "type is: \"null object\" \n" );

                    ret = jcs_json_to_byte_hdl_obj( arg, obj, true );
                }
                break;
                default:
                {
                    arg->byte_i += arg->meta[arg->meta_i].size;
                    arg->meta_i += 1;

                    printf( "type is: \"null\"; byte_i is %d \n", arg->byte_i );
                }
                break;
            }
        }
        break;
        case json_type_boolean:
        {

            int64_t val = json_object_get_boolean( obj );
            ret = jcs_copy_to_byte( arg, &val, arg->meta[arg->meta_i].size  );

            printf( "type is: \"boolean\"; val is: %ld; byte_i is %d \n", val, arg->byte_i );
        }
        break;
        case json_type_double:
        {
            double val = json_object_get_double( obj );
            ret = jcs_copy_to_byte( arg, &val, arg->meta[arg->meta_i].size  );

            printf( "type is: \"double\"; val is: %f; byte_i is %d \n", val, arg->byte_i );
        }
        break;
        case json_type_int:
        {
            int64_t val = json_object_get_int64( obj );
            ret = jcs_copy_to_byte( arg, &val, arg->meta[arg->meta_i].size  );

            printf( "type is: \"integer\"; val is: %ld; byte_i is %d \n", val, arg->byte_i );
        }
        break;
        case json_type_string:
        {
            char* val = (char*)json_object_get_string( obj );
            ret = jcs_copy_to_byte( arg, val, strlen(val) );

            printf( "type is: \"string\"; val is: \"%s\"; byte_i is %d \n", val, arg->byte_i );
        }
        break;
        case json_type_object:
        {
            printf( "type is: \"object\" \n" );

            ret = jcs_json_to_byte_hdl_obj( arg, obj, nullify );
        }
        break;
        case json_type_array:
        {
            printf( "type is: \"array\" \n" );

            ret = jcs_json_to_byte_hdl_arr( arg, obj, nullify );
        }
        break;
    }

    return ret;
}

int jcs_byte_to_json( jcs_arg_t* arg )
{
    int ret = 0;

    arg->meta_i = 0;
    arg->byte_i = 0;

    json_object* obj = json_object_new_object();

    jcs_byte_to_json_hdl_obj( arg, obj );

    return ret;
}

int jcs_byte_to_json_hdl_obj( jcs_arg_t* arg, json_object* obj )
{
    int ret = 0;
    int obj_level = arg->meta[arg->meta_i].level;

    for( arg->meta_i++; arg->meta_i < arg->meta_lim; )
    {
        if( arg->meta[arg->meta_i].level == obj_level ) break;
        if( arg->byte_i >= arg->byte_lim ) return -JCS_ERR_TO_JSON_HDL_OBJ_BYTE_LIM;

        ret = jcs_byte_to_json_hdl_type( arg, obj );
    }

    return ret;
}

int jcs_byte_to_json_hdl_arr( jcs_arg_t* arg, json_object* obj )
{
    int ret = 0;

    return ret;
}

int jcs_byte_to_json_hdl_type( jcs_arg_t* arg, json_object* obj )
{
    int ret = 0;

    switch( arg->meta[arg->meta_i].type )
    {
        case json_type_boolean:
        {
            int64_t val = 0;
            jcs_copy_to_json( &val, arg, arg->meta[arg->meta_i].size );
            json_object* val_obj = json_object_new_boolean( val );
            json_object_object_add( obj, arg->meta[arg->meta_i].key, val_obj );

            printf( "type is: \"boolean\"; val is: %ld; byte_i is %d \n", val, arg->byte_i );
        }
        break;
        case json_type_double:
        {
            double val = 0;
            jcs_copy_to_json( &val, arg, arg->meta[arg->meta_i].size );
            json_object* val_obj = json_object_new_double( val );
            json_object_object_add( obj, arg->meta[arg->meta_i].key, val_obj);

            printf( "type is: \"double\"; val is: %f; byte_i is %d \n", val, arg->byte_i );
        }
        break;
        case json_type_int:
        {
            int64_t val = 0;
            jcs_copy_to_json( &val, arg, arg->meta[arg->meta_i].size );
            json_object* val_obj = json_object_new_int64( val );
            json_object_object_add( obj, arg->meta[arg->meta_i].key, val_obj);

            printf( "type is: \"integer\"; val is: %ld; byte_i is %d \n", val, arg->byte_i );
        }
        break;
        case json_type_string:
        {
            char* val = &arg->byte[arg->byte_i];
            jcs_copy_to_json( val, arg, arg->meta[arg->meta_i].size );
            json_object* val_obj = json_object_new_string_len( val, arg->meta[arg->meta_i].size );
            json_object_object_add( obj, arg->meta[arg->meta_i].key, val_obj);

            printf( "type is: \"string\"; val is: \"%s\"; byte_i is %d \n", val, arg->byte_i );
        }
        break;
        case json_type_object:
        {
            const char* key = arg->meta[arg->meta_i].key;
            json_object* val_obj = json_object_new_object();
            jcs_byte_to_json_hdl_obj( arg, val_obj );
            json_object_object_add( obj, key, val_obj);

            printf( "type is: \"object\" \n" );
        }
        break;
        case json_type_array:
        {
            printf( "type is: \"array\" \n" );
        }
        break;
        default: return -JCS_ERR_TO_JSON_HDL_ARR_BAD_TYPE;
    }

    return ret;
}

int jcs_byte_to_struct()
{
    int ret = 0;

    return ret;
}

int jcs_json_to_struct()
{
    int ret = 0;

    return ret;
}

void jcs_swap( void* val )
{
    uint64_t tmp = 0;
    memcpy( &tmp, val, 8 );
    *((uint64_t*)tmp) = ( ( *((uint64_t*)tmp) <<  8 ) & 0xFF00FF00FF00FF00ULL ) | ( ( *((uint64_t*)tmp) >>  8 ) & 0x00FF00FF00FF00FFULL );
    *((uint64_t*)tmp) = ( ( *((uint64_t*)tmp) << 16 ) & 0xFFFF0000FFFF0000ULL ) | ( ( *((uint64_t*)tmp) >> 16 ) & 0x0000FFFF0000FFFFULL );
    *((uint64_t*)tmp) =   ( *((uint64_t*)tmp) << 32 )                           |   ( *((uint64_t*)tmp) >> 32 );
    memcpy( val, &tmp, 8 );
}

int jcs_copy_to_byte( jcs_arg_t* arg, void* src, int len )
{
    if( arg->meta[arg->meta_i].type == json_type_boolean
    ||  arg->meta[arg->meta_i].type == json_type_double
    ||  arg->meta[arg->meta_i].type == json_type_int )
    {
        if( len != 8 &&   arg->meta[arg->meta_i].type == json_type_double )    return -JCS_ERR_TO_BYTE_MEMCPY_LEN_DBL;
        if( len  > 8 && ( arg->meta[arg->meta_i].type == json_type_int
        ||                arg->meta[arg->meta_i].type == json_type_boolean ) ) return -JCS_ERR_TO_BYTE_MEMCPY_LEN_INT;

        if( JCS_ENDIAN_LIL == arg->end_sys )
        {
            // apply the sign bit
            uint8_t sign = ((uint8_t*)src)[7] & 0x80;
            if( arg->meta[arg->meta_i].type == json_type_int) ((uint8_t*)src)[len] |= sign;

            // copy to byte array
            if( JCS_ENDIAN_LIL == arg->end_byte ) memcpy( &arg->byte[arg->byte_i], src, len );
            else
            {
                jcs_swap( src );
                memcpy( &arg->byte[arg->byte_i], src+8-len, len );
            }
        }
        else if( JCS_ENDIAN_BIG == arg->end_sys )
        {
            // apply the sign bit
            uint8_t sign = ((uint8_t*)src)[0] & 0x80;
            if( arg->meta[arg->meta_i].type == json_type_int) ((uint8_t*)src)[8-len] |= sign;

            // copy to byte array
            if( JCS_ENDIAN_BIG == arg->end_byte ) memcpy( &arg->byte[arg->byte_i], src+8-len, len );
            else
            {
                jcs_swap( src );
                memcpy( &arg->byte[arg->byte_i], src, len );
            }
        }
    }
    else
    {
        if( len > arg->meta[arg->meta_i].size ) return -JCS_ERR_TO_BYTE_MEMCPY_LEN_ARG;
        memcpy( &arg->byte[arg->byte_i], src, len );
    }

    // increment indexes
    arg->byte_i += arg->meta[arg->meta_i].size;
    arg->meta_i += 1;

    return 0;
}

int jcs_copy_to_json( void* dst, jcs_arg_t* arg, int len )
{
    if( arg->meta[arg->meta_i].type == json_type_boolean
    ||  arg->meta[arg->meta_i].type == json_type_double
    ||  arg->meta[arg->meta_i].type == json_type_int )
    {
        if( len != 8 &&   arg->meta[arg->meta_i].type == json_type_double )    return -JCS_ERR_TO_JSON_MEMCPY_LEN_DBL;
        if( len  > 8 && ( arg->meta[arg->meta_i].type == json_type_int
        ||                arg->meta[arg->meta_i].type == json_type_boolean ) ) return -JCS_ERR_TO_JSON_MEMCPY_LEN_INT;

        if( JCS_ENDIAN_LIL == arg->end_byte )
        {
            // save the sign bit
            uint8_t sign = arg->byte[arg->byte_i+len] & 0x80;

            // copy to destination address
            memcpy( &((uint8_t*)dst)[0], &arg->byte[arg->byte_i], len );

            // apply the sign bit
            if( arg->meta[arg->meta_i].type == json_type_int) ((uint8_t*)dst)[7] |= sign;

            // swap the bytes
            if( JCS_ENDIAN_BIG == arg->end_sys ) jcs_swap( dst );
        }
        else if( JCS_ENDIAN_BIG == arg->end_byte )
        {
            // save the sign bit
            uint8_t sign = arg->byte[arg->byte_i] & 0x80;

            // copy to destination address
            memcpy( &((uint8_t*)dst)[8-len], &arg->byte[arg->byte_i], len );

            if( arg->meta[arg->meta_i].type == json_type_int) ((uint8_t*)dst)[0] |= sign;

            // swap the bytes
            if( JCS_ENDIAN_LIL == arg->end_sys ) jcs_swap( dst );
        }
    }

    // increment indexes
    arg->byte_i += arg->meta[arg->meta_i].size;
    arg->meta_i += 1;

    return 0;
}