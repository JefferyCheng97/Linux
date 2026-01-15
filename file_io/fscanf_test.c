#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE* ioFile = fopen("user.txt", "r");
    (ioFile == NULL) ? printf("打开文件失败！\n") : printf("打开文件成功！\n");

    char name[50];
    int age;
    char lover[50];
    int scanfR = fscanf(ioFile, "%s %d %s", name, &age, lover);

    while (fscanf(ioFile, "%s %d %s", name, &age, lover) != EOF)
    {
        printf("成功读取了 %d 个数据\n", scanfR);
        printf("%s 在 %d 岁时遇见了 %s\n", name, age, lover);
    } 
    
    (fclose(ioFile) == EOF) ? printf("关闭文件失败！\n") : printf("关闭文件成功！\n");
 
    return 0;
}
