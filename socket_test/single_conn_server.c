#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define handle_error(cmd, result) \
    if (result < 0)               \
    {                             \
        perror(cmd);              \
        return -1;                \
    }


/**
 * @brief 线程函数，用于接收客户端发送的数据
 * @param arg 传入的客户端socket文件描述符
 * @return void*
 */
void *read_from_client(void* arg)
{
    // 使用recv接收客户端发送的数据
    char* read_buff = NULL;
    int clientfd = *((int *)arg);
    
    read_buff = malloc(sizeof(char) * 1024);
    ssize_t count = 0;

    if (!read_buff)
    {
        perror("malloc");

        return NULL;
    }
    
    while (count = recv(clientfd, read_buff, 1024, 0))
    {
        if (count < 0)  
        {
            perror("recv");
        }
        
        fputs(read_buff, stdout);
    }

    printf("客户端断开连接，释放资源\n");
    free(read_buff);

    return NULL;
}


/**
 * @brief 线程函数，用于向客户端发送数据
 * @param arg 传入的客户端socket文件描述符
 * @return void*
 */
void *write_to_client(void* arg)
{
    // 接收控制台输入的数据
    char* write_buff = NULL;
    int clientfd = *((int *)arg);
    
    write_buff = malloc(sizeof(char) * 1024);
    ssize_t count = 0;

    if (!write_buff)
    {
        perror("malloc");

        return NULL;
    }

    while (fgets(write_buff, 1024, stdin))
    {
        // 发送数据
        count = send(clientfd, write_buff, 1024, 0);

        if (count < 0)
        {
            perror("send");
        }
    }

    printf("接收到控制台的关闭请求");
    shutdown(clientfd, SHUT_WR);
    free(write_buff);

    return NULL;
}

int main(int argc, char const *argv[])
{    
    int sockfd;
    int temp_result;
    int clientfd;

    // 创建服务端地址结构体
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); // 清空结构体，之后再赋值
    server_addr.sin_family = AF_INET;  // 填写协议族ipv4
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 填写ip地址
    server_addr.sin_port = htons(6666); // 填写端口号

    // 创建客户端地址结构体
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr)); // 清空结构体，之后再赋值

    // 服务端网络编程流程
    // 1. socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockfd);

    // 2. 绑定地址
    temp_result = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    handle_error("bind", temp_result);

    // 3. 监听
    listen(sockfd, 128);
    handle_error("listen", temp_result);

    // 4. 获取客户端连接
    socklen_t client_addr_len = sizeof(client_addr);
    clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
    handle_error("accept", clientfd);
    printf("客户端连接成功，IP: %s, 端口: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
    // 创建线程用于收发消息
    pthread_t pid_read;
    pthread_t pid_write;
    pthread_create(&pid_read, NULL, read_from_client, (void *)&clientfd);
    pthread_create(&pid_write, NULL, write_to_client, (void *)&clientfd);

    // 阻塞主线程
    pthread_join(pid_read, NULL);
    pthread_join(pid_write, NULL);

    printf("释放资源");
    close(clientfd);
    close(sockfd);

    return 0;
}

