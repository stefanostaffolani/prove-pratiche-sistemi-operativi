#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	FILE *fp = fopen("/tmp/countpid", "r");
	printf("aperto il file\n");
	char *counter = (char *)malloc(sizeof(pid_t));
	fread(counter, sizeof(pid_t), sizeof(pid_t), fp);
	printf("%d\n", atoi(counter));
	fclose(fp);
	printf("ok read\n");
	kill(atoi(counter), SIGUSR1);
	switch(fork()){
	case 0:
		execvp(argv[1], argv+1);
		break;
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
		break;
	default:
		wait(0);
		kill(atoi(counter), SIGUSR2);
		break;
	}
	exit(EXIT_SUCCESS);
}
