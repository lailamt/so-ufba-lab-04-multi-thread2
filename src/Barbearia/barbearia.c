/*
  O programa deve ser executado desta maneira:
      gcc barbearia.c -o barbearia -std=c99 -Wall -lpthread

    ./barbearia

*/

#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "filaCliente.c"    // Fila de clientes que vao esperar para cortar o cabelo
#include "filaBarbeiro.c"   // Fila dos barbeiros para entregar dinheiro ao caixa 
#include "mensagens.h"      // Mensagens sobre o que esta ocorrendo
#include "funcoesThread.c"  // Funcoes onde ocorrem de fato as operacoes

int main(){

    // Inicializando os mutexes e os semaforos
    pthread_mutex_init(&pararFila,NULL);
    pthread_mutex_lock(&pararFila);

    pthread_mutex_unlock(&pararFila);

    sem_init(&capacidadeDeClientes, 0, capacidadeMaxima);

    for(int i=0; i<qtdMaxClientes; i++){
        sem_init(&cliente[i], 0, 0);
    }

    sem_init(&pagamento, 0, 0);
    sem_init(&clientes, 0, 0);

    for(int i=0; i<qtdMaxBarbeiros; i++){
        sem_init(&barbeiro[i], 0, 0);
    }

    sem_init(&barbeiros, 0, 0);
    sem_init(&corteDoCabelo, 0, 0);
    sem_init(&entregarDinheiro, 0, 0);

    pthread_mutex_init(&filaDoCliente, NULL);
    pthread_mutex_init(&filaDoBarbeiro, NULL);
    
    pthread_t threadBarbeiro[qtdMaxBarbeiros];       //declaracao das threads do barbeiro
    pthread_t threadCliente[qtdMaxClientes];         // declaracao das threads dos clientes
    pthread_t threadCaixa;                          //declaracao das threads do caixa

    long i=0;

    pthread_mutex_lock(&pararFila);
    pthread_mutex_unlock(&pararFila);

    pthread_create(&threadCaixa,NULL,CaixaRegistradora,NULL);   // criando thread do caixa

    pthread_mutex_lock(&pararFila);
    pthread_mutex_unlock(&pararFila);

    while (i < qtdMaxBarbeiros){
        pthread_create(&threadBarbeiro[i],NULL,Barbeiro,(void *)i);//criando thread dos barbeiros
        i++;
    }

    i=0;

    while( i<qtdMaxClientes) {
        srand(time(NULL));
        sleep(rand() % 4 + 1);
        pthread_create(&threadCliente[i],NULL,Cliente,(void *)i);//criando thread dos clientes
        i++;
    }
}