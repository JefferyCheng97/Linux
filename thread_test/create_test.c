#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_LEN 1024

char *buf;

void* input_thread(void* arg)
{
    int i = 0;

    while (1)
    {
        char c = fgetc(stdin);

        if (c && c!= '\n')
        {
            buf[i++] = c;
        }

        if (i >= BUF_LEN)
        {
            i = 0;
        }
    }

    return NULL;
}

void* output_thread(void* arg)
{
    int i = 0;

    while (1)
    {
        if (buf[i])
        {
            fputc(buf[i], stdout);
            fputc('\n', stdout);
            buf[i++] = 0;

            if (i >= BUF_LEN)
            {
                i = 0;
            }
        }
        else
        {
            sleep(1);
        }
    }

    return NULL;
}



// 创建两个线程
// (1) 读取控制台信息，写入到buf中
// (2) 从buf中读取信息，打印到控制台
int main(int argc, char const *argv[])
{
    buf = malloc(BUF_LEN);

    pthread_t pid_input;
    pthread_t pid_output;

    // 创建读线程
    pthread_create(&pid_input, NULL, input_thread, NULL);

    // 创建写线程
    pthread_create(&pid_output, NULL, output_thread, NULL);

    pthread_join(pid_input, NULL);
    pthread_join(pid_output, NULL);

    free(buf);

    return 0;
}
