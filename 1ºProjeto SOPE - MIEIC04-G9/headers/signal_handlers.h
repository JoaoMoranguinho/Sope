#ifndef _SIGNAL_HANDLERS
#define _SIGNAL_HANDLERS

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int signo);

void sig_handler_2(int signo);


#endif
