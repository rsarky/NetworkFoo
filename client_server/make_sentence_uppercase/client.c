#include<stdio.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in addr;

    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("10.87.5.130");

    connect(sockfd, (struct sockaddr*)&addr, sizeof addr);

    while(1) {
        char input_buf[256];
        char caps[256];
        printf("Enter string to be sent to server:\n");
        scanf("%s",input_buf);

        send(sockfd, input_buf, sizeof input_buf, 0);
        if(strcmp(input_buf, "QUIT") == 0) {
            return 0;
        }

        recv(sockfd, caps, sizeof caps, 0);
        printf("The capitalized string is: %s\n",caps);
    }
}

