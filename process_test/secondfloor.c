#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("参数不够，不能上二楼！\n");

        return 1; 
    }

    printf("我是%s, 编号%d, 老学员是%d，我上二楼了！\n", argv[1], getpid(), getppid());

    return 0;
}
