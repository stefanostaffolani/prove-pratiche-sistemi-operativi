#include <stdio.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	pid_t pid1, pid2;
	int status;
	prctl(PR_SET_CHILD_SUBREAPER);
	printf("il processo ha pid: %d\n",getpid());
	pid1 = fork();
	switch(pid1){
	case 0:     		//child process
		printf("il child ha pid: %d\n", getpid());
		pid2 = fork();
		switch(pid2){
		case 0:
			sleep(5);   // il nipote aspetta 5 secondi
			printf("il padre del nipote : %d\n",getppid());	
			exit(42);
			break;

		case -1:
			perror("fork nipote");   // errore
			exit(EXIT_FAILURE);
			break;
		default:
			exit(EXIT_SUCCESS);     // termina il child
			break;
		}
		break;
	case -1:               // error
		perror("fork");
		exit(EXIT_FAILURE);
		break;
	default:              // parent process
		wait(NULL);  // aspetta che termini il figlio
		wait(&status);  // ora il nipote
		break;
	}
	printf("status: %d\n", status);
	if (WEXITSTATUS(status) == 42){
		printf("ricevuto end nipote\n");
	}
	exit(EXIT_SUCCESS);
}
