#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


// Program to find best sum of squares for all integers
#define MAX_DEPTH 10

struct global {
    int depth ;
    int power ;
    int ratio ;
} Global = { MAX_DEPTH, 2, 0 } ;
    

long long int power( int value )
{
    int p ;
    long long int result = value ;
    for ( p=Global.power; p>1 ; --p ) {
        result *= value ;
    }
    return result ;
}

void Zero( int * c )
{
    int i ;
    for ( i = 0 ; i < Global.depth ; ++i ) {
        c[i] = 0 ;
    }
}

void Show( int * c )
{
    int i ;
    for ( i = 0 ; i < Global.depth ; ++i ) {
        printf(",%8d",c[i]) ;
    }
    printf("\n");
}


void file_parse( void )
{
    long int line = 0 ;
    long int next_side = 1;
    long int next_power = power( next_side ) ;
    long int num ;
    long int count ; 
    int counts[Global.depth] ;

    Zero(counts) ;
    
    while ( scanf( "%ld,%ld",&num,&count) == 2 ) {
        ++ line ;
        if ( count < 1 || count > Global.depth ) {
            fprintf( stderr, "Count %ld out of range on line %ld\n",count,line) ;
            exit(1);
        }
        ++ counts[count-1] ;
        if ( line == next_power ) {
            if ( Global.ratio == 0 ) {
                printf("%8ld",line) ;
                Show(counts) ;
                ++ next_side ;
                next_power = power( next_side ) ;
            } else {
                // ratios
                int i ;
                long int this_power = next_power ;
                printf("%8ld",next_side) ;
                ++ next_side ;
                next_power = power( next_side ) ;
                for ( i = 0 ; i < Global.depth ; ++i ) {
                    printf(", %g", (double) counts[i] / (double) (next_power-this_power) ) ;
                }
                printf("\n");
            }
            Zero(counts) ;
        }
    }
}
        

void usage( char * prog )
{
    printf( "Sum-of-squares counts: add up depths from sos -c for each square interval\n");
    printf( "\t{c} 2018 Paul H Alfille see github.com\n" );
    printf( "Usage %s number\n",prog);
    printf( "\t-3 --cube look for cubed number sums\n" );
    printf( "\t-4 --fourth power sums\n");
    printf( "\t-5 --fifth power sums\n");
    printf( "\t-6 --sixth power sums\n");
    printf( "\t-p --power up to 10th\n");
    printf( "\t-d --depth max number of squares summed (default 10)\n");
    printf( "\t-h --help this summary\n") ;
    exit(0) ;
}


void commandline( int argc, char * argv[] )
{
    // options

    int opt ;
    int long_index = 0 ; // dummy
    static struct option long_opts[] = {
        { "depth", required_argument, 0, 'd' } ,
        { "ratio", no_argument, 0, 'r' } ,
        { "cube", no_argument, 0, '3' } ,
        { "fourth", no_argument, 0, '4' } ,
        { "fifth", no_argument, 0, '5' } ,
        { "sixth", no_argument, 0, '6' } ,
        { "power", required_argument, 0, 'p' } ,
        { "help", no_argument, 0, 'h' } ,
        { 0, 0, 0, 0, },
    } ;
    while ( (opt=getopt_long(argc, argv, "d:p:r3456h", long_opts, &long_index)) != -1){
        switch (opt) {
            case 'p':
				if ( optarg != NULL ) {
                    Global.power = atoi(optarg) ;
                    if (Global.power > 10) {
                        fprintf(stderr,"Power too large %d > 10\n",Global.power) ;
                        exit(1) ;
                    } else if ( Global.power < 1 ) {
                        fprintf(stderr,"Power too small %d < 1\n",Global.power) ;
                        exit(1) ;
                    }
				} else {
					fprintf(stderr,"Option %c needs a following value -- ignoring\n",opt);
				}
                break ;
            case 'd':
				if ( optarg != NULL ) {
					 Global.depth = atoi(optarg) ;
				} else {
					fprintf(stderr,"Option %c needs a following value -- ignoring\n",opt);
				}
            case 'r':
                Global.ratio = 1 ;
                break ;
            case '3':
                Global.power = 3 ;
                break ;
            case '4':
                Global.power = 4 ;
                break ;
            case '5':
                Global.power = 4 ;
                break ;
            case '6':
                Global.power = 4 ;
                break ;
            case '?':
            case 'h':
                usage(argv[0]);
                exit(0);
            default:
                usage(argv[0]) ;
                exit(1);
        }
    }

}
    

int main( int argc, char * argv[] )
{
    int i;

    commandline( argc, argv ) ;
    file_parse() ;
    return 0 ;
    
}
