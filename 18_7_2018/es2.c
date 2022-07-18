
#include <stdio.h>
#include <sys/signalfd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(){
	int sfd;
	struct signalfd_siginfo fdsi;
	ssize_t s;
	FILE *fp;
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);
	if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1){
		perror("sigprocmask");
		exit(EXIT_FAILURE);
	}
	sfd = signalfd(-1, &mask, 0);
	if(sfd == -1){
		perror("signalfd");
		exit(EXIT_FAILURE);	
	}
	fp = fopen("/tmp/countpid", "w");
	fprintf(fp,"%d", getpid());
	fclose(fp);
	//printf("pid : %d\n", getpid());	
	int counter = 0;
	for(;;){
		s = read(sfd, &fdsi, sizeof(fdsi));
		if(s != sizeof(fdsi)){
			perror("read");
			exit(EXIT_SUCCESS);
		}
		if(fdsi.ssi_signo == SIGUSR1)
			counter++;
		else if(fdsi.ssi_signo == SIGUSR2)
			counter--;
		printf("counter: %d\n", counter);
		fflush(stdout);
	}
	exit(EXIT_SUCCESS);
}
