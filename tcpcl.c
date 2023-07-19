#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define port 8000
int main(){
    int sockfd,connfd;
    struct sockaddr_in haddr,claddr;
    sockfd = socket(AF_INET,SOCK_STREAM ,0 );
    if (sockfd <0){return -1;}
    haddr.sin_addr.s_addr = INADDR_ANY;
    haddr.sin_family = AF_INET;
    haddr.sin_port = htons(port);
    connfd = connect(sockfd, (struct sockaddr *)&haddr, sizeof(haddr));
    char *msg = "Hello There from client";
    write(sockfd,msg , strlen(msg));
    char buf[100];
    read(sockfd, &buf,100);
    printf("Recieved Message: %s",buf);
}
