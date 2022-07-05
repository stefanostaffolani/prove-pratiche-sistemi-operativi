
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	//char buf[PATH_MAX];
	DIR* dir;
	FILE *entry_file;
	struct dirent *in_file;
	//char files[1000];
	int i;

	if (argc != 2){
		perror("argc");
		exit(EXIT_FAILURE);
	}

	dir = opendir(argv[1]);

	if (dir == NULL){
		perror("can't open dir");
		exit(EXIT_FAILURE);
	}

	while((in_file = readdir(dir)) != NULL){
		char buf[PATH_MAX];
		char *res = realpath(argv[1], buf);
		if(res){
			printf("source is at %s\n", buf);
		}else{
			perror("errore realpath");
			exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);
}


