#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

int buffer[10];
int BUFFER_SIZE = 10;

int in_index = 0, out_index = 0, produced = 0, consumed = 0; 

atomic_int producer_er_kaj_chole = 0, consumer_er_kaj_chole = 1;

// buffer management

int buffer_count ()
{
    int count = 0;

    for (int i=0; i<BUFFER_SIZE; ++i)
        if (buffer[i] != 0)
            ++count;

    return count;
}

//Semaphore Implementation

void ustad_seat_khali_nai(atomic_int *semaphore)
{   
    while(*semaphore <= 0); // vai ektu thamen 5* khan ar hariye jan

    (*semaphore)--;
}

void ustad_seat_khali_hoise(atomic_int *semaphore)
{
    (*semaphore)++;
}

void *producer()
{
    while (produced < 50) {
        
        ustad_seat_khali_nai(&consumer_er_kaj_chole);

        if (buffer_count() == BUFFER_SIZE) {
            ustad_seat_khali_hoise(&producer_er_kaj_chole);
            continue;    
        }

        buffer[in_index] = ++produced;

        printf("Producer produced = %d\n", buffer[in_index]);
        printf("current status of the queue : ");

        for(int i=0; i<BUFFER_SIZE; ++i){
            printf("%d ", buffer[i]);
        } printf("\n");
        
        in_index = (in_index + 1) % BUFFER_SIZE;
        ustad_seat_khali_hoise(&producer_er_kaj_chole);
    }
}

void *consumer()
{
    int out;

    while (consumed < 50) {

        ustad_seat_khali_nai(&producer_er_kaj_chole);

        if (buffer_count() == 0) {
            ustad_seat_khali_hoise(&consumer_er_kaj_chole);
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
        ustad_seat_khali_hoise(&consumer_er_kaj_chole);
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
