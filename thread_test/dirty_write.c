// dirty_write.c
#include <pthread.h>
#include <stdio.h>

int counter = 0;

void* worker(void* arg) 
{
    for (int i = 0; i < 100000; ++i) 
    {
        int tmp = counter;   // 读
        tmp = tmp + 1;       // 改
        counter = tmp;       // 写 —— 可能覆盖别人刚写入的值
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("期望值: 200000, 实际值: %d\n", counter);
    return 0;
}
