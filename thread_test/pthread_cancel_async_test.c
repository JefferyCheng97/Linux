#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* task(void* arg) 
{
    printf("线程启动...\n");
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    printf("working...\n");
    int i = 0;

    while (1)
    {
        // 模拟线程工作
        printf("线程工作中... %d\n", i++);        
    }

    printf("线程取消后...\n");

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, task, NULL);
    
    if (pthread_cancel(tid))
    {
        perror("pthread_cancel error");
    }

    void* res;
    pthread_join(tid, &res);
    
    if (res == PTHREAD_CANCELED)
    {
        printf("线程被取消了...\n");
    }
    else
    {
        printf("线程没有被取消，%ld...\n", (long)res);
    }
        
    return 0;
}
