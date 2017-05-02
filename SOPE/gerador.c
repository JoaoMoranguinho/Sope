#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/file.h>
#include <time.h>


void *gerador_func(void *arg);
void *messager_func(void *arg);

struct gerador_data {
int  npedidos;
int  maxtempo;
 };


struct gerador_data gerador;

int main(int argc, char *argv[])
{
  

  if (argc < 4){
  printf("Usage: gerador <n.pedidos> <max.utilizacao> <un.tempo>\n");
}

  else{

  int npedidos = atoi(argv[1]);
  int maxtempo = atoi(argv[2]);
  

  printf("Gerador Criado na main.....\n");

  int retcode;
  void * retval;  
  pthread_t tid, tid2;
  gerador.npedidos = npedidos;
  gerador.maxtempo = maxtempo;
  retcode = pthread_create(&tid, NULL, gerador_func, (void *) &gerador);
  //retcode = pthread_create(&tid2, NULL, messager_func, NULL);



  retcode = pthread_join(tid, &retval);
  //retcode = pthread_join(tid2, &retval);
  sleep(3);

  srand(time(NULL));

  printf("<------------------------------------------>\n");

  
}

return 0; 

}


void *gerador_func(void *arg)
{
  int i, numeropedido, tempo, rand1, rand2;
  char genero;
  int pid = getpid();
  char  pidstring[13];
  char filename[100];   // array to hold the result.
  time_t rawtime;
  struct tm * timeinfo;


  sprintf(pidstring, "%d", pid);

  strcpy(filename,"ger.");
  strcat(filename,pidstring);

  FILE *fp;

  fp = fopen(filename, "w+");

  printf("Gerador Inicializado.....\n");
  printf("pid: %s\n",pidstring);
  sleep(1);
  struct gerador_data *data;
  data = (struct gerador_data *) arg;
  int npedidos = data->npedidos;
  int maxtempo = data->maxtempo;
  int   fd, messagelen;
  char  message[100];
  
  do
  {
    fd=open("entrada",O_WRONLY);
    if (fd==-1) sleep(1);
  }
  while (fd==-1);

  for(i=0; i < npedidos ; i++)
    {
      numeropedido = i+1;
      rand1 = rand() % 2;
      rand2 = rand() % maxtempo +1;

      switch(rand1){
        case 0:
        genero = 'M';
        break;

        case 1:
        genero = 'F';
        break;

      }
      
      tempo = rand2;
      /*
      time ( &rawtime );
      timeinfo = localtime ( &rawtime );
      */

      time_t result = time(NULL);
      
      fprintf(fp, "%s - %s - %d : %c - %d \n" , asctime(gmtime(&result)) ,pidstring , numeropedido , genero , tempo);

      sprintf(message,"n-%d g-%c t-%d\n", i+1, genero , tempo);
      messagelen=strlen(message)+1;
      write(fd,message,messagelen);

      printf("Numero do pedido: %d ", numeropedido);
      printf("Genero: %c ", genero);
      printf("Tempo de utilizacao: %d\n", tempo);
      sleep(1);
  
  }
  fclose(fp);
  close(fd);

  printf("Gerador Terminado.....\n");

//tasknum = my_data->thread_num;
//value = my_data->value;
//hello_msg = my_data->message;
return NULL;
}


void *messager_func(void *arg){

  int   fd, messagelen, i;
  char  message[100];
  do
  {
    fd=open("entrada",O_WRONLY);
    if (fd==-1) sleep(1);
  }
  while (fd==-1);

  for (i=1; i<=3; i++)
  {
  sprintf(message,"Hello no. %d from process %d\n", i, getpid());
  messagelen=strlen(message)+1;
  write(fd,message,messagelen);
  sleep(3);
  }
  close(fd);

  return NULL;
}
