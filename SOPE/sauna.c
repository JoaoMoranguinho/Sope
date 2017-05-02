#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <string.h>

int readline(int fd, char *str);
void *entrada_func(void *arg);


int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("Usage: sauna <n.lugares> <un.tempo>\n");
	}
	else
	{

		pthread_t tid;
		int retcode;
		void * retval;

		retcode = pthread_create(&tid, NULL, entrada_func, NULL);
		retcode = pthread_join(tid, &retval);

		sleep(1);
	}

	return 0;
}


int readline(int fd, char *str)
{
	int n;
	do
	{
		n = read(fd,str,1);
	}
	while (n>0 && *str++ != '\0');
	return (n>0);
}

void *entrada_func(void *arg){
	int   i, fd , n, nF=0, nM=0;
	char  str[100], npedido[2], genero, tempo[2];
	mkfifo("entrada",0660);
	fd=open("entrada",O_RDONLY);
	n=1;
	while(readline(fd,str)){
		printf("%s",str);
		
		if(n < 10)
		{
		strncpy(npedido, str + 2, 4 - 2);
		genero = str[6];
		//strncpy(genero, str + 6, 7 - 6);
		strncpy(tempo, str + 10, 11 - 10);
		}
		else
		{
		strncpy(npedido, str + 3, 5 - 3);
		genero = str[7];
		//strncpy(genero, str + 6, 7 - 6);
		strncpy(tempo, str + 11, 12 - 11);
		}

		switch(genero){
			case 'F': nF++;
			break;

			case 'M': nM++;
		}

		if(nF<4 && nM<4){
		printf("npedido: %d\n", atoi(npedido) );
		printf("genero: %c\n", genero);
		printf("tempo: %d\n", atoi(tempo) );
		}
		else{
		printf("npedido: %d\n", atoi(npedido) );
		printf("genero: %c\n", genero);
		printf("tempo: %d\n", atoi(tempo) );
		printf("Rejeitado \n");	
		}
		n++;
		
	} 
	close(fd);

	return NULL;
}