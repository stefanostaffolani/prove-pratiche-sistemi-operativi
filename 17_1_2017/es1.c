#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct file_list{
	ino_t inode;
	struct file_list*next;
} *p_file;

p_file add_to_list(p_file head, p_file new){
	if(head == NULL)
		return new;
	else{
		new->next = head;
		head = new;
		return head;
	}
}

int search_list(p_file head ,ino_t inode){
	p_file iter = head;
	while(iter != NULL){
		if (iter->inode == inode)
			return 1;
		iter = iter->next;
	}
	return 0;
}

p_file tot_files_and_dirs(char *path, p_file head){
	DIR *dir = opendir(path);
	struct dirent *entry;
	struct stat sb;
	if(dir){
		while((entry = readdir(dir)) != NULL){
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;

			if(entry->d_type == DT_DIR){
				char *buf = (char *)malloc(PATH_MAX);
				getcwd(buf, PATH_MAX);
				strncat(buf, "/",  PATH_MAX-strlen(buf));
				strncat(buf, entry->d_name, PATH_MAX-strlen(buf));
				//printf("%s\n", buf);
				stat(buf, &sb);
				printf("inode : %d\n", sb.st_ino);
				if(!search_list(head, sb.st_ino)){
					p_file new = (p_file)malloc(sizeof(struct file_list));
					new->inode = sb.st_ino;
					new->next = NULL;
					head = add_to_list(head, new);
				}
				head = tot_files_and_dirs(buf, head);
			}else if(entry->d_type == DT_REG){
				char *buf = (char *)malloc(PATH_MAX);
				getcwd(buf, PATH_MAX);
				strncat(buf, "/",  PATH_MAX-strlen(buf));
				strncat(buf, entry->d_name, PATH_MAX-strlen(buf));
				printf("%s\n", buf);
				stat(buf, &sb);
				printf("inode : %d\n", sb.st_ino);
				if(!search_list(head, sb.st_ino)){
					p_file new = (p_file)malloc(sizeof(struct file_list));
					new->inode = sb.st_ino;
					new->next = NULL;
					head = add_to_list(head, new);
				}
			}
		}
		closedir(dir);
	}
	return head;
}

int list_len(int n, p_file head){
	if(head != NULL)
		return list_len(n+1, head->next);
	else
		return n;
}


int main(int argc, char *argv[]){
	p_file head = NULL;
	head = tot_files_and_dirs(argv[1], head);
	printf("tot files and dirs : %d\n",list_len(0, head));
	exit(EXIT_SUCCESS);
}
