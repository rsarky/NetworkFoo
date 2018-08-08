#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>


int main() {
    int sock;
    struct sockaddr_in addr;
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("10.87.5.130");

    bind(sock,(struct sockaddr*)&addr,sizeof(addr));

    listen(sock,5);
    
    struct sockaddr_in client_addr;
    int client;
    char *message = "Hello World";
    socklen_t addr_size = sizeof client_addr; 
    int len = strlen(message);
    while(1) {
        printf("Server listening...\n");
        client = accept(sock,(struct sockaddr*)&client_addr,&addr_size);

        send(client,message,len,0);
    }
    return 0;
}
