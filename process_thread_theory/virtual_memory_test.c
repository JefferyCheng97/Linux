#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int val = 123;

    __pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        val = 321;
        printf("子进程中val的值为：%d，地址是：%p\n", val, &val);
    }
    else
    {
        sleep(1);
        printf("父进程中val的值为：%d，地址是：%p\n", val, &val);
    }
    
    return 0;
}
