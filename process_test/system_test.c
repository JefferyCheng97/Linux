#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    
    int sysR = system("ping -c 10 www.baidu.com");

    if (sysR != 0)
    {
        perror("system");
        exit(EXIT_FAILURE);
    }

    return 0;
}
