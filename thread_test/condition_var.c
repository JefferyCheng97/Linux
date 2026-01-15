#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

// 初始化互斥锁和条件变量
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

// 向缓冲区生产数据
void* producer_function(void* arg) 
{
    int item = 1;

    while (1)
    {
        pthread_mutex_lock(&mutex); // 获取锁

        // 缓冲区满，暂停线程
        if (count == BUFFER_SIZE) 
        {
            
            pthread_cond_wait(&cond_var, &mutex);
        }
        
        buffer[count++] = item++;
        printf("白月光发送了一个幸运数字%d\n", buffer[count - 1]);

        pthread_cond_signal(&cond_var); // 唤醒消费者

        pthread_mutex_unlock(&mutex); // 释放锁
    }
}

// 从缓冲区消费数据
void* consumer_function(void* arg) 
{
    while (1)
    {
        pthread_mutex_lock(&mutex); // 获取锁

        if (count == 0) 
        {
            // 缓冲区空，暂停线程
            pthread_cond_wait(&cond_var, &mutex);
        }

        printf("我收到白月光的幸运数字为%d\n", buffer[--count]);
        pthread_cond_signal(&cond_var); // 唤醒生产者

        pthread_mutex_unlock(&mutex); // 释放锁
    }
}

int main(int argc, char const *argv[])
{
    // 创建两个线程 
    pthread_t producer; // 一个往buffer里写数据
    pthread_t consumer; // 一个从buffer里读数据

    pthread_create(&producer, NULL, producer_function, NULL);
    pthread_create(&consumer, NULL, consumer_function, NULL);

    // 主线程等待创建的子线程运行完成
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    return 0;
}
