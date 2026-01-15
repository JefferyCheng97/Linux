#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 20000

// 初始化锁
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

// 创建多个线程
void* add_thread(void* arg) 
{
    int* p = (int*)arg;

    pthread_mutex_lock(&counter_mutex); // 上锁
    (*p)++;
    pthread_mutex_unlock(&counter_mutex); // 解锁

    return (void*) 0;
}

int main(int argc, char const *argv[])
{
    pthread_t pid[THREAD_COUNT];
    int num = 0;

    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(pid + i, NULL, add_thread, &num);
    }

    // 等待所有线程结束
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(pid[i], NULL);
    }
    
    // 输出结果
    printf("累加结果为：%d\n", num);

    return 0;
}
