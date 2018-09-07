#include<stdio.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void combine(int arr[][3], int buf1[], int buf2[], int buf3[]);
void print(int arr[][3]);
int main() {
    int sd;
    struct sockaddr_in serverAddr,clientAddr;
    
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("10.87.5.130");

    bind(sd, (struct sockaddr*) &serverAddr, sizeof serverAddr);

    int len = sizeof clientAddr;

    int buffer1[3];
    int buffer2[3];
    int buffer3[3];

    recvfrom(sd ,
            buffer1,
            sizeof buffer1,
            0,
            (struct sockaddr*)&clientAddr,
            &len);
    
    recvfrom(sd,
            buffer2,
            sizeof buffer1,
            0,
            (struct sockaddr*)&clientAddr,
            &len);

    recvfrom(sd,
            buffer3,
            sizeof buffer1,
            0,
            (struct sockaddr*)&clientAddr,
            &len);
     int arr[3][3];

     combine(arr,buffer1,buffer2,buffer3);
     print(arr);
} 

void combine(int arr[][3], int buffer1[], int buffer2[], int buffer3[]) {
    for(int i=0;i<3;i++) {
        arr[0][i] = buffer1[i];
    }
    for(int i=0;i<3;i++) {
        arr[1][i] = buffer2[i];
    }
    for(int i=0;i<3;i++) {
        arr[2][i] = buffer3[i];
    }
}

void print(int arr[][3]) {

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
