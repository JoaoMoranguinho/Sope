#include "search.h"
extern int child_counter;
extern struct sigaction oldsigaction;
char cwd[350];

char * getDir(char *str){

	getcwd(cwd, sizeof(cwd));
	if(str[1] == '.'){
		int i;
		for(i = strlen(cwd)-1; cwd[i]!='/'; i--);
		cwd[i] = '\0';
	}

	return cwd;
}

void search(Search search_type, Action action_type , char* name_type_mode, char* dir_path)
{

	//realpth
	struct dirent *dentry;
	DIR *dir;
	struct stat stat_entry;

	char dir_path_alt[350];
	realpath(dir_path, dir_path_alt);

	//erro com path
	if ((dir = opendir(dir_path_alt)) == NULL){
		perror(dir_path_alt);
		_exit(11);
	}


	while((dentry = readdir(dir)) != NULL){
		//verifica se path é nó de origem
		if(!strcmp(dentry->d_name,"..") || !strcmp(dentry->d_name,".")){
			continue;
		}

		char filepath[350];
		strcpy(filepath,dir_path_alt);
		strcat(filepath,"/");
		strcat(filepath,dentry->d_name);
		//verifica informação do ficheiro em filepath
		lstat(filepath, &stat_entry);

		switch(search_type){

			//-name
			case NAME:
				if(!strcmp(dentry->d_name,name_type_mode)){
					action(action_type, dentry->d_name, dir_path);
				}
				break;

				//-type
			case TYPE:
				switch((char)name_type_mode[0]){
					case 'f':
						if(S_ISREG(stat_entry.st_mode)){
							action(action_type, dentry->d_name, dir_path);
						}
						break;
					case 'd':
						if(S_ISDIR(stat_entry.st_mode)){
							action(action_type, dentry->d_name, dir_path);
						}
						break;
					case 'l':
						if(S_ISLNK(stat_entry.st_mode)){
							action(action_type, dentry->d_name, dir_path);
						}
						break;
				}
				break;

				//-perm
			case PERM:
				;
				char mode_permissions_[5];
				char *mode_permissions;
				sprintf(mode_permissions_, "%o" ,(stat_entry.st_mode));
				mode_permissions = (mode_permissions_+(strlen(mode_permissions_)-3));
				if(!strcmp(mode_permissions, name_type_mode)){
					action(action_type, dentry->d_name, dir_path);
				}
				break;
		}
sleep(1);
		if(S_ISDIR(stat_entry.st_mode)){
			char pathname[350];
			strcpy(pathname, dir_path);
			strcat(pathname,"/");
			strcat(pathname, dentry->d_name);

			if((action_type == DELETE) && (access(pathname, F_OK)==-1)){
				//itwasdeleted
				continue;
			}
			if(fork()){
				child_counter++;
			}else
			{

				sigaction(SIGTSTP, &oldsigaction,0);
				signal(SIGINT, SIG_IGN);
				child_counter = 0;
				search(search_type, action_type, name_type_mode, pathname);

				while(child_counter--){
					wait(0);
				}
				exit(0);
			}
		}
	}
}
