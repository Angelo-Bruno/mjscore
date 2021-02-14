#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define PND 2
#define CFOME 1
#define COMENDO 0
#define ESQ (fnum + 4) % N
#define DIRE (fnum + 1) % N

int estado[N];
int filo[N] = {0, 1, 2, 3, 4};

sem_t mutex;

sem_t S[N];

void test(int fnum)
{
    if (estado[fnum] == CFOME && estado[ESQ] != COMENDO && estado[DIRE] != COMENDO)
    {
        // estado para comer
        estado[fnum] = COMENDO;

        sleep(2);

        printf("Filosofo %d apanhou os garfos %d e %d\n",
               fnum + 1, ESQ + 1, fnum + 1);

        printf("Filosofo %d esta comendo\n", fnum + 1);

        
        sem_post(&S[fnum]);

    }
}

// apanhar os garfos(2)
void take_fork(int fnum)
{

    sem_wait(&mutex);

    // estado que esta com  fome
    estado[fnum] = CFOME;

    printf("Filosofo %d esta com fome\n", fnum + 1);

    // comer se os filosofos de ambos os lados nao estao a comer
    test(fnum);
    printf(" \n");
    sem_post(&mutex);// se nao conseguir comer esperar ate for sinalizado

    
    sem_wait(&S[fnum]);

    sleep(1);
}

// pousar o garfo
void put_fork(int fnum)
{

    sem_wait(&mutex);//trinco

    // estado de pensar
    estado[fnum] = PND;

    printf("Filosofo %d pousou os garfos %d e %d \n",
           fnum + 1, ESQ + 1, fnum + 1);
    printf("Filosofo %d esta a pensar\n", fnum + 1);

    test(ESQ);
    test(DIRE);

    sem_post(&mutex);
}

void *filosofo(void *num)
{

    while (1)
    {

        int *i = num;

        sleep(2);
       
        take_fork(*i);

        sleep(2);
       

        put_fork(*i);
    }
}

int main()
{

    int i;
    pthread_t thread_id[N];

    // inicializar os semaforos
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)

        sem_init(&S[i], 0, 0);
        
    for (i = 0; i < N; i++)
    {

        // criar os filosofos(processos)
        pthread_create(&thread_id[i], NULL,
                       filosofo, &filo[i]);

        printf("Filosofo %d esta a pensar\n", i + 1);
    }

    for (i = 0; i < N; i++)

        pthread_join(thread_id[i], NULL);
}





