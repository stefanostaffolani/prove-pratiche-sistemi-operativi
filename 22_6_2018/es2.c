
#include <stdio.h>
#include <sys/timerfd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>
#include <stdint.h>


int main(int argc, char *argv[]){
	
	struct pollfd pfds[argc-1];
	int fd;
	for(int i = 1; i < argc; i++){
		fd = timerfd_create(CLOCK_REALTIME, 0);
		
		if(fd < 0){
			perror("timerfd_create");
			exit(EXIT_FAILURE);
		}
		
		int sec = atoi(argv[i])/1000;
		long nanosec_time = (long) (atoi(argv[i])%1000)*1000000;
		struct itimerspec spec = {
					{0,0},
					{sec, nanosec_time}
					};
		timerfd_settime(fd, 0, &spec, NULL);
		pfds[i-1].fd = fd;
		pfds[i-1].events = POLLIN;
		pfds[i-1].revents = 0;
	}
	uint64_t buf;
	for(int i = 1; i< argc; i++){
		poll(pfds, argc-1, -1);
		for(int j = 0; j < argc-1; j++){
			if(pfds[j].revents == POLLIN){
				read(pfds[j].fd, &buf, sizeof(uint64_t));
				pfds[j].revents = 0;
				printf("%s expired\n", argv[j+1]);
				//print_elapsed_time();
			}
		}
	}

	exit(EXIT_SUCCESS);
}


