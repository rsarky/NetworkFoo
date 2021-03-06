#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc,char *argv[]) {
    int status;
    struct addrinfo hints;
    struct addrinfo *res;

    if(argc < 2) {
        printf("Usage: test domain");
        return 1;
    }

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if((status = getaddrinfo(argv[1],NULL, &hints, &res) != 0)) {
            printf("Error");
            return 2;
    }

    printf("IP addresses for %s are : \n",argv[1]);

    struct addrinfo *p;
    char ipstr[INET6_ADDRSTRLEN];
    for(p=res;p!=NULL;p=p->ai_next) {
        void* addr;
        char* ipver;
        if(p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in*) p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPV4";
        }
        else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6*) p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPV6";
        }
        
        inet_ntop(p->ai_family,addr,ipstr,sizeof ipstr);
        printf("%s: %s\n",ipver,ipstr);
    }
    freeaddrinfo(res);
    return 0;
}


