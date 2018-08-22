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

int evaluate(int arr[]);

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
        int arr[3];
        if(fork() == 0) {
            //client
            read(client,arr,sizeof arr);
            int ans = evaluate(arr);
            write(client,&ans,sizeof(int));
            close(client);
        } else {
            close(client);
        }
    }
    return 0;
}

int evaluate(int arr[]) {
    switch(arr[2]){
        case 0: return arr[0] + arr[1];
        case 1: return arr[0] - arr[1];
        case 2: return arr[0] * arr[1];
        case 3: return arr[0] / arr[1];
    }
}

