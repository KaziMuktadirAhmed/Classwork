#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdatomic.h>

int buffer[10];
int BUFFER_SIZE = 10;

int in_index = 0, out_index = 0, produced = 0, consumed = 0; 

// sychonization utility

atomic_int tala_lagaya_dise = 0;

atomic_int test_and_set (atomic_int *target)
{
    atomic_int return_value = *target;
    *target = 1;
    return return_value;
}

// buffer management

int buffer_count ()
{
    int count = 0;

    for (int i=0; i<BUFFER_SIZE; ++i)
        if (buffer[i] != 0)
            ++count;

    return count;
}

void *producer()
{
    while (produced < 50) {
        
        while(test_and_set(&tala_lagaya_dise));

        if (buffer_count() == BUFFER_SIZE) {
            tala_lagaya_dise = 0;
            continue;    
        }

        buffer[in_index] = ++produced;

        printf("Producer produced = %d\n", buffer[in_index]);
        printf("current status of the queue : ");

        for(int i=0; i<BUFFER_SIZE; ++i){
            printf("%d ", buffer[i]);
        } printf("\n");
        
        in_index = (in_index + 1) % BUFFER_SIZE;

        tala_lagaya_dise = 0;
    }
}

void *consumer()
{
    int out;

    while (consumed < 50) {

        while(test_and_set(&tala_lagaya_dise));

        if (buffer_count() == 0) {
            tala_lagaya_dise = 0;
            continue;    
        }

        int item = buffer[out_index];
        consumed = buffer[out_index];
        buffer[out_index] = 0;

        printf("Consumer consumed = %d\n",item);
        printf("current status of the queue : ");

        if(buffer_count() == 0)
            printf("BLANK\n");
        else
        {
            for(int i=0; i<BUFFER_SIZE; ++i){
                printf("%d ", buffer[i]);
            } printf("\n");    
        }
        
        out_index = (out_index + 1) % BUFFER_SIZE;

        tala_lagaya_dise = 0;
    }
}


int main(void)
{
    pthread_t thread1,thread2;

    pthread_create(&thread1, NULL, (void *)producer, NULL);
    pthread_create(&thread2, NULL, (void *)consumer, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return 0;
}