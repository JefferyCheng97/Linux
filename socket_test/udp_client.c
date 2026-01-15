#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define handle_error(cmd, result) \
    if (result < 0)               \
    {                             \
        perror(cmd);              \
        return -1;                \
    }

int main(int argc, char const *argv[])
{
    // 使用upd协议完成客户端和服务端的通信
    // 人为地设置EOF作为关闭的信号
    int sockfd;
    int temp_result;

    char* buf = malloc(sizeof(char) * 1024);

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    // 清空
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // 填写服务端地址
    server_addr.sin_family = AF_INET;
    // 填写ip地址
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // 填写端口号
    server_addr.sin_port = htons(6666);

    // udp网络编程流程
    // 1. socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    handle_error("socket", sockfd);

    // 2. 客户端不需要绑定地址
    socklen_t server_len = sizeof(server_addr);
    socklen_t client_len = sizeof(client_addr);

    // 3. 接收数据
    do
    {
        printf("请输入要发送的消息, EOF表示结束:\n");
        
        // 从控制台读取数据
        int buf_len = read(STDIN_FILENO, buf, 1023);
        temp_result = sendto(sockfd, buf, buf_len, 0, (struct sockaddr*)&server_addr, server_len);
        handle_error("sendto", temp_result);

        // 清空缓冲区
        memset(buf, 0, 1024);
        temp_result = recvfrom(sockfd, buf, 1024, 0, NULL, NULL);
        handle_error("recvfrom", temp_result);

        if (strncmp(buf, "EOF", 3) != 0)
        {
            printf("收到服务端%s:%d回复: %s", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port), buf);
        }
    } 
    while (strncmp(buf, "EOF", 3));

    free(buf);

    return 0;
}

