#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int fd = open("io.txt", O_RDONLY);

    if (fd == -1) 
    {
        // printf("打开文件失败\n");
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[5];
    ssize_t bytes_read;
    
    while ((bytes_read = read(fd, buffer, sizeof(buffer)))> 0)
    {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) 
    {
        // printf("读取文件失败\n");
        perror("Error reading file");
        close(fd); // 关闭文件描述符
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}
