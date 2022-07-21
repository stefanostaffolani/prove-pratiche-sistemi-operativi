#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	pid_t mypid = getpid();
	printf("mypid : %d\n", mypid);
	for(int i = 0; i<5; i++){
		kill(atoi(argv[1]), SIGUSR1);
		kill(atoi(argv[1]), SIGUSR2);
		sleep(2);
	}
	return 0;
}
