#include<stdio.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main() {
    int sd;
    struct sockaddr_in serverAddr,clientAddr;
    
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("10.87.5.130");

    int len = sizeof clientAddr;

    int buffer1[3] = {1, 2 , 3};
    int buffer2[3] = {4, 5 , 6};
    int buffer3[3] = {7, 8 , 9};

    sendto(sd,
            buffer1,
            sizeof buffer1,
            0,
            (struct sockaddr*)&serverAddr,
            len);
    
    sendto(sd,
            buffer2,
            sizeof buffer2,
            0,
            (struct sockaddr*)&serverAddr,
            len);

    sendto(sd,
            buffer3,
            sizeof buffer3,
            0,
            (struct sockaddr*)&serverAddr,
            len);

} 

