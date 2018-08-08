#include<stdio.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#define PORT 8000

int main() {
    int sockfd,res;
    struct sockaddr_in addr;

    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("10.87.5.130");

    socklen_t addrlen = sizeof addr;

    if((res = connect(sockfd,(struct sockaddr*)&addr,addrlen) == -1)) {
            printf("Connection error\n");
            return 1;
    }

    char buffer[100];
    int len = recv(sockfd, buffer, sizeof buffer, 0);
    if(len == -1) {
        printf("Some error");
        return 2;
    }

    printf("The time is : %s\n",buffer);

    pid_t pid;
    len = recv(sockfd,&pid, sizeof pid, 0);
    if(len == -1) {
        printf("Some error");
        return 2;
    }
    if(len == 0) {
        return 3;
    }
    printf("Server process id : %ld\n",(long)pid);
    return 0;
}

