#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_ARGS 10

typedef struct node{
	struct node *next;
	char *cmd[MAX_ARGS];
} node_t;

node_t *add_to_tail(node_t *head, node_t *new){
	if(head == NULL){
		head = new;
	}else{
		node_t *iter = head;
		while(iter->next != NULL){
			iter = iter->next;
		}
		iter->next = new;
	}
	return head;
}

int main(int argc, char * argv[]){
	if(argc < 2){
		printf("usage ./a.out MAX cmd1...\n");
		exit(EXIT_FAILURE);
	}
	
	node_t *head = NULL;
	int n = 1;	// numero di comandi
	for (int i = 1; i < argc; i++){
		if(!strcmp(argv[i], "//"))
			n++;
	}

	for(int i = 0; i < n; i++){
		node_t *tmp = malloc(sizeof(node_t));
		head = add_to_tail(head, tmp);
		tmp->next = NULL;
	}

	node_t *iter = head;
	int j = 0;
	for(int i = 1; i < argc; i++){
		if(strcmp(argv[i], "//")){
			iter->cmd[j] = argv[i];
			j++;
		}else{
			iter->cmd[j] = NULL;
			iter = iter->next;
			j = 0;
		}
	}
	
	iter->cmd[j] = NULL;   // mette terimantore per ultimo cmd
	
	iter = head;
	
	while(n > 0){             // exec
		switch(fork()){
			case -1:
				perror("fork");
				exit(EXIT_FAILURE);
				break;
			case 0:
				execvp(iter->cmd[0], iter->cmd);	
				break;
			default:
				//iter = iter->next;
				n--;
				iter = iter->next;    // passa al prossimo comando
				wait(NULL);
				break;
		}
	}

	node_t *helper = head;
	while(head != NULL){       // libera lo spazio
		head = head->next;
		free(helper);
		helper = head;
	}
	exit(EXIT_SUCCESS);
}

