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

void *read_from_client_then_write(void* arg)
{
    // 读取客户端发送的消息，然后打印到控制台，回复收到
    int client_fd = *(int*)arg;
    char* read_buf = malloc(sizeof(char) * 1024);
    char* write_buf = malloc(sizeof(char) * 1024);
    ssize_t count = 0;
    ssize_t send_count = 0;

    if (!read_buf)
    {
        printf("初始化读缓冲失败\n");
        close(client_fd);
        perror("read_buf");

        return NULL;
    }

    if (!write_buf)
    {
        printf("初始化写缓冲失败\n");
        close(client_fd);
        free(read_buf);
        perror("write_buf");

        return NULL;
    }
    
    while (count = recv(client_fd, read_buf, 1024, 0))
    {
        if (count < 0)
        {
            perror("recv");
        }

        // 接收到数据
        printf("收到客户端消息: %s\n", read_buf);

        // 回复收到
        strcpy(write_buf, "收到");
        send(client_fd, write_buf, strlen(write_buf), 0);
        
        if (send_count < 0)
        {
            perror("send");
        }
    }

    // 客户端断开连接
    close(client_fd);
    free(read_buf);
    free(write_buf);
    printf("客户端断开连接\n");
    
    return NULL;
}

int main(int argc, char const *argv[])
{
    int sockfd;
    int temp_result;

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

    // 网络编程流程
    // 1. socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockfd);

    // 2. 绑定地址
    temp_result = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    handle_error("bind", temp_result);

    // 3. 监听
    temp_result = listen(sockfd, 128);
    handle_error("listen", temp_result);

    // 4. 获取客户端连接
    // 需要能够接收多个连接
    socklen_t client_addr_len = sizeof(client_addr);

    while (1)
    {
        int clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
        pthread_t pid_read_write;
        handle_error("accept", clientfd);
        printf("客户端连接成功，IP: %s, 端口: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // 和每一个客户端使用一个线程交互
        // 把客户端发送的消息发送到控制台
        if (pthread_create(&pid_read_write, NULL, read_from_client_then_write, (void *)&clientfd))
        {
            perror("pthread_create");
        }

        // 需要等待线程结束，但不能挂起等待
        pthread_detach(pid_read_write);
    }
    
    printf("释放资源\n");
    close(sockfd);
    
    return 0;
}


