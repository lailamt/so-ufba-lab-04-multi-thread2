#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>


#define NUM_TYPE_X 1
#define NUM_TYPE_Y 1
#define NUM_TYPE_Z 1

#define B1_SIZE 5
#define B2_SIZE 5


pthread_mutex_t b_mutex;	
pthread_cond_t B1_sem, B2_sem;

int b1_items, b2_items;

void espera(int n)
{
  sleep (random() % n) ;	// pausa entre 0 e n segundos (inteiro)
  usleep (random() % 1000000) ;	// pausa entre 0 e 1 segundo (float)
}

void * entityXBody(void *id) {
    long tid = (long) id ;
    printf("OI, TUDO BEM? EU SOU A ENTIDADE X (%ld)\n", tid);

    while (1) {
        printf("OI (X:%ld), EU QUERO PRODUZIR PRA B1\n", tid);
        pthread_mutex_lock(&b_mutex);
        while (b1_items == B1_SIZE) {
            printf("b1_items == B1_SIZE\n");
            pthread_cond_wait (&B1_sem, &b_mutex);
        }
        b1_items++;
        printf("OI (X:%ld), EU PRODUZI PRA B1, ela tem %d itens\n", tid, b1_items);
        pthread_cond_signal (&B1_sem);
        pthread_mutex_unlock(&b_mutex);

        espera(2);
    }
}

void * entityYBody(void *id) {
    long tid = (long) id ;
    printf("OI, TUDO BEM? EU SOU A ENTIDADE Y (%ld)\n", tid);

    while (1) {
        pthread_mutex_lock(&b_mutex);
        printf("OI (Y:%ld), EU QUERO CONSUMIR DE B1\n", tid);
        while (b1_items <= 0) {
            printf("b1_items <= 0\n");
            pthread_cond_wait (&B1_sem, &b_mutex);
        }
        b1_items--;
        printf("OI (Y:%ld), EU CONSUMI DE B1, ela tem %d itens\n", tid, b1_items);
        pthread_cond_signal (&B1_sem);
        pthread_mutex_unlock(&b_mutex);

        printf("OI (Y:%ld), EU QUERO PRODUZIR PRA B2\n", tid);
        pthread_mutex_lock(&b_mutex);
        while (b2_items == B2_SIZE) {
            printf("b2_items == B2_SIZE\n");
            pthread_cond_wait (&B2_sem, &b_mutex);
        }
        b2_items++;
        printf("OI (Y:%ld), EU PRODUZI PRA B2, ela tem %d itens\n", tid, b2_items);
        pthread_cond_signal (&B2_sem);
        pthread_mutex_unlock(&b_mutex);


        espera(2);
    }
}

void * entityZBody(void *id) {
    long tid = (long) id ;
    printf("OI, TUDO BEM? EU SOU A ENTIDADE Z (%ld)\n", tid);

    while (1) {
        pthread_mutex_lock(&b_mutex);
        printf("OI (Z:%ld), EU QUERO CONSUMIR DE B2\n", tid);
        while (b2_items <= 0) {
            printf("b2_items <= 0\n");
            pthread_cond_wait (&B2_sem, &b_mutex);
        }
        b2_items--;
        printf("OI (Z:%ld), EU CONSUMI DE B2, ela tem %d itens\n", tid, b2_items);
        pthread_cond_signal (&B2_sem);
        pthread_mutex_unlock(&b_mutex);

        espera(2);
    }
}



int main(int argc, char const *argv[]) {
    pthread_t entity_type_x[NUM_TYPE_X];
    pthread_t entity_type_y[NUM_TYPE_Y];
    pthread_t entity_type_z[NUM_TYPE_Z];
    long i;

    b1_items = 0;
    b2_items = 0;

    pthread_cond_init(&B1_sem, NULL);
    pthread_cond_init(&B2_sem, NULL);
    pthread_mutex_init(&b_mutex, NULL);

    for (i=0; i<NUM_TYPE_X; i++) pthread_create(&entity_type_x[i], NULL, entityXBody, (void *) i);

    for (i=0; i<NUM_TYPE_Y; i++) pthread_create(&entity_type_y[i], NULL, entityYBody, (void *) i);

    for (i=0; i<NUM_TYPE_Z; i++) pthread_create(&entity_type_z[i], NULL, entityZBody, (void *) i);

    pthread_exit (NULL) ;
    return 0;
}
