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
    if(mkfifo(pipe_path, 0664) != 0)
    {
        perror("mkfifo error");
        if (errno != EEXIST) // 如果不是文件已存在错误，则退出
        {
            exit(EXIT_FAILURE);
        }
    }

    // 对有名管道的特殊文件创建文件描述符
    fd = open(pipe_path, O_WRONLY);

    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[100];
    ssize_t read_num;

    while ((read_num = read(STDIN_FILENO, buf, 100)) > 0)
    {
        write(fd, buf, read_num);
    }

    if (read_num < 0)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("发送数据到管道完成，进程终止\n");
    close(fd);

    // 删除有名管道文件
    if (unlink(pipe_path) == -1)
    {
        perror("unlink");
    }

    return 0;
}
