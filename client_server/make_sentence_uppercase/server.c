//Add error checking to both server and client.
//Prettify Output
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netinet/ip.h>

#define PORT 8080
#define BUFFER_SIZE 256

void capitalize(char input[], char output[]);

int main() {
    int serv_sockfd,client_sockfd;
    struct sockaddr_in serv_addr,client_addr;

    serv_sockfd = socket(PF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("10.87.5.130");

    bind(serv_sockfd, (struct sockaddr*)&serv_addr, sizeof serv_addr);

    listen(serv_sockfd, 5);

    printf("Server listening.\n");
    while(1) {
        printf("Waiting for client to connect...\n");
        socklen_t len = sizeof client_addr;
        client_sockfd  = accept(serv_sockfd, (struct sockaddr*)&client_addr, &len);

        while(1) {
            
            char buffer[BUFFER_SIZE];
            int bytes_read = recv(client_sockfd, buffer, sizeof buffer, 0);
            buffer[bytes_read] = '\0';

            printf("Client Message : %s\n", buffer);
            int client_port;
            char client_ip[20];
            client_port = ntohs(client_addr.sin_port);
            strcpy(client_ip,inet_ntoa(client_addr.sin_addr));
            printf("Client IP : %s\n", client_ip);
            printf("Client Port: %d\n", client_port);
            if(strcmp(buffer,"QUIT") == 0) {
                return 0;
            }

            char caps[BUFFER_SIZE];
            capitalize(buffer, caps);
            
            send(client_sockfd, caps, strlen(caps), 0);
        }
    }
}

void capitalize(char input[], char output[]) {
    int i;
    for(i=0;input[i]!='\0';i++) {
        output[i] = input[i] - 32;
    }
    output[i] = '\0';
}
