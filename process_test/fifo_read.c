#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int fd;
    char *pipe_path = "/tmp/my_fifo";
    // if(mkfifo(pipe_path, 0664) != 0)
    // {
    //     perror("mkfifo error");
    //     exit(EXIT_FAILURE);
    // }

    // 对有名管道的特殊文件创建文件描述符
    fd = open(pipe_path, O_RDONLY);

    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    char buf[100];
    ssize_t read_num;

    // 读取管道信息，写入到控制台
    while ((read_num = read(fd, buf, 100)) > 0)
    {
        write(STDOUT_FILENO, buf, read_num);
    }

    if (read_num < 0)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("接收管道数据完成，进程终止\n");
    close(fd);
    return 0;
}
