/*
O programa deve ser executado desta maneira:
    gcc prodCons.c -o procon -std=c99 -Wall -lpthread
    ./procon
!!! Ou usa o make !!!
    make procon
    ./build/procon
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

// int ib1=0, ib2=0, m1=1, m2=1;

int N1=0, N2=0;
int qtdX=0, qtdY=0, qtdZ=0;

int count_threads_x = 1, count_threads_y = 1, count_threads_z = 1;
int buffer1_count = 0, buffer2_count = 0;

sem_t buffer1_empty, buffer1_full,buffer1_mutex, buffer2_empty, buffer2_full, buffer2_mutex; // mutex para acesso aos buffers
sem_t threads, capacidades; // semáforos para o controle de capacidade do buffer e de threads

void tempo(int n);
void *X(); // X é produtor em B1
void *Y(); // Y é consumidor em B1 e produtor em B2
void *Z(); // Z é consumidor em B2

int main(int argc, char*argv[]){

    //le qtd de threads e tamanhos dos buffers
    printf("Insira a quantidade de threads para X, Y e Z: ");
    scanf("%d %d %d", &qtdX, &qtdY, &qtdZ);
    printf("Insira as capacidades dos buffers B1 e B2: ");
    scanf("%d %d", &N1, &N2);
    // int eb1=N1, eb2=N2;

    // iniciar semáforos
    sem_init (&buffer1_empty, 0, N1);
    sem_init (&buffer1_full, 0, 0);
    sem_init (&buffer1_mutex, 0, 1);

    sem_init (&buffer2_empty, 0, N2);
    sem_init (&buffer2_full, 0, 0);
    sem_init (&buffer2_mutex, 0, 1);

    // iniciar threads
    pthread_t threadX[qtdX];
    pthread_t threadY[qtdY];
    pthread_t threadZ[qtdZ];

    for(int i = 0; i < qtdX; i++){
        pthread_create(&(threadX[i]), NULL, X, NULL);
    }
    for(int i = 0; i < qtdY; i++){
        pthread_create(&(threadY[i]), NULL, Y, NULL);
    }
    for(int i = 0; i < qtdZ; i++){
        pthread_create(&(threadZ[i]), NULL, Z, NULL);
    }

    pthread_exit(NULL);

/*     for(int i = 0; i < qtdX; i++){
        pthread_join(threadX[i], NULL);
    }
    for(int i = 0; i < qtdY; i++){
        pthread_join(threadY[i], NULL);
    }
    for(int i = 0; i < qtdZ; i++){
        pthread_join(threadZ[i], NULL);
    } */
    
    // printf("x: %d; y: %d; z: %d\n", X, Y, Z);
    // printf("n1: %d; n2: %d\n", N1, N2);
}

/*
// Função pra gerar o valor aleatório, achei melhor colocar direto dentro das outras funções
void tempo(int n){
    sleep(rand()%n); // pausa entre 0 e n seg
}
*/

/*
// Como a própria questão não diz que é preciso entrar em detalhes quanto a estas funções
// achei melhor nem gastar tempo com o desenvolvimento dela.
// O resultado do que seria, está dentro das funções de X, Y e Z.
void insere(){}
void remove(){} 
*/

void *X(){
    // printf("New thread X created!\nthread_x = %d\n", count_threads_x);
    // int id = count_threads_x;
    // count_threads_x++;

    while(1){
        sem_wait(&buffer1_empty);   // semáforo que verifica se o buffer ta vazio
        sem_wait(&buffer1_mutex);   // semáforo que da block na seção crítica
        // printf("thread X%d\n", id);
        // buffer1_count++;
        //printf("item foi inserido no buffer B1\nbuffer1_count: %d\n", buffer1_count);
        printf("item foi inserido no buffer B1\n");
        sem_post(&buffer1_mutex);   // semáforo desbloqueia a seção crítica
        sem_post(&buffer1_full);    // semáforo que verifica se o buffer tá cheio
        sleep(rand()%5);            // tempo de sleep randomico
    } //fim_while
}

void *Y(){
    // printf("New thread Y created!\nthread_y = %d\n", count_threads_y);
    // int id = count_threads_y;
    // count_threads_y++;

    while(1){
        sem_wait(&buffer1_full);    // semáforo que verifica se o buffer tá cheio
        sem_wait(&buffer1_mutex);   // semáforo que da block na seção crítica
        // printf("thread Y%d\n", id);
        // buffer1_count--;
        // printf("item retirado do buffer B1\nbuffer1 count: %d\n", buffer1_count);
        printf("item foi retirado do buffer B1\n");
        sem_post(&buffer1_mutex);   // semáforo desbloqueia a seção crítica
        sem_post(&buffer1_empty);   // semáforo que verifica se o buffer ta vazio

        sem_wait(&buffer2_empty);   // semáforo que verifica se o buffer ta vazio
        sem_wait(&buffer2_mutex);   // semáforo que da block na seção crítica
        // buffer2_count++;
        // printf("item inserido no buffer B2\nbuffer2 count: %d\n", buffer2_count);
        printf("item foi inserido no buffer B2\n");
        sem_post(&buffer2_mutex);   // semáforo desbloqueia a seção crítica
        sem_post(&buffer2_full);    // semáforo que verifica se o buffer tá cheio
        sleep(rand()%5);            // tempo de sleep randomico
    } // fim_while
}

void *Z(){
    // printf("New thread Z created!\nthread_z = %d\n", count_threads_z);
    // int id = count_threads_z;
    // count_threads_z++;

    while(1){
        sem_wait(&buffer2_full);    // semáforo que verifica se o buffer tá cheio
        sem_wait(&buffer2_mutex);   // semáforo que da block na seção crítica
        // printf("thread Z%d\n", id);
        // buffer2_count--;
        // printf("item retirado do buffer B2\nbuffer2_count: %d\n", buffer2_count);
        printf("item foi retirado do buffer B2\n");
        sem_post(&buffer2_mutex);   // semáforo desbloqueia a seção crítica
        sem_post(&buffer2_empty);   // semáforo que verifica se o buffer ta vazio
        sleep(rand()%5);            // tempo de sleep randomico
    } // fim_while
}