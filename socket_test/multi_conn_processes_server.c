#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>


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

// 处理僵尸进程
void zombie_dealer(int sig) 
{
    pid_t pid;
    int status;
    // 一个SIGCHLD可能对应多个子进程的退出
    // 使用while循环回收所有退出的子进程，避免僵尸进程的出现
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) 
    {
        if (WIFEXITED(status)) 
        {
            printf("子进程: %d 以 %d 状态正常退出，已被回收\n", pid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) 
        {
            printf("子进程: %d 被 %d 信号杀死，已被回收\n", pid, WTERMSIG(status));
        }
        else 
        {
            printf("子进程: %d 因其它原因退出，已被回收\n", pid);
        }
    }
}


int main(int argc, char const *argv[])
{
    int sockfd;
    int temp_result;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    // 注册信号处理函数，防止僵尸进程
    signal(SIGCHLD, zombie_dealer); 

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

        // 创建单独的子进程和连接的客户端交换
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            close(sockfd); // 关闭子进程的监听套接字
            printf("客户端连接成功，IP: %s, 端口: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            read_from_client_then_write((void*)&clientfd);
            close(clientfd); // 关闭子进程的已连接套接字
            exit(0); // 结束子进程
        }
        else
        {
            close(clientfd); // 关闭父进程的已连接套接字
        }
    }
    
    printf("释放资源\n");    
    close(sockfd);
    
    return 0;
}


