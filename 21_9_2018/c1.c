#include <stdio.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]){
	pid_t mypid = getpid();
	printf("il mio pid e' : %d\n", mypid);
	sigset_t mask;
	int sfd;
	struct signalfd_siginfo fdsi;
	ssize_t s;
	time_t t;
	struct tm tm;
	sigemptyset(&mask);
	//sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);

	sigprocmask(SIG_BLOCK, &mask, NULL);

	sfd = signalfd(-1, &mask, 0);

	FILE *f;
	char pidh[10];
	while(1){
		s = read(sfd, &fdsi, sizeof(fdsi));
		if(fdsi.ssi_signo == SIGUSR1 || fdsi.ssi_signo == SIGUSR2){
			printf("%d\n", fdsi.ssi_pid);
			//itoa(fdsi.ssi_pid, pidh, 10);
			sprintf(pidh, "%d", fdsi.ssi_pid);
			//fd = open(, O_CREAT | O_RDWR | O_APPEND);
			f = fopen(pidh, "a");
			t = time(NULL);
			tm = *localtime(&t);
			if (fdsi.ssi_signo == SIGUSR1)
				fprintf(f, " SIGUSR1 %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			else
				fprintf(f, " SIGUSR2 %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			fclose(f);
		}
	}

	exit(EXIT_FAILURE);
}

