#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "jcs_test_meta.h"


void print_raw( jcs_arg_t* arg )
{
    for( int i = 0; i < arg->byte_i; i++ )
    {
        if( i % 16 == 0 ) printf( "\n" );
        printf( "%02X ", arg->byte[i] );
    }
    printf( "\n" );
}

int main()
{
    {
        // TEST 1
        printf( "\ntest 1: \n");
        int ret = -1;
        char    json[0x100000] = {0};
        uint8_t byte[0x100000] = {0};
        jcs_arg_t arg = { .meta = jcs_test_1_meta, .meta_lim = sizeof(jcs_test_1_meta)/sizeof(jcs_meta_t), .byte = byte, .json = json };
        char* file_json = "json/test_1.json";
        char* file_byte = "json/test_1.bin";
        int fd = open( file_json, O_RDONLY );
        arg.meta = jcs_test_1_meta;
        if( fd != -1 )
        {
            ret = pread( fd, json, sizeof(json), 0 );
            close( fd );
        }
        else printf( "unable to open %s \n", file_json );
        if( ret != -1)
        {
            ret = jcs_json_to_byte( &arg );
            printf( "jcs_json_to_byte returned %d", ret );
            print_raw( &arg );
            // fd = open( file_byte, O_RDWR | O_CREAT );
            // if( fd != -1 )
            // {
            //     pwrite( fd, arg.byte, arg.byte_i, 0 );
            //     close( fd );
            // }
            // else printf( "unable to open %s \n", file_byte );
        }
    }
    {
        // TEST 2
        printf( "\ntest 2: \n");
        int ret = -1;
        char    json[0x100000] = {0};
        uint8_t byte[0x100000] = {0};
        jcs_arg_t arg = { .meta = jcs_test_2_meta, .meta_lim = sizeof(jcs_test_2_meta)/sizeof(jcs_meta_t), .byte = byte, .json = json };
        char* file_json = "json/test_2.json";
        char* file_byte = "json/test_2.bin";
        int fd = open( file_json, O_RDONLY );
        if( fd != -1 )
        {
            ret = pread( fd, json, sizeof(json), 0 );
            close( fd );
        }
        else printf( "unable to open %s \n", file_json );
        if( ret != -1)
        {
            ret = jcs_json_to_byte( &arg );
            printf( "jcs_json_to_byte returned %d", ret );
            print_raw( &arg );
            // fd = open( file_byte, O_RDWR | O_CREAT );
            // if( fd != -1 )
            // {
            //     pwrite( fd, arg.byte, arg.byte_i, 0 );
            //     close( fd );
            // }
            // else printf( "unable to open %s \n", file_byte );
        }
    }
    {
        // TEST 3
        printf( "\ntest 3: \n");
        int ret = -1;
        char    json[0x100000] = {0};
        uint8_t byte[0x100000] = {0};
        jcs_arg_t arg = { .meta = jcs_test_3_meta, .meta_lim = sizeof(jcs_test_3_meta)/sizeof(jcs_meta_t), .byte = byte, .json = json };
        char* file_json = "json/test_3.json";
        char* file_byte = "json/test_3.bin";
        int fd = open( file_json, O_RDONLY );
        if( fd != -1 )
        {
            ret = pread( fd, json, sizeof(json), 0 );
            close( fd );
        }
        else printf( "unable to open %s \n", file_json );
        if( ret != -1)
        {
            ret = jcs_json_to_byte( &arg );
            printf( "jcs_json_to_byte returned %d", ret );
            print_raw( &arg );
            // fd = open( file_byte, O_RDWR | O_CREAT );
            // if( fd != -1 )
            // {
            //     pwrite( fd, arg.byte, arg.byte_i, 0 );
            //     close( fd );
            // }
            // else printf( "unable to open %s \n", file_byte );
        }
    }
    {
        // TEST 4
        printf( "\ntest 4: \n");
        int ret = -1;
        char    json[0x100000] = {0};
        uint8_t byte[0x100000] = {0};
        jcs_arg_t arg = { .meta = jcs_test_4_meta, .meta_lim = sizeof(jcs_test_4_meta)/sizeof(jcs_meta_t), .byte = byte, .json = json };
        char* file_json = "json/test_4.json";
        char* file_byte = "json/test_4.bin";
        int fd = open( file_json, O_RDONLY );
        if( fd != -1 )
        {
            ret = pread( fd, json, sizeof(json), 0 );
            close( fd );
        }
        else printf( "unable to open %s \n", file_json );
        if( ret != -1)
        {
            ret = jcs_json_to_byte( &arg );
            printf( "jcs_json_to_byte returned %d", ret );
            print_raw( &arg );
            // fd = open( file_byte, O_RDWR | O_CREAT );
            // if( fd != -1 )
            // {
            //     pwrite( fd, arg.byte, arg.byte_i, 0 );
            //     close( fd );
            // }
            // else printf( "unable to open %s \n", file_byte );
        }
    }
    {
        // TEST 5
        printf( "\ntest 5: \n");
        int ret = -1;
        char    json[0x100000] = {0};
        uint8_t byte[0x100000] = {0};
        jcs_arg_t arg = { .meta = jcs_test_5_meta, .meta_lim = sizeof(jcs_test_5_meta)/sizeof(jcs_meta_t), .byte = byte, .json = json };
        char* file_json = "json/test_5.json";
        char* file_byte = "json/test_5.bin";
        int fd = open( file_json, O_RDONLY );
        if( fd != -1 )
        {
            ret = pread( fd, json, sizeof(json), 0 );
            close( fd );
        }
        else printf( "unable to open %s \n", file_json );
        if( ret != -1)
        {
            ret = jcs_json_to_byte( &arg );
            printf( "jcs_json_to_byte returned %d", ret );
            print_raw( &arg );
            // fd = open( file_byte, O_RDWR | O_CREAT );
            // if( fd != -1 )
            // {
            //     pwrite( fd, arg.byte, arg.byte_i, 0 );
            //     close( fd );
            // }
            // else printf( "unable to open %s \n", file_byte );
        }
    }
    {
        // TEST 6
        printf( "\ntest 6: \n");
        int ret = -1;
        char    json[0x100000] = {0};
        uint8_t byte[0x100000] = {0};
        jcs_arg_t arg = { .meta = jcs_test_6_meta, .meta_lim = sizeof(jcs_test_6_meta)/sizeof(jcs_meta_t), .byte = byte, .json = json };
        char* file_json = "json/test_6.json";
        char* file_byte = "json/test_6.bin";
        int fd = open( file_json, O_RDONLY );
        if( fd != -1 )
        {
            ret = pread( fd, json, sizeof(json), 0 );
            close( fd );
        }
        else printf( "unable to open %s \n", file_json );
        if( ret != -1)
        {
            ret = jcs_json_to_byte( &arg );
            printf( "jcs_json_to_byte returned %d", ret );
            print_raw( &arg );
            // fd = open( file_byte, O_RDWR | O_CREAT );
            // if( fd != -1 )
            // {
            //     pwrite( fd, arg.byte, arg.byte_i, 0 );
            //     close( fd );
            // }
            // else printf( "unable to open %s \n", file_byte );
        }
    }

    return 0;
}