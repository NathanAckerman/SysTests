#include <stdio.h>
#include <stdlib.h>

// perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations sleep 5 

int main(int argc, char *argv[])
{
	long num_longs = 10000;
	long *p = malloc(num_longs*(sizeof(long)));
	long i;
	for(i = 0; i < num_longs; i++){
		p[i] = i; 
	}
	
	int j;
	for(j = 0; j < 10; j++){
		for(i = 0; i < num_longs; i++){
			//printf("%ld",p[i]); 
			long x = p[i];
		}
	}
	return 0;
}























