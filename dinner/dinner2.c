#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[N];

void test(int phnum)
{
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        // estado para comer
        state[phnum] = EATING;

        sleep(2);

        printf("Filosofo %d apanhou os garfos %d e %d\n",
               phnum + 1, LEFT + 1, phnum + 1);

        printf("Filosofo %d esta comendo\n", phnum + 1);

        // sem_post(&S[phnum]) has no effect
        // during takefork
        // used to wake up hungry philosophers
        // during putfork
        sem_post(&S[phnum]);
    }
}

// apanhar os garfos(2)
void take_fork(int phnum)
{

    sem_wait(&mutex);

    // estado que esta com  fome
    state[phnum] = HUNGRY;

    printf("Filosofo %d esta com fome\n", phnum + 1);

    // comer se os filosofos de ambos os lados nao estao a comer
    test(phnum);

    sem_post(&mutex);

    // se nao conseguir comer esperar ate for sinalizado
    sem_wait(&S[phnum]);

    sleep(1);
}

// pousar o garfo
void put_fork(int phnum)
{

    sem_wait(&mutex);

    // estado de pensar
    state[phnum] = THINKING;

    printf("Filosofo %d pousou os garfos %d e %d \n",
           phnum + 1, LEFT + 1, phnum + 1);
    printf("Filosofo %d esta a pensar\n", phnum + 1);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void *philospher(void *num)
{

    while (1)
    {

        int *i = num;

        sleep(1);

        take_fork(*i);

        sleep(0);

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
                       philospher, &phil[i]);

        printf("Filosofo %d esta a pensar\n", i + 1);
    }

    for (i = 0; i < N; i++)

        pthread_join(thread_id[i], NULL);
}
