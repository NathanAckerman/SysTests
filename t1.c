#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations ./t1 num_procs num_longs 
// usage ./t1 num_procs num_longs
void work(long num);//method stubby

int main(int argc, char *argv[])
{
	int num_procs = atoi(argv[1]);//number of processes to spawn to do work
	long num_longs = atol(argv[2]);

	int wait_on[num_procs];//hold pids to wait on in main

	int making_procs = 1;//start out true for needing to make more
	int num_made;
	int fork_id;//ret of fork

	for(num_made = 0; num_made < num_procs; num_made++){
		fork_id = fork();//fork to make new proc
		wait_on[num_made] = fork_id;
		if(fork_id == 0){//if in a child process
			printf("calling work %d\n", num_made);
			work(num_longs);//do stuffs
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

//with 1,000,000 longs: 1 proc = 45% cache misses, 16 procs = 70% cache misses

//do work in an individual process
void work(long num){
	long num_longs = num;
	long *p = malloc(num_longs*(sizeof(long)));
	long i;
	for(i = 0; i < num_longs; i++){
		p[i] = i; 
	}
					
	int j;
	for(j = 0; j < 50; j++){
		for(i = 0; i < num_longs; i++){
			//printf("%ld",p[i]); 
			long x = p[i];//seems like it doesnt execute this loop without doing something in here?
		}
	}
}



















