#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // 邀请之前
    char* name = "jeffery";
    printf("%s %d继续在一楼精进\n", name, getpid());

    // 邀请新学员
    pid_t pid = fork();

    if (pid == -1)
    {
        printf("邀请新学员失败！\n");
        return 1;
    }
    else if (pid == 0)
    {
        // 新学员在这里
        char* new_name = "jack";
        char *args[] = {"/home/jeffery/sgg/process_test/secondfloor", new_name, NULL};
        char *envs[] = {NULL};
        int exR = execve(args[0], args, envs);

        if (exR == -1)
        {
            printf("新学员上二楼失败！\n");
            return 1;
        }
    }
    else
    {
        // 老学员
        sleep(1);
        printf("老学员%d 邀请完 %d继续在一楼精进\n", getpid(), pid);
    }

    return 0;
}
