#include <stdio.h>

int main(int argc, char const *argv[])
{
    char* filename = "io.txt";
    FILE* ioFile = fopen(filename, "a+");

    if (ioFile == NULL) 
    {
        printf("打开文件失败！\n");
    }
    else 
    {
        printf("打开文件成功！\n");
    }

    char* name = "jeffery";
    int printfR = fprintf(ioFile, "Hello, %s!\n", name);

    if (printfR == EOF) 
    {
        printf("写入文件失败！\n");
    }
    else 
    {
        printf("成功写入 %d 个字符到文件。\n", printfR);
    }


    int result = fclose(ioFile);

    if (result == EOF) 
    {
        printf("关闭文件失败！\n");
    }
    else if (result == 0)
    {
        printf("关闭文件成功！\n");
    }

    return 0;
}
 