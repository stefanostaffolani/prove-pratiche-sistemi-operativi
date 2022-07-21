#include <stdio.h>
#include <sys/timerfd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int td = timerfd_create(CLOCK_REALTIME, 0);
	if(td < 0){
		perror("timerfd_create");
		exit(EXIT_FAILURE);
	}
	int seconds = atoi(argv[1])/1000;
	long nanosec_time = (long) (atoi(argv[1])%1000)*1000000;
	struct itimerspec spec = {
				{0,0},
				{seconds, nanosec_time}
				};
	char buf[8];
	timerfd_settime(td, 0, &spec, NULL);
	int retval;
	retval = read(td, &buf, sizeof(char)*8);
	if(retval < 0){
		perror("read");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}


