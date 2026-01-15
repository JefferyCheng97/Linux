#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE* ioFile = fopen("io.txt", "r");

    if (ioFile == NULL) 
    {
        printf("打开文件失败！\n");
    }
    else 
    {
        printf("打开文件成功！\n");
    }

    char buffer[100];
    
    while (fgets(buffer, sizeof(buffer), ioFile))
    {
        printf("%s", buffer);
    }

    int closeR = fclose(ioFile);

    if (closeR == EOF) 
    {
        printf("关闭文件失败！\n");
    }
    else if (closeR == 0)
    {
        printf("关闭文件成功！\n");
    }

    return 0;
}
