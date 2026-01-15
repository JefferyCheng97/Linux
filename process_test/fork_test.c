#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    // 调用fork之前
    printf("父进程 %d\n", getpid());

    pid_t pid = fork(); // 创建子进程

    // printf("子进程 %d\n", pid);
    if (pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
    {
        // 子进程
        printf("子进程 %d, 父进程 %d\n", getpid(), getppid());
    }
    else
    {
        // 父进程
        printf("父进程 %d, 子进程 %d\n", getpid(), pid);
    }

    return 0;
}
