#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>

int main() {
    int sockfd;

    struct sockaddr_in addr;
    
    sockfd  = socket(PF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("10.87.5.130");

    connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    char buf[100];
    int len = recv(sockfd,buf,sizeof(buf),0);
    buf[len] = '\0';
    printf("%s\n",buf);
}

