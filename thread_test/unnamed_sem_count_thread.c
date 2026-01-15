#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

sem_t *full;
sem_t *empty;

int shard_num;

int rand_num()
{
    srand(time(NULL));

    return rand();
}

void* producer_function(void* arg) 
{
    for(size_t i = 0; i < 5; i++)
    {
        sem_wait(empty); // 获取信号量
        printf("第%ld轮数据传输\n", i + 1);
        sleep(1);
        shard_num = rand_num();
        sem_post(full); // 释放信号量
    }
}

void* consumer_function(void* arg)
{
    
    for(size_t i = 0; i < 5; i++)
    {
        sem_wait(full); // 获取信号量
        printf("第%ld轮消费者开始读取数据\n", i + 1);
        sleep(1);
        printf("读取到的数据为%d\n", shard_num);
        sem_post(empty); // 释放信号量
    }
}


int main(int argc, char const *argv[])
{
    full = malloc(sizeof(sem_t));
    empty = malloc(sizeof(sem_t));

    // 初始化信号量
    sem_init(full, 0, 0);
    sem_init(empty, 0, 1);

    // 创建生产者和消费者线程
    pthread_t producer, consumer;
    pthread_create(&producer, NULL, (void *)producer_function, NULL);
    pthread_create(&consumer, NULL, (void *)consumer_function, NULL);

    // 等待线程结束
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    // 销毁信号量
    sem_destroy(empty);
    sem_destroy(full);

    return 0;
}
