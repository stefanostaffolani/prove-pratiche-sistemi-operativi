#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sig(int sign, siginfo_t* sig, void *p){
	printf("%p\n", sig->si_value.sival_ptr);
	printf("arrivo qua\n");
	char *a = (char *)(&sig->si_value.sival_ptr);
	for(int i = 0; i < 8; i++){
		printf("%c",*a);
		a++;
	}
	printf("\n");
}

int main(){
	printf("il mio pid e' %d\n", getpid());
	//signal(SIGUSR1, handle_sig);
	struct sigaction new_action;
	new_action.sa_sigaction = &handle_sig;
	sigemptyset(&new_action.sa_mask);

	new_action.sa_flags = 0;
	new_action.sa_flags |= SA_SIGINFO;
	sigaction(SIGUSR1, &new_action, NULL);
	pause();
	exit(EXIT_SUCCESS);
}

