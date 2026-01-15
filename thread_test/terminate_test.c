#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

// 接收线程结果的结构体
typedef struct Result
{
    char* p;
    int len;
} Result;

void* red_thread(void* argv)
{
    Result *result = malloc(sizeof(Result));
    char code = *((char*)argv);
    // 存放回信
    char* ans = malloc(101);

    while (1)
    {
        fgets(ans,100,stdin);
        if (ans[0]==code)
        {
            //接收到了对应的信息
            free(ans);
            printf("红玫瑰离开了!\n");
            char *redAns = strdup("红玫瑰独自去了纽约.\n");
            result->p = redAns;
            result->len = strlen(redAns);
            // 结束线程 输出返回值
            pthread_exit((void*)result);
        }else{
            printf("红玫瑰还在等你!\n");
        }
    }
    
}

void* white_thread(void* argv)
{
    Result* result = malloc(sizeof(Result));
    char code = *((char*)argv);
    // 存放回信
    char *ans = malloc(101);
    
    while (1)
    {
        fgets(ans,100,stdin);
        if (ans[0]==code)
        {
            //接收到了对应的信息
            free(ans);
            printf("白玫瑰离开了!\n");
            char *redAns = strdup("白玫瑰独自去了伦敦.\n");
            result->p = redAns;
            result->len = strlen(redAns);
            
            // 结束线程 输出返回值
            pthread_exit((void*)result);
        }else{
            printf("白玫瑰还在等你!\n");
        }
    }
}

int main(int argc, char const *argv[])
{
    pthread_t pid_red;
    pthread_t pid_white;
    char red_rose = 'r';
    char white_rose = 'w';
    Result* red_result = NULL;
    Result* white_result = NULL;

    pthread_create(&pid_red, NULL, red_thread, (void*)&red_rose);
    pthread_create(&pid_white, NULL, white_thread, (void*)&white_rose);

    pthread_join(pid_red, (void**)&red_result);
    printf("红玫瑰的结果是：%s, 长度是：%d\n", red_result->p, red_result->len);
    free(red_result->p);
    free(red_result);

    pthread_join(pid_white, (void**)&white_result);
    printf("白玫瑰的结果是：%s, 长度是：%d\n", white_result->p, white_result->len);
    free(white_result->p);
    free(white_result);

    return 0;
}

