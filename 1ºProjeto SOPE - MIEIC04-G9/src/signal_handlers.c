#include <stdio.h>
#include "signal_handlers.h"

void sig_handler(int sig){
	if(sig == SIGINT){

		char input;
		printf("\nAre you sure you want to terminate? \ny -yes \nn -no\n");
		kill(0, SIGTSTP); //envia sinal Stop ao processo pai

		do{
			read(STDIN_FILENO, &input, 1);
			if (input == 'Y' || input == 'y')
			{
				kill(0,SIGTERM); //envia sinal de Terminacao ao proceso pai
			}else
				if (input == 'N' || input == 'n')
				{
					kill(0,SIGCONT); //envia sinal ao processo pai para continuar
					break;
				}
		}while(input != 'Y' && input != 'y' && input != 'N' && input != 'n');
	}

}
