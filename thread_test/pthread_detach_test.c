#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* task(void* arg) 
{
    printf("Thread is running...\n");
    sleep(2);
    printf("Thread is finishing...\n");

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, task, NULL);
    pthread_detach(tid);
    printf("Main thread is doing other work...\n");
    sleep(3);
    printf("Main thread is exiting...\n");
    
    return 0;
}
