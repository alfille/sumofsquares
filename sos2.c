#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


// Program to find best sum of squares for all integers

// Second version -- uses more space but o(N^1.5)

#define MAX_N 1000 // max integer (squared)
#define MAX_M MAX_N // max covering square

struct global {
    int n ;
    int m ;
    long long int nn ;
    int count ;
    int power ;
} Global = { MAX_N, MAX_M, 0, 0, 2 } ;
    
size_t * Powers ;
int * Best ; // Best solution for each residual
size_t * First ; // First element of decomposition

long long int power( int value )
{
    int p ;
    long long int result = value ;
    for ( p=Global.power; p>1 ; --p ) {
        result *= value ;
    }
    return result ;
}

void SetupSQ( void )
{
    int i;
    Global.nn = power(Global.n);
    Powers = calloc( Global.m+1, sizeof(Powers[0]) ) ;
    if (Powers==NULL) exit(1) ;
    for ( i=0 ; i<Global.m+1 ; ++i ) {
        Powers[i] = power(i);
    }
    Best = calloc( Global.nn+1, sizeof(Best[0]) );
    if ( Global.count == 1 ) {
        First = calloc( Global.nn+1, sizeof(First[0]) );
        First[0] = 0 ;
        First[1] = 1 ;
    }
    Best[0] = 0 ;
    Best[1] = 1;
}

void TestNum( size_t N )
{
    size_t sq ;
    int best = 1 + Best[N-1] ;
    int first = 1 ;
    for (sq = 2; sq < Global.m ; ++sq ) {
        ssize_t diff = N - Powers[sq] ;
        if ( diff < 0 ) {
            break ;
        } else {
            int try = 1 + Best[diff] ;
            if ( try <= best ) {
                best = try ;
                first = sq ;
            }
        }
    }
    Best[N] = best ;
    First[N] = first ;
}
 
void TestNum_just_count( size_t N )
{
    size_t sq ;
    int best = 1 + Best[N-1] ;
    for (sq = 2; sq < Global.m ; ++sq ) {
        ssize_t diff = N - Powers[sq] ;
        if ( diff < 0 ) {
            break ;
        } else {
            int try = 1 + Best[diff] ;
            if ( try <= best ) {
                best = try ;
            }
        }
    }
    Best[N] = best ;
}
 
void ShowTerms( size_t N )
{
    size_t next = N ;
    do {
        size_t first = First[next] ;
        printf( ",%8ld", (long int) first ) ;
        next -= Powers[first] ;
    } while ( next > 0 ) ;
    printf("\n");
}

void ShowCount( size_t N )
{
    printf(",%8d\n", Best[N] ) ;
}


void usage( char * prog )
{
    printf( "Sum-of-squares decomposition: Find the minimum number of integer squares thqt sum to a given number\n");
    printf( "\t{c} 2018 Paul H Alfille see github.com\n" );
    printf( "Usage %s number\n",prog);
    printf( "\tlook for sums up to <number> squared (default 100)\n");
    printf( "\t-m --max max_number used for squares\n");
    printf( "\t-3 --cube look for cubed number sums\n" );
    printf( "\t-4 --fourth power sums\n");
    printf( "\t-5 --fifth power sums\n");
    printf( "\t-6 --sixth power sums\n");
    printf( "\t-p --power up to 10th\n");
    printf( "\t-c --count number of terms rather than list them\n");
    printf( "\t-h --help this summary\n") ;
    exit(0) ;
}


void commandline( int argc, char * argv[] )
{
    // options

    int opt ;
    int long_index = 0 ; // dummy
    static struct option long_opts[] = {
        { "max", required_argument, 0, 'm' },
        { "cube", no_argument, 0, '3' } ,
        { "fourth", no_argument, 0, '4' } ,
        { "fifth", no_argument, 0, '5' } ,
        { "sixth", no_argument, 0, '6' } ,
        { "count", no_argument, 0, 'c' } ,
        { "power", required_argument, 0, 'p' } ,
        { "help", no_argument, 0, 'h' } ,
        { 0, 0, 0, 0, },
    } ;
    while ( (opt=getopt_long(argc, argv, "m:p:3456ch", long_opts, &long_index)) != -1){
        switch (opt) {
            case 'm':
				if ( optarg != NULL ) {
					 Global.m = atoi(optarg) ;
				} else {
					fprintf(stderr,"Option %c needs a following value -- ignoring\n",opt);
				}
                break ;
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
            case 'c':
                Global.count = 1 ;
                break ;
            default:
                usage(argv[0]) ;
                exit(1);
        }
    }
    
    if ( optind < argc ) {
		Global.n = atoi( argv[optind] ) ;
	}

}
    

int main( int argc, char * argv[] )
{
    size_t i;

    commandline( argc, argv ) ;
    SetupSQ() ;
    for (i=1;i<Global.nn;++i) {
        printf("%8ld", (long int) i );
        TestNum( i ) ;
        if ( Global.count == 1 ) {
            TestNum_just_count( i ) ;
            ShowCount( i ) ;
        } else {
            TestNum( i ) ;
            ShowTerms( i ) ;
        }
    }
    return 0 ;
    
}
