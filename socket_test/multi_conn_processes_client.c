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

void *read_from_server(void* arg)
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
    
    // 接收数据
    while (count = recv(clientfd, read_buff, 1024, 0))
    {
        if (count < 0)  
        {
            perror("recv");
        }
        
        fputs(read_buff, stdout);
    }

    printf("服务端断开连接，释放资源\n");
    free(read_buff);

    return NULL;
}

void *write_to_server(void* arg)
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

    pthread_t pid_read;
    pthread_t pid_write;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    // 清空
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // 填写服务端地址
    server_addr.sin_family = AF_INET;

    // 填写ip地址
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // 填写端口号
    server_addr.sin_port = htons(6666);


    // 客户端网络编程流程
    // 1. socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockfd);

    // 2. 绑定地址
    // 客户端可以不绑定，系统会自动分配一个空闲的端口号
    

    // 3. 主动连接服务端
    temp_result = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    handle_error("connect", temp_result);

    printf("连接服务端成功，等待服务端响应...\n");
    
    // 创建线程用于收发消息
    pthread_create(&pid_read, NULL, read_from_server, (void *)&sockfd);
    pthread_create(&pid_write, NULL, write_to_server, (void *)&sockfd);

    // 阻塞主线程
    pthread_join(pid_read, NULL);
    pthread_join(pid_write, NULL);

    printf("释放资源");
    close(sockfd);

    return 0;
}

