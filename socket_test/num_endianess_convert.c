#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char const *argv[])
{
    // 声明两个端口号
    unsigned short local_num = 0x1f;
    unsigned short network_num = 0;

    // 主机字节序转网络字节序
    network_num = htons(0x1f);
    printf("将主机字节序 0x%x 转换为网络字节序 0x%x\n", local_num, network_num);

    local_num = ntohs(network_num);
    printf("将网络字节序 0x%x 转换为主机字节序 0x%x\n", network_num, local_num);
    
    return 0;
}
