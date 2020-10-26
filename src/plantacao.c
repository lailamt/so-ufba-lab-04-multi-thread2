/*
O programa deve ser executado desta maneira:
    gcc plantacao.c -o plantacao -std=c99 -Wall -lpthread
    ./plantacao
!!! Ou usa o make !!!
    make planta
    ./build/planta
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

int MAX;
int vazios = 0, fechar = 0;

sem_t pa; // mutex para acesso aos buffers
sem_t buracos, afechar; // semáforos para o controle de capacidade do buffer

void tempo(int n);
void *Joao(); // X é produtor em B1
void *Pedro(); // Y é consumidor em B1 e produtor em B2
void *Paulo(); // Z é consumidor em B2

int main(int argc, char*argv[]){

    //le qtd de máxima de buracos possíveis
    printf("Insira a quantidade máxima de buracos que João pode cavar: ");
    scanf("%d", &MAX);

    //iniciar semáforos
    sem_init (&buracos, 0, MAX);
    sem_init (&afechar, 0, 0);
    sem_init (&pa, 0, 1);

    //iniciar threads
    pthread_t threadJoao;
    pthread_t threadPedro;
    pthread_t threadPaulo;

    pthread_create(&(threadJoao), NULL, Joao, NULL);
    pthread_create(&(threadPedro), NULL, Pedro, NULL);
    pthread_create(&(threadPaulo), NULL, Paulo, NULL);

    pthread_exit(NULL);
}

/*
void tempo(int n){
    sleep(rand()%n); // pausa entre 0 e n seg
    usleep(rand()%1000000); // pausa entre 0 e 1 seg
}
*/

void *Joao(){
    while(1){
        // if (vazios < MAX){
            sem_wait(&buracos);
            sem_wait(&pa);
            vazios++;
            printf("João cavou! Total vazios: %d.\n", vazios);
            sem_post(&pa);
            sleep(rand()%5);
    //    } //fim_if
    } //fim_while
}

void *Pedro(){
    while(1){
        if(vazios > 0){
            sem_post(&afechar);
            vazios--;
            fechar++;
            printf("Pedro semeou! Total vazios: %d. Total a fechar: %d.\n", vazios, fechar);
            sleep(rand()%5);
        } // fim_if
    } // fim_while
}

void *Paulo(){
    while(1){
        // if(fechar > 0){
            sem_wait(&afechar);
            sem_wait(&pa);
            fechar--;
            printf("Paulo fechou! Total a fechar: %d.\n", fechar);
            sem_post(&pa);
            sem_post(&buracos);
            sleep(rand()%5);   
        // } // fim_if
    } // fim_while
}