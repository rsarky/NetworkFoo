#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#define MAX 20

void print(int arr[]);
int main() {
    int sockfd;

    struct sockaddr_in addr;
    
    sockfd  = socket(PF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("10.87.5.130");

    int arr[MAX];
    printf("Enter the length of the array : \n");
    int len;
    scanf("%d",&len);
    printf("Enter elements...\n");
    arr[0] = len;
    for(int i=1;i<=len;i++) {
        scanf("%d",&arr[i]);
    }
    connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));

    write(sockfd, arr, sizeof arr);

    read(sockfd, arr, sizeof arr);
    print(arr);

}

void print(int arr[]) {
    int len = arr[0];
    for(int i=1;i<=len;i++) {
        printf("%d\n",arr[i]);
    }
}
