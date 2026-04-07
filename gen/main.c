#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <jcs.h>


#define FLAG_META   1
#define FLAG_STRUCT 2


static int gen_meta  ( char* buf );
static int gen_struct( char* buf );

static void pr_usage( int argc, char** argv )
{
    printf( "\n%s: json-c serializer code generator \n\n", argv[0] );
    printf( "    argv[1]: \"meta\" or \"struct\" \n" );
    printf( "    argv[2]: output file base name (filename is prefix+_base+.h); \"\" for \"jcs_meta.h\", or \"jcs_struct.h\" depending on argv[1] \n" );
    printf( "    argv[3] - argv[n]: list of files to generate code from \n\n" );
}

int main( int argc, char** argv )
{
    int   ret  = 0;
    int   flag = 0;
    char* prfx = NULL;
    char* name[1024] = {0};

    if( argc < 4 )
    {
        pr_usage( argc, argv );
        return -1;
    }

    if( strcmp( "meta", argv[1] ) == 0 )
    {
        flag = FLAG_META;
        prfx = "jcs_meta";
    }
    else if( strcmp( "struct", argv[1] ) == 0 )
    {
        flag = FLAG_STRUCT;
        prfx = "jcs_struct";
    }
    else
    {
        pr_usage( argc, argv );
        return -1;
    }

    strcat( name, prfx );
    if( strcmp( "", argv[2] ) == 0 ) strcat( name, ".h" );
    else
    {
        strcat( name, "_"     );
        strcat( name, argv[2] );
        strcat( name, ".h"    );
    }

    for( int i = 3; i < argc; i++ )
    {
        char buf[0x100000] = {0};
        int fd = open( argv[i], O_RDONLY );
        if( fd != -1 )
        {
            ret = pread( fd, buf, sizeof(buf), 0 );
            close( fd );
        }
        else
        {
            printf( "unable to open %s \n", argv[i] );
            return -1;
        }

        if( ret == -1 )
        {
            printf( "unable to read %s \n", argv[i] );
            return -1;
        }

        printf( "file data is:\n%s\n", buf );

        if     ( flag == FLAG_META   ) gen_meta  ( buf );
        else if( flag == FLAG_STRUCT ) gen_struct( buf );
    }
    
    return 0;
}

int gen_meta( char* buf )
{
    int ret = 0;

    printf( "generating meta file \n" );

    return ret;
}

int gen_struct( char* buf )
{
    int ret = 0;

    printf( "generating struct file \n" );

    return ret;
}
