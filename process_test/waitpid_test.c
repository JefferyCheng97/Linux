#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int subprocess_status;
    printf("父进程\n");
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        // 子进程
        char* args[] = {"/usr/bin/ping", "-c", "10", "www.baidu.com", NULL};
        char* envs[] = {NULL};
        printf("子进程ping网站10次\n");
        int exR = execve(args[0], args, envs);

        if (exR < 0)
        {
            perror("execve");
            return 1;
        }
    }
    else
    {
        // 父进程
        printf("父进程%d等待子进程%d结束\n", getpid(), pid);
        waitpid(pid, &subprocess_status, 0);
    }

    printf("父进程等待子进程结束");

    return 0;
}
