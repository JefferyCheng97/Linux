#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char* ch = malloc(100);

    fgets(ch, 100, stdin);
    printf("你好：%s\n", ch);

    fputs(ch, stdout);
    printf("\n");

    fputs(ch, stderr);
    printf("\n");

    return 0;
}
