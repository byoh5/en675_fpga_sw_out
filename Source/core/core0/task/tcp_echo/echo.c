#include "dev.h"

#include "enx_freertos.h"

#include <string.h>									// for memory
#include <stdlib.h>									// for atoi, qsort

#include "lwip/sockets.h"
#include "lwip/inet.h"

void EchoServer(){

	printf("EchoServer start\n");

int lSocket;
struct sockaddr_in sLocalAddr;

lSocket = lwip_socket(AF_INET, SOCK_STREAM, 0);
if (lSocket < 0) return;

memset((char *)&sLocalAddr, 0, sizeof(sLocalAddr));
sLocalAddr.sin_family = AF_INET;
sLocalAddr.sin_len = sizeof(sLocalAddr);
sLocalAddr.sin_addr.s_addr = htonl(INADDR_ANY);
sLocalAddr.sin_port =lwip_htons(5555);

if (lwip_bind(lSocket, (struct sockaddr *)&sLocalAddr, sizeof(sLocalAddr)) < 0) {
        lwip_close(lSocket);
        printf("EchoServer bind Close\n");
        return;
}

if ( lwip_listen(lSocket, 20) != 0 ){
        lwip_close(lSocket);
        printf("EchoServer listen Close\n");
        return;
}
printf("EchoServer listen\n");
while (1) {
        int clientfd;
        struct sockaddr_in client_addr;
        int addrlen=sizeof(client_addr);
        char buffer[1024];
        int nbytes;

        clientfd = lwip_accept(lSocket, (struct sockaddr*)&client_addr, (socklen_t)&addrlen);
        if (clientfd>0){
            do{
                nbytes=lwip_recv(clientfd, buffer, sizeof(buffer),0);
                if (nbytes>0) lwip_send(clientfd, buffer, nbytes, 0);
            }  while (nbytes>0);

             lwip_close(clientfd);
          }
    }
    lwip_close(lSocket);
}
