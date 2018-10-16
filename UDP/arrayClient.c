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
	struct sockaddr_in address;

	sd = socket(AF_INET, SOCK_DGRAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");//172.16.58.173
	address.sin_port = htons(9704);

	printf("Enter length of each 1D array:\n");
	int n = 3;
	scanf("%d", &n);

	int len = sizeof(address);
	sendto(sd ,&n, sizeof(int), 0, (struct sockaddr*)&address, len);

	int arr[n][n];
	printf("Enter the array:\n");
	for(int i = 0; i < n; i++){
		printf("Enter row %d:\n", i + 1);
		for(int j = 0; j < n; j++){
			scanf("%d", &arr[i][j]);
		}
		len = sizeof(address);
		sendto(sd, arr[i], sizeof(arr[i]), 0, (struct sockaddr*)&address, len);
	}
	return 0;
}
