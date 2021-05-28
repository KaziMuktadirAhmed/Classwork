#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 20
void *read( void *name );
void *write( void *name );

sem_t rwMutex;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int  readCount = 0;
int accessedVar=0;

int main()
{
    int rc1, rc2;
    pthread_t writers[NUM_THREADS];
    pthread_t readers[NUM_THREADS];
    char *nameReader = "Reader 1";
    char *nameWriter = "Writer 1";
    pthread_t thread1, thread2;
    sem_init(&rwMutex,0,1);
    int i;	
    for (i=0;i<NUM_THREADS;i++){
	   if(rc2=pthread_create( &readers[i], NULL, &read, (int*) &i))
       {
       	  printf("Thread creation failed: %d\n", rc2);
       }
	   if(rc1=pthread_create( &writers[i], NULL, &write, (int*) &i))
	   {
		  printf("Thread creation failed: %d\n", rc1);
	   }
	}

    for (i=0;i<NUM_THREADS;i++){
	   pthread_join(writers[i], NULL);
	}
	for (i=0;i<NUM_THREADS;i++){
	   pthread_join(readers[i], NULL);
	}

    return 0;
}

void *write( void *name )
{
	sem_wait(&rwMutex);
    accessedVar++;
    printf("Writer %d writing %d\n", *((int *) name), accessedVar);
    sem_post(&rwMutex);
}

void *read( void *name )
{
	pthread_mutex_lock(&mutex);
	readCount++;

	if (readCount == 1){
		sem_wait(&rwMutex);
	}
	pthread_mutex_unlock(&mutex);

	printf("Reader %d reading %d\n", *((int *) name), accessedVar);

	pthread_mutex_lock(&mutex);
	readCount--;
	if (readCount == 0){
		 sem_post(&rwMutex);
	}
	pthread_mutex_unlock(&mutex);
}
