#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 跳转之前
    char* name = "jeffery";
    printf("我是%s, 编号%d, 我在一楼！\n", name, getpid());

    // 执行跳转
    char *args[] = {"/home/jeffery/sgg/process_test/secondfloor", name, NULL};
    char *envs[] = {NULL};
    int re = execve(args[0], args, envs);

    if (re == -1)
    {
        printf("你没有机会上二楼！\n");
        return 1;
    }

    return 0;
}
