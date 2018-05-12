#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>


// Program to find best sum of squares for all integers

// Second version -- uses more space but o(N^1.5)

#define MAX_N 1000 // max integer (squared)
#define MAX_M MAX_N // max covering square

struct global {
    int n ;
    int m ;
    long long int nn ;
    enum {no_count, just_count, summary } count  ;
    int power ;
    int max_depth ;
} Global = { MAX_N, MAX_M, 0, no_count, 2, 4 } ;
    
#define MAX_DECOMP 255 // fits in uint8_t
    
size_t * Powers ;
uint8_t * Best ; // Best solution for each residual
size_t * First ; // First element of decomposition
//size_t summaries* ;
size_t summaries[MAX_DECOMP+1] ;

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
        //printf("%d->%d\n",i,(int)Powers[i]);
    }
    Best = calloc( Global.nn+1, sizeof(Best[0]) );
    switch ( Global.count) {
		case no_count:
			First = calloc( Global.nn+1, sizeof(First[0]) );
			First[0] = 0 ;
			First[1] = 1 ;
			break ;
		case summary:
			//summaries = malloc( Global.max_depth * sizeof(summaries[0]) ) ;
			break ;
        case just_count:
            break ;
    }
    Best[0] = 0 ;
    Best[1] = 1;
}

void TestNum( size_t N )
{
    size_t sq ;
    uint16_t best = 1 + Best[N-1] ;
    int first = 1 ;
    for (sq = 2; sq <= Global.m ; ++sq ) {
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

void Summary_zero( void )
{
	int i ;
	for (i = 0 ; i < Global.max_depth ; ++i ) {
		summaries[i] = 0 ;
	}
}

void Summary_add( int new_size )
{
	int old_max = Global.max_depth ;
    int i ;
    
	Global.max_depth = new_size ;
//	summaries = realloc( summaries, new_size * sizeof( summaries[0] ) ) ;
    for (i=old_max ; i < new_size ; ++i ) {
        summaries[i] = 0 ;
    }
}

void Summary_show( void )
{
	int i ;
	for (i = 0 ; i < Global.max_depth ; ++i ) {
		printf( ",%8ld",summaries[i] ) ;
	}
    printf("\n");
}
    
void TestNum_just_count( size_t N )
{
    size_t sq ;
    uint16_t best = 1 + Best[N-1] ;
    for (sq = 2; sq <= Global.m ; ++sq ) {
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
 
void TestNum_summary( size_t N )
{
    size_t sq ;
    uint16_t best = 1 + Best[N-1] ;
    static size_t generation = 0 ;
    for (sq = 2; sq <= Global.m ; ++sq ) {
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
    if ( best <= Global.max_depth ) {
		++ summaries[best-1];
		if ( best == 1 ) {
            ++ generation ;
            printf("%8d",generation) ;
            Summary_show() ;
            Summary_zero() ;
		}		
    } else {
        Summary_add( best ) ;
		++ summaries[best-1];
    }
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
    printf( "\t-d --summary of counts for each power interval\n");
    printf( "\t-h --help this summary\n") ;
    exit(0) ;
}


void commandline( int argc, char * argv[] )
{
    // options

    int opt ;
    int long_index = 0 ; // dummy
    int maxxed = 0 ;
    static struct option long_opts[] = {
        { "max", required_argument, 0, 'm' },
        { "cube", no_argument, 0, '3' } ,
        { "fourth", no_argument, 0, '4' } ,
        { "fifth", no_argument, 0, '5' } ,
        { "sixth", no_argument, 0, '6' } ,
        { "count", no_argument, 0, 'c' } ,
        { "power", required_argument, 0, 'p' } ,
        { "summary", no_argument, 0, 's' } ,
        { "help", no_argument, 0, 'h' } ,
        { 0, 0, 0, 0, },
    } ;
    while ( (opt=getopt_long(argc, argv, "m:p:3456csh", long_opts, &long_index)) != -1){
        switch (opt) {
            case 'm':
				if ( optarg != NULL ) {
					 Global.m = atoi(optarg) ;
                     maxxed = 1 ;
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
                Global.count = just_count ;
                break ;
            case 's':
                Global.count = summary ;
                break ;
            default:
                usage(argv[0]) ;
                exit(1);
        }
    }
    
    if ( optind < argc ) {
		Global.n = atoi( argv[optind] ) ;
        if ( maxxed == 0 ) {
            Global.m = Global.n ;
        }
	}

}
    

int main( int argc, char * argv[] )
{
    size_t i;

    commandline( argc, argv ) ;
    SetupSQ() ;

    switch (Global.count) {
    case just_count:
        for (i=1;i<=Global.nn;++i) {
            printf("%8ld", (long int) i );
            TestNum_just_count( i ) ;
            ShowCount( i ) ;
        }
        break ;
    case no_count:
        for (i=1;i<=Global.nn;++i) {
            printf("%8ld", (long int) i );
            TestNum( i ) ;
            ShowTerms( i ) ;
        }
        break ;
    case summary:
		Summary_zero() ;
        for (i=1;i<=Global.nn;++i) {
            TestNum_summary( i ) ;
        }
        break ;
    }
    return 0 ;
    
}
