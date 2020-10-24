
/*
  O programa deve ser executado desta maneira:
      gcc monitorDorminhoco.c -o monitorDorminhoco -std=c99 -Wall -lpthread

    ./monitorDorminhoco

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#define qtdMaxCadeiras 3 //qtdMaxCadeiras representa o número de cadeiras da sala de espera

int inicio = 0;
int fim = 0;
int qtdEstudantes = 0;
int filaAtendEstudantes[qtdMaxCadeiras+1];//Utiliza-se qtdMaxCadeiras+1, pois é contabilizado tambem a cadeira do monitor



//A mutex is a MUTual EXclusion device, and is useful for protecting shared data structures 
//from concurrent modifications, and implementing critical sections and monitors. 

//mutex deve ser uma variável  do tipo pthread_mutex_t que é um mutex (para indicar "mutual exclusion") 
//e serve para proteger uma região crítica. Uma thread para proteger uma região crítica deve dar um pthread_mutex_lock 
//para obter exclusão mútua e pthread_mutex_unlock para liberar a região crítica.

pthread_mutex_t pararFila;

    void colocaNaFila(int estudante);// poe o estudante na fila para ser atendido
    int tiraDaFila();// retira o estudante da fila apos ser atendido
    void* estudante(void* arg);//funcao para a criacao da thread do estudante
    void* monitor();//funcao para a criacao da thread do monitor


int main(){

  //The pthread_mutex_init() function shall initialize the mutex referenced by mutex with attributes specified by attr.
  // If attr is NULL, the default mutex attributes are used; the effect shall be the same as passing the address of a default 
  //mutex attributes object. Upon successful initialization, the state of the mutex becomes initialized and unlocked. 
  //int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
  pthread_mutex_init(&pararFila, NULL);

  int i;
  pthread_t threadMonitor, threadEstudante;

  pthread_create(&threadMonitor, NULL, monitor, NULL);
  srand(time(NULL));
  for (i = 0 ; ; ++i){// aqui pode setar o limite para a quantidade de estudantes a serem atendidos
    sleep(rand() % 4 + 1); //tempo para a chegada de estudantes
    pthread_create(&threadEstudante, NULL, estudante, &i);
  }

  return 0;
}

void colocaNaFila(int estudante){
  if (qtdEstudantes < qtdMaxCadeiras+1){
    if (!qtdEstudantes){// checando se a fila/quantidadeDeEstudantes esta vazia
      printf("O estudante %d acorda o monitor e senta em sua cadeira.\n", estudante);
    }
    else{
      printf("O estudante %d senta em uma das cadeiras vagas da sala de espera.\n", estudante);
    }

    filaAtendEstudantes[fim] = estudante;
    fim = (fim+1) % (qtdMaxCadeiras+1);

    qtdEstudantes++;
  }else
    printf("Todas as cadeiras estao ocupadas, o estudante %d foi embora.\n", estudante);
}

int tiraDaFila(){
  if (qtdEstudantes){//checando se existem estudantes
    srand(time(NULL));
    sleep(rand() % 4 + 1); //tempo que o monitor demora para atender o estudante
    printf("O monitor terminou de atender o estudante %d, em seguida o estudante vai embora.\n", filaAtendEstudantes[inicio]);

    int estudante = filaAtendEstudantes[inicio];
    inicio = (inicio+1) % (qtdMaxCadeiras+1);
    qtdEstudantes--;

    if (!qtdEstudantes)// checando se a fila/quantidadeDeEstudantes esta vazia
      printf("Não há estudantes para serem atendidos, o monitor vai dormir.\n");
    else
      printf("O estudante %d senta na cadeira do monitor.\n", filaAtendEstudantes[inicio]);

    return estudante;
  }else
    //caso chegue aqui é pq aconteceu algum erro
    return -1;
}

void* estudante(void* arg){
  unsigned long idEstudante = *((unsigned long*) arg);

  pthread_mutex_trylock(&pararFila);
  colocaNaFila(idEstudante);
  pthread_mutex_unlock(&pararFila);
}

void* monitor(){
  for ( ; ; ){
    pthread_mutex_trylock(&pararFila);
    tiraDaFila();
    pthread_mutex_unlock(&pararFila);
  }
}