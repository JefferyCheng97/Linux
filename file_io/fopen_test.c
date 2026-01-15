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

    return 0;
}
 