#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int fd = open("io.txt", O_RDONLY | O_CREAT, 0664);

    if (fd == -1)
    {
        printf("打开文件失败！\n");    
    }
    else
    {
        printf("打开文件成功！\n");
    }

    return 0;
}
