#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
int main(int argc, char *argv[]){
	pid_t pid1,pid2;
	char helper1, helper2, helper3, helper4;
	int status1, status2;
	FILE *fp1, *fp2;
	fp1 = fopen(argv[1], "r");	
	fseek(fp1, 0L, SEEK_END);
	size_t sz1 = ftell(fp1);	
	printf("size of file : %ld\n", sz1);
	rewind(fp1);
	
	fp2 = fopen(argv[2], "r");	
	fseek(fp2, 0L, SEEK_END);
	size_t sz2 = ftell(fp2);	
	printf("size of file : %ld\n", sz2);
	rewind(fp2);
	
	if (sz1 ^ sz2){    // hanno diversa dimensione
		printf("files differs\n");
		exit(EXIT_SUCCESS);
	}

	size_t middle;
	if (sz1 % 2)
		middle = ((sz1*sizeof(char)-1)/2);
	else
		middle = ((sz1*sizeof(char))/2);
		
	switch(pid1 = fork()){
		case 0:   // primo processo che controlla la prima meta'
			for(size_t i = 0; i < middle; i++){
				fread(&helper1, sizeof(char), 1, fp1);
				fread(&helper2, sizeof(char), 1, fp2);
				if(helper1 ^ helper2)  // files differs
					exit(40);	
			}
			exit(41);		
			break;
		case -1:
			exit(EXIT_FAILURE);
			break;
		default:
			switch(pid2 = fork()){
				case 0:
					fseek(fp1, middle*sizeof(char), SEEK_SET);
					fseek(fp2, middle*sizeof(char), SEEK_SET);
					for(size_t i = middle; i <= sz2; i++){
						fread(&helper3, sizeof(char), 1, fp1);
						fread(&helper4, sizeof(char), 1, fp2);
						if(helper3 ^ helper4)  // files differs
							exit(42);
					}
					exit(43);	
					break;
				case -1:
					exit(EXIT_FAILURE);
					break;
				default:
					wait(&status1);
					if(WEXITSTATUS(status1) == 40){
						printf("files differs\n");
						kill(pid2, SIGUSR1);
						exit(EXIT_SUCCESS);
					}else if(WEXITSTATUS(status1) == 42){
						printf("files differs\n");
						kill(pid1, SIGUSR1);
						exit(EXIT_SUCCESS);
					}
					else{
						wait(&status2);
						if(WEXITSTATUS(status2) == 40){
							printf("files differs\n");
							kill(pid2, SIGUSR1);
							exit(EXIT_SUCCESS);
						}else if(WEXITSTATUS(status2) == 42){
							printf("files differs\n");
							kill(pid1, SIGUSR1);
							exit(EXIT_SUCCESS);
						}
					}
				}
			}				

	return 0;
}
