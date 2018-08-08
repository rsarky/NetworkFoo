#include<stdio.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>

#include<time.h>
#define PORT 8000

void getTime(char t[]);

int main() {
    int sockfd,sockfd_client;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_size = sizeof client_addr;

    if( (sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1 ) {
        printf("Error");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("10.87.5.130");

    socklen_t addrlen = sizeof server_addr;

    if(bind(sockfd, (struct sockaddr*)&server_addr, addrlen) == -1) {
        printf("Binding error");
        return 2;
    }

    if(listen(sockfd,5) == -1) {
        printf("Listening error");
        return 3;
    }

    while(1) {
        printf("Server Listening...\n");
        if((sockfd_client = accept(sockfd,(struct sockaddr*)&client_addr,&client_size)) == -1){
            printf("Error\n");
            return 4;
        }

        char time[100];
        getTime(time);
        if(send(sockfd_client,time,strlen(time),0) == -1) {
            printf("Sending error");
            return 5;
        }
        time[strlen(time)] = '\0';
        pid_t pid = getpid();
        if(send(sockfd_client,&pid,sizeof(pid),0) == -1) {
            printf("Sending error");
            return 5;
        }


    }

    return 0;

}

void getTime(char t[]) {
    time_t time_epoch;
    time(&time_epoch);
    strcpy(t,ctime(&time_epoch));
}



    
