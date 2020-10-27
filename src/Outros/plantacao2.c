#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>


#define FREE 1
#define BUSY 0

#define B1_SIZE 5
#define B2_SIZE 5

#define MAX_HOLES 5

int emptyHoles, toCloseHoles, holes;
int shovel = FREE;

sem_t holesSem, emptyHolesSem, toCloseHolesSem;
sem_t shovelMutex;


void espera(int n)
{
  sleep (random() % n) ;	// pausa entre 0 e n segundos (inteiro)
  usleep (random() % 1000000) ;	// pausa entre 0 e 1 segundo (float)
}

void * joao() {
    printf("OI, TUDO BEM? EU SOU JOÃO\n");

    while (1) {

        if (holes <= MAX_HOLES) {
            printf("JOÃO QUER PEGAR A PÁ\n");
            sem_wait(&shovelMutex);

            sem_post(&holesSem);
            sem_post(&emptyHolesSem);

            emptyHoles++;
            holes++;

            shovel = BUSY;
            printf("JOÃO CAVA UM BURACO (emptyHoles:%d|toCloseHoles:%d|holes:%d)\n", emptyHoles, toCloseHoles, holes);
            shovel = FREE;
            
            sem_post(&shovelMutex);
        }
        espera(5);

    } 

}

void * pedro() {
    printf("OI, TUDO BEM? EU SOU PREDO\n");

    while (1) {
        if (emptyHoles > 0) {

            sem_post(&toCloseHolesSem);
            sem_wait(&emptyHolesSem);

            toCloseHoles++;
            emptyHoles--;

            printf("PREDO SEMEIA (emptyHoles:%d|toCloseHoles:%d|holes:%d)\n", emptyHoles, toCloseHoles, holes);
        }
        espera(5);
    } 

}

void * paulo() {
    printf("OI, TUDO BEM? EU SOU PAULO\n");

    while (1) {
        if (toCloseHoles > 0) {
            printf("PAULO QUER PEGAR A PÁ\n");
            sem_wait(&shovelMutex);

            sem_wait(&toCloseHolesSem);
            sem_wait(&holesSem);

            toCloseHoles--;
            holes--;

            shovel = BUSY;
            printf("PAULO FECHA UM BURACO (emptyHoles:%d|toCloseHoles:%d|holes:%d)\n", emptyHoles, toCloseHoles, holes);
            shovel = FREE;
            
            sem_post(&shovelMutex);
        }
        espera(5);
    } 

}

int main(int argc, char*argv[]) {
    pthread_t joaoThread;
    pthread_t pedroThread;
    pthread_t pauloThread;
    long i;

    emptyHoles = 0;
    toCloseHoles = 0;
    holes = 0;

    sem_init(&holesSem, 0, 0);
    sem_init(&emptyHolesSem, 0, 0);
    sem_init(&toCloseHolesSem, 0, 0);
    sem_init(&shovelMutex, 0, 1);

    pthread_create(&joaoThread, NULL, joao, NULL);
    pthread_create(&pedroThread, NULL, pedro, NULL);
    pthread_create(&pauloThread, NULL, paulo, NULL);

    pthread_exit (NULL) ;
    return 0;
}