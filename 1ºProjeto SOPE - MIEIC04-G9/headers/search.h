#ifndef _SEARCH
#define _SEARCH

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <wait.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "action.h"
#include "macros.h"

void sig_handler_2(int signo);

void search(Search search_type, Action action_type , char* name_type_mode, char* dir_path);

#endif
