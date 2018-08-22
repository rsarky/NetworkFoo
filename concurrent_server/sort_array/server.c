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

void asort(int arr[]);
void print(int arr[]);
int main() {
    int sock;
    struct sockaddr_in addr;
    pid_t pid;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("10.87.5.130");

    bind(sock,(struct sockaddr*)&addr,sizeof(addr));
    listen(sock,5);
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof client_addr;        
    int client;
    while(1) {
        printf("Server listening...\n");
        client = accept(sock,(struct sockaddr*)&client_addr,&addr_size);
        int arr[MAX];
        if(fork() == 0) {
            //client
            read(client,arr,sizeof arr);
            print(arr);
            asort(arr);
            write(client,arr,sizeof arr);
            close(client);
        } else {
            close(client);
        }
    }
    return 0;
}

void asort(int arr[]) {
    int len = arr[0];

    for(int i=1;i<len;i++) {
        for(int j=1; j<= len-i;j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void print(int arr[]) {
    int len  = arr[0];
    for(int i=1; i<=len;i++) {
        printf("%d\n",arr[i]);
    }
}
