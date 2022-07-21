#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if (argc < 2){
		perror("missing args\n");
		exit(EXIT_FAILURE);
	}
	union sigval s;
	pid_t dest = atoi(argv[1]);
	//char **bo = &argv[2];
	//printf("*bo : %p\n",*bo);
	//printf("*((char **) argv) : %p\n", *((char **) argv[2]));
	//printf("argv[2] : %p\n", argv[2]);
	//printf("(void**)argv[2] : %p\n",(void **)argv[2]);
	//printf("*(void**)argv[2] : %p\n", *(void **)argv[2]);
	
	/* Il puntatore a char argv[2] punta ad una zona di 1 byte che sarebbe l'ultimo char poiche' little endian
	 * facendo un semplice cast a void* riusciremmo a prendere tutta la locazione da 8 byte ma non potremmo leggerne il contenuto poiche'
	 * void non puo' essere dereferenziato dunque facciamo un cast a void** cosi' da poter fare una dereferenziazione e leggerne il contenuto. 
	 * il contenuto saranno i byte della stringa che potranno essere passati 
	 */
	s.sival_ptr = *((void **)argv[2]);


	printf("%p\n",s.sival_ptr);
	sigqueue(dest, SIGUSR1, s);
	printf("ok send\n");
	exit(EXIT_SUCCESS);
}

