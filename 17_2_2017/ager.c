#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <utime.h>
#include <stdlib.h>

#define TEN_DAYS 60*60*24*10

int main(int argc, char *argv[]){
	
	struct stat sf;
	time_t mtime;
	struct utimbuf new_times;

	for(int i = 1; i < argc; i++){
		if(stat(argv[i], &sf) < 0){
			perror(argv[i]);
			exit(EXIT_FAILURE);
		}
		mtime = sf.st_mtime;
		new_times.actime = sf.st_atime - (time_t)TEN_DAYS;   
		new_times.modtime = sf.st_mtime - (time_t)TEN_DAYS;  
		utime(argv[i], &new_times);	
	}
	exit(EXIT_SUCCESS);
}


