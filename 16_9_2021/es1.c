#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define EVENT_SIZE ( sizeof (struct inotify_event) )
#define MAX_BUF ( 1024 * ( EVENT_SIZE + 16 ) )

typedef struct inotify_event* pinot;

int count_words(char *name){
	char *h = name;
	int counter = 1;
	while(*h != '\0'){
		if(*h == ' ')
			counter++;
		h++;
	}
	return counter;
}

int main(int argc, char *argv[]){
	int fd = inotify_init();
	int wd = inotify_add_watch(fd, argv[1], IN_CREATE);
	//int length, i = 0;
	if(wd == -1){
		perror("initify_add_watch");
		exit(EXIT_FAILURE);
	}else{
		printf("watching...\n");
	}
	char buffer[MAX_BUF];
	int len;
	for(;;){
		len = read(fd, buffer, MAX_BUF);
		if(len > 0){
			int i = 0;
			while( i < len){
				pinot event;
				event = (pinot) &buffer[i];
				
				if(event->mask & IN_CREATE){
					int n = count_words(event->name);
					char *args[n+1];
					char *a = malloc(strlen(event->name));
					strncpy(a, event->name, strlen(event->name));
					char *token = strtok(a, " ");
					int i = 0;
					while(token != NULL){
						args[i] = malloc(strlen(token));
						strncpy(args[i], token, strlen(token));
						i++;
						token = strtok(NULL, " ");
					}
					args[i] = NULL;
					int pid;
					if(pid = fork() > 0){
						wait(NULL);
						unlink(event->name);
					}else if (pid < 0){
						perror("errore fork");
						exit(EXIT_FAILURE);
					}else{
						execvp(args[0], args);
					}
					
				}
				i += EVENT_SIZE + event->len;
			}
		}

	}
	inotify_rm_watch(fd, wd);
	close(fd);
	exit(EXIT_SUCCESS);
}
