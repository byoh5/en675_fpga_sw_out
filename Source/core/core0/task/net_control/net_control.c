#include "dev.h"

#include "enx_freertos.h"

#include <string.h>									// for memory
#include <stdlib.h>									// for atoi, qsort

#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "net_control.h"



unsigned int example1(char* cmdline, int fd){
	printf("example1\n");

	UINT argc;

	lwip_send(fd, cmdline, strlen(cmdline), 0);

	return 0;
}

TCLI_CMD cli_cmds[] =
{
	{ "ex1",		example1,	"example1" },

	{ 0, 0, 0 }
};

unsigned int cli_stdin_request_(char* cmdline, int fd)
{
	printf("cli_stdin_request: \"%s\"\n", cmdline);

	// parse a command
	char cmd_buf[CLI_CMD_LEN];
	static char cmdline_old[CLI_CMD_LEN];


	if (cmdline[0] == '_')	cmdline++;
	if (cmdline[0] == '!')	strcpy(cmdline, cmdline_old);

	strcpy(cmd_buf, cmdline);

	if (cmdline[0] != '!')	strcpy(cmdline_old, cmdline);

	// run a command
	TCLI_CMD* pCmd = cli_cmds;
	UINT err = -1;
	for (; pCmd->name; pCmd++) {
		if (!strncmp(pCmd->name, cmdline, strlen(pCmd->name))) {
			err = pCmd->func(cmdline,fd);
			break;
		}
	}
	return err;
}


#define CLI_CMD_LEN 		1024
void Thread_read(void *arg)
{
	int nbytes;
	int clientfd = *(int*)arg;
	char cmd[CLI_CMD_LEN+10];
	int ret;
	while(1){


		nbytes=lwip_recv(clientfd, cmd, sizeof(cmd),0);
		printf("getb:%d\n", nbytes);
		if(nbytes == -1 ){
			lwip_close(clientfd);
			printf("Socket Err\n");
			break;
		}
		if ((cmd[0] == 'E' && cmd[1] == 'X' && cmd[2] == 'I' && cmd[3] == 'T') || \
					(cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'i' && cmd[3] == 't')){		// For escape terminal	EX) exit EXIT
					lwip_close(clientfd);
					printf("Socket closed(%d)!\n", clientfd);
					break;
		}



		if (nbytes > 2){
					cmd[nbytes] = '\0';
//					sprintf(cmd, "%s %d ", cmd, clientfd);
//					printf("%s %d", cmd, nbytes);
					ret = cli_stdin_request_(cmd,clientfd);
					printf("ret: %d\n",ret);
					if (ret){
						lwip_send(clientfd, "BAD CMD", strlen("BAD CMD"), 0);
						printf("Bad or not command!\n");
					}

		}

	//	vTaskDelay(10);
	}

}


void NControl(void)
{

	printf("NControl start\n");

int lSocket;
struct sockaddr_in sLocalAddr;

lSocket = lwip_socket(AF_INET, SOCK_STREAM, 0);
if (lSocket < 0) return;

memset((char *)&sLocalAddr, 0, sizeof(sLocalAddr));
sLocalAddr.sin_family = AF_INET;
sLocalAddr.sin_len = sizeof(sLocalAddr);
sLocalAddr.sin_addr.s_addr = htonl(INADDR_ANY);
sLocalAddr.sin_port =lwip_htons(5556);

if (lwip_bind(lSocket, (struct sockaddr *)&sLocalAddr, sizeof(sLocalAddr)) < 0) {
        lwip_close(lSocket);
        printf("NControl bind Close\n");
        return;
}
if ( lwip_listen(lSocket, 20) != 0 ){
        lwip_close(lSocket);
        printf("NControl listen Close\n");
        return;
}
while (1) {



        int clientfd;
        struct sockaddr_in client_addr;
        int addrlen=sizeof(client_addr);
        char buffer[1024];
        int nbytes;

        clientfd = lwip_accept(lSocket, (struct sockaddr*)&client_addr, (socklen_t)&addrlen);
        if (clientfd>0){
        	printf("NControl accept\n");
        	vTaskCreate("read", Thread_read,(void*)&clientfd, LV4_STACK_SIZE, LV3_TASK_PRIO);
        }
    }
    lwip_close(lSocket);
}
