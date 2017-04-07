#include "action.h"
#include <stdio.h>
#include <string.h>
extern char** argv_2;

void action(Action type, char* file_name, char* path){
	char dir_path[350];

	strcpy(dir_path,path);
	strcat(dir_path,"/");
	strcat(dir_path, file_name);

	switch(type){

		//-print
		case PRINT:
			;
			char * dir_path_aux = dir_path;
			while((dir_path_aux[0] == '/') && (dir_path_aux[1] == '/'))
			{
				dir_path_aux++;
			}
			printf("%s\n", dir_path_aux);
			break;

			//-delete
		case DELETE:
			if(access(dir_path, W_OK)!=-1){
				struct stat s;
				stat(dir_path,&s);
				if(s.st_mode & S_IFDIR){
					if(rmdir(dir_path) ==-1){
						char* msg = strerror(errno);
						write(STDOUT_FILENO, "Cannot delete: ", 15);
						write(STDOUT_FILENO, file_name, strlen(file_name));
						write(STDOUT_FILENO, ", ", 2);
						write(STDOUT_FILENO, msg, strlen(msg));
						write(STDOUT_FILENO, "\n", 1);
					}
				}else
					if(unlink(dir_path) == -1){
						char* msg = strerror(errno);
						write(STDOUT_FILENO, "Cannot delete: ", 15);
						write(STDOUT_FILENO, file_name, strlen(file_name));
						write(STDOUT_FILENO, ", ", 2);
						write(STDOUT_FILENO, msg, strlen(msg));
						write(STDOUT_FILENO, "\n", 1);
					}
			}
			else{
				write(STDOUT_FILENO, "No permission to delete file: ", 30);
				write(STDOUT_FILENO, file_name, strlen(file_name));
				write(STDOUT_FILENO, "\n", 1);
			}
			break;

			//-exec
		case EXEC:
			;

			if(!fork()){

				int i;
				for(i=0; (strcmp(argv_2[i],";") && (argv_2[i]!=0)); i++){
					if(!strcmp(argv_2[i],"{}")){
						argv_2[i] = dir_path;
					}
				}
				argv_2[i] = 0;
				execvp(argv_2[0],argv_2);
				_exit(9);
			}else
				wait(0);
			break;
	}
}
