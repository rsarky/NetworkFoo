#include<stdio.h>
#include<unistd.h>
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

    int arr[3];
    printf("Enter op1: \n");
    scanf("%d",&arr[0]);
    printf("Enter op2: \n");
    scanf("%d",&arr[1]);
    printf("Enter operation: \n");
    scanf("%d",&arr[2]);
    connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));

    write(sockfd, arr, sizeof arr);
    int ans;
    read(sockfd, &ans, sizeof ans);
    printf("The answer is : %d\n",ans);


}
