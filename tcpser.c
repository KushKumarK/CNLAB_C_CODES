#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define port 8000
int main(){
    int sockfd,bindfd,accfd,listfd;
    struct sockaddr_in haddr,claddr;
    sockfd = socket(AF_INET,SOCK_STREAM ,0 );
    if (sockfd <0){return -1;}
    haddr.sin_addr.s_addr = INADDR_ANY;
    haddr.sin_family = AF_INET;
    haddr.sin_port = htons(port);
    bindfd = bind(sockfd,(struct sockaddr*)&haddr ,sizeof(haddr) );
    if (bindfd<0){
        return -1;
    }
    listfd = listen(sockfd, 3);
    if (listfd<0){
        return -1;
    }
    socklen_t s = sizeof(claddr);
    accfd = accept(sockfd, (struct sockaddr *)&claddr, &s);
    if (accfd <0){
        return -1;
    }
    char *msg = "Hello There";
    write(accfd,msg , strlen(msg));
    char buf[100];
    read(accfd, &buf,100);
    printf("Recieved Message: %s",buf);
}
