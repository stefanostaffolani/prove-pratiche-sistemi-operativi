#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]){
	char buf[PATH_MAX];

	if(argc != 2){
		perror("argc");
		exit(EXIT_FAILURE);
	}

	char *res = realpath(argv[1], buf);
	if(res){
		printf("source is at %s\n", buf);
	}else{
		perror("errore realpath");
		exit(EXIT_FAILURE);
	}
	if(unlink(argv[1]) != 0){
		perror("unable to unlink");
		exit(EXIT_FAILURE);
	}	
	if(symlink(buf, argv[1]) != 0){
		perror("symlink err");
		exit(EXIT_FAILURE);
	}	
	exit(EXIT_SUCCESS);
}


