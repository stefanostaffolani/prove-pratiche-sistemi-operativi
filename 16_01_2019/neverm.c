#include <stdio.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE 
#define FALSE 0
#endif

#define EVENT_SIZE (sizeof (struct inotify_event))
#define BUF_LEN    (16 * (EVENT_SIZE + 16))
#define MAX_SIZE_NAME 4096

typedef struct inotify_event* pinot;
typedef unsigned int bool;

bool touch(const char *filename){
	int fd = open(filename, O_CREAT | S_IROTH | S_IWOTH);
	//printf("\n%s\n", filename);	
	if (fd == -1){
		perror("Unable to touch file");
		return FALSE;
	}
	close(fd);
	return TRUE;
}

int main(int argc, char * argv[]){
	int wd, fd;
	fd = inotify_init();
	wd = inotify_add_watch(fd, argv[1], IN_DELETE);
	if (wd == -1)
		printf("Couldn't add watch to %s\n", argv[1]);
	else
		printf("Watching %s\n",argv[1]);
		
	char buf[BUF_LEN];
	int len;
	for(;;){
		len = read(fd, buf, BUF_LEN);
		if (len > 0){
			int i = 0;
			while (i < len){
				pinot event;
				event = (pinot) &buf[i];

				printf("wd=%d mask=%x cookie=%u len=%u\n",
				       		event->wd, event->mask,
						event->cookie, event->len);
				if (event->mask & IN_DELETE){
					printf("file %s deleted\n", event->name);
					char filename[MAX_SIZE_NAME] = "./";
					strncat(filename, argv[1], MAX_SIZE_NAME);
					strncat(filename, event->name, MAX_SIZE_NAME);
					//printf("\n%s\n", filename);
					if(!touch(filename))
						exit(EXIT_FAILURE);

				}
				i += EVENT_SIZE + event->len;
			}
		}
	}	
	
	
	return 1;
}

