#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    FILE* file = fopen("/home/jeffery/sgg/socket_test/testfile.txt", "w");

    // 修改刷写模式
    // setvbuf(file, NULL, _IONBF, 0); // 设置为无缓冲
    setvbuf(file, NULL, _IOLBF, 0); // 设置为行缓冲

    // 文件写入是全缓冲，等待缓冲区满或者手动刷写
    fprintf(file, "hello world\n");

    // 手动刷写
    // fflush(file);

    if (file == NULL)
    {
        perror("fopen");

        return -1;
    }
    
    char* args[] = {"/usr/bin/ping", "-c", "5", "www.baidu.com", NULL};
    char* env[] = {NULL};
    execve(args[0], args, env);

    // 如果跳转失败
    perror("execve");

    return 0;
}
