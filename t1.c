#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations ./t1 num_procs num_longs num_rounds
// perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations ./t1 16 1000000 50
// usage ./t1 num_procs num_longs num_rounds
void work(long num_longs, long num_rounds);//method stubby

int main(int argc, char *argv[])
{
	int num_procs = atoi(argv[1]);//number of processes to spawn to do work
	long num_longs = atol(argv[2]);//number of longs (increases number of different cache refs per loop)
	long num_rounds = atol(argv[3]);//number of rounds (increases repeats of cache refs)

	int wait_on[num_procs];//hold pids to wait on in main

	int making_procs = 1;//start out true for needing to make more
	int num_made;
	int fork_id;//ret of fork

	for(num_made = 0; num_made < num_procs; num_made++){
		fork_id = fork();//fork to make new proc
		wait_on[num_made] = fork_id;
		if(fork_id == 0){//if in a child process
			printf("calling work %d\n", num_made);
			work(num_longs, num_rounds);//do stuffs
			break;//don't want to loop if in child proc
		}
	}

	//in parent and need to wait for all the babies to die horrible deaths
	if(fork_id != 0){
		int i;
		for(i = 0; i < num_procs; i++){
			waitpid(wait_on[i], NULL, 0);
		}
	}

	return 0;
}

//with 1,000,000 longs and 50 rounds: 1 proc = 45% cache misses, 8 procs = 71% cache misses

//do work in an individual process
void work(long num_longs, long num_rounds){
	long *p = malloc(num_longs*(sizeof(long)));
	long i;
	for(i = 0; i < num_longs; i++){
		p[i] = i; 
	}
					
	int j;
	for(j = 0; j < num_rounds; j++){
		for(i = 0; i < num_longs; i++){
			//printf("%ld",p[i]); 
			long x = p[i];//seems like it doesnt execute this loop without doing something in here?
		}
	}
}



















