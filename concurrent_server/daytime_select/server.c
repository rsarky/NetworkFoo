#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<time.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/ioctl.h>
#include<unistd.h>

void getTime(char buff[]);
int main() {
    int server_sockfd,client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    fd_set readfds,testfds;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("10.87.5.130");
    server_addr.sin_port = htons(8080);

    server_len = sizeof server_addr;

    bind(server_sockfd, (struct sockaddr*)&server_addr, server_len);
    listen(server_sockfd,5);

    FD_ZERO(&readfds);
    FD_SET(server_sockfd,&readfds);

    while(1) {
        testfds = readfds;
        printf("Server waiting...\n");
        int res = select(FD_SETSIZE, &testfds, (fd_set*)0, (fd_set*)0, (struct timeval*) 0);

        if(res < 1) {
            exit(1);
        }

        for(int fd=0; fd < FD_SETSIZE; fd++) {
            if(FD_ISSET(fd, &testfds)) {
                    if(fd == server_sockfd) {
                        client_len = sizeof client_addr;
                        client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len);
                        char time[100];
                        getTime(time);
                        time[strlen(time)] = '\0';
                        write(client_sockfd,time,sizeof time);
                        close(client_sockfd);
                    }
            }
        }
    }
    return 0;
}

void getTime(char t[]) {
    time_t time_epoch;
    time(&time_epoch);
    strcpy(t,ctime(&time_epoch));
}



