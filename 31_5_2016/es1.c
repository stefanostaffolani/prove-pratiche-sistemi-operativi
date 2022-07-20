#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// soluzione naive con array e lunghezza prefisssata

typedef struct name{
	int val;   // suffix
	char name[30];
}name_t;

int parse_name(char *name){
	char *token = strtok(name, ".");
	char *last = malloc(256);
	while(token != NULL){
		strncpy(last, token, 256);
		token = strtok(NULL, ".");
	}
	if (last != NULL){
		int ret = atoi(last);
		if (ret != 0)  // atoi success
			return ret;
	}		
	return -1;
}

int cmp_p_name(const void *a, const void *b){
	name_t *aa = (name_t *) a;
	name_t *bb = (name_t *) b;
	return (aa->val - bb->val);
}

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("usage: ./es path\n");
		exit(EXIT_FAILURE);
	}
	name_t arr[30];
	DIR *dir = opendir(argv[1]);
	struct dirent *entry;
	int curr = 0;
	if(dir){
		while((entry = readdir(dir)) != NULL){
			if(entry->d_type == DT_REG){
				char *cpname = malloc(strlen(entry->d_name));
				strncpy(cpname, entry->d_name, strlen(entry->d_name));
				int val = parse_name(cpname);
				if(val == -1){
					continue;
				}
				arr[curr].val = val;
				strcpy(arr[curr].name, entry->d_name);
				curr++;
			}
		}
		closedir(dir);
	}
	qsort(arr, curr, sizeof(name_t), cmp_p_name);
	for(int i = 0; i < curr; i++)
		printf("%s\n",arr[i].name);
	exit(EXIT_SUCCESS);
}
