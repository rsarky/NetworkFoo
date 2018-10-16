#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
	int sd;
	//char buf[256];
	struct sockaddr_in sadd, cadd;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	sadd.sin_family = AF_INET;
	sadd.sin_addr.s_addr = inet_addr("127.0.0.1");//172.16.58.173
	sadd.sin_port = htons(9704);

	int result = bind(sd, (struct sockaddr*)&sadd, sizeof(sadd));
	int len = sizeof(cadd);
	int n;
	recvfrom(sd, &n, sizeof(n), 0, (struct sockaddr*)&cadd, &len);
	//printf("Size sent from the client: %d\n", n);

	int arr[n][n], ar[n];
	int i;
	for(i = 0; i < n; i++){
		recvfrom(sd, ar, sizeof(ar), 0, (struct sockaddr*)&cadd, &len);
		for(int j = 0; j < n; j++){
			arr[i][j] = ar[j];
		}
	}

	printf("Matrix sent from the client side:\n");
	for(i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
