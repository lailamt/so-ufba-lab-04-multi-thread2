#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

int N1=0, N2=0;
int qtdX=0, qtdY=0, qtdZ=0;
int ib1=0, ib2=0, m1=1, m2=1;

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
    int eb1=N1, eb2=N2;

    //iniciar semáforos
    sem_init (&buffer1_empty, 0, eb1);
    sem_init (&buffer1_full, 0, 0);
    sem_init (&buffer1_mutex, 0, 1);

    sem_init (&buffer2_empty, 0, eb2);
    sem_init (&buffer2_full, 0, 0);
    sem_init (&buffer2_mutex, 0, 1);

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

    for(int i = 0; i < qtdX; i++){
        pthread_join(threadX[i], NULL);
    }
    for(int i = 0; i < qtdY; i++){
        pthread_join(threadY[i], NULL);
    }
    for(int i = 0; i < qtdZ; i++){
        pthread_join(threadZ[i], NULL);
    }
    
    // printf("x: %d; y: %d; z: %d\n", X, Y, Z);
    // printf("n1: %d; n2: %d\n", N1, N2);
}

/*
void tempo(int n){
    sleep(rand()%n); // pausa entre 0 e n seg
    usleep(rand()%1000000); // pausa entre 0 e 1 seg
}
*/

void *X(){
    // printf("New thread X created!\nthread_x = %d\n", count_threads_x);
    int id = count_threads_x;
    count_threads_x++;

    while(1){
        sem_wait(&buffer1_empty);
        sem_wait(&buffer1_mutex);
        // printf("thread X%d\n", id);
        buffer1_count++;
        printf("item foi inserido no buffer B1\nbuffer1_count: %d\n", buffer1_count);
        sem_post(&buffer1_mutex);
        sem_post(&buffer1_full);
        sleep(rand()%5);
    } //fim_while
}

void *Y(){
    // printf("New thread Y created!\nthread_y = %d\n", count_threads_y);
    int id = count_threads_y;
    count_threads_y++;

    while(1){
        sem_wait(&buffer1_full);
        sem_wait(&buffer1_mutex);
        // printf("thread Y%d\n", id);
        buffer1_count--;
        printf("item retirado do buffer B1\nbuffer1 count: %d\n", buffer1_count);
        sem_post(&buffer1_mutex);
        sem_post(&buffer1_empty);

        sem_wait(&buffer2_empty);
        sem_wait(&buffer2_mutex);
        buffer2_count++;
        printf("item inserido no buffer B2\nbuffer2 count: %d\n", buffer2_count);
        sem_post(&buffer2_mutex);
        sem_post(&buffer2_full);
        sleep(rand()%5);
    } // fim_while
}

void *Z(){
    // printf("New thread Z created!\nthread_z = %d\n", count_threads_z);
    int id = count_threads_z;
    count_threads_z++;

    while(1){
        sem_wait(&buffer2_full);
        sem_wait(&buffer2_mutex);
        // printf("thread Z%d\n", id);
        buffer2_count--;
        printf("item retirado do buffer B2\nbuffer2_count: %d\n", buffer2_count);
        sem_post(&buffer2_mutex);
        sem_post(&buffer2_empty);
        sleep(rand()%5);   
    } // fim_while
}