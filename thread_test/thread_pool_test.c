#include <glib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void task_func(gpointer data, gpointer user_data)
{
    int task_num = *(int*)data;
    free(data);
    printf("任务%d开始执行\n", task_num);
    sleep(task_num);
    printf("任务%d执行完毕\n", task_num);
    
}

int main(int argc, char const *argv[])
{
    // 创建线程池
    GThreadPool* pool = g_thread_pool_new((GFunc)task_func, NULL, 5, TRUE, NULL);
    
    // 向线程池添加任务
    for(size_t i = 0; i < 10; i++)
    {
        int* tmp = malloc(sizeof(int));
        *tmp = i + 1;
        g_thread_pool_push(pool, tmp, NULL);
    }

    // 释放线程池
    g_thread_pool_free(pool, FALSE, TRUE);
    printf("所有的任务都已经完成\n");

    return 0;
}
