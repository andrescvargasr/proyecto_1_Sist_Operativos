#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include "tcp.h"

#define MAX 80

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	
	
} 

// Driver function 
int main(int argc, char *argv[]) 
{ 
	int socket, connfd;  
	int puerto;

	if (argc != 2) {
		printf("Uso: %s <puerto>\n",argv[0]);
		return 1;
	}
	
	puerto = atoi(argv[1]);

	socket = TCP_Server_Open(puerto);
	connfd = TCP_Accept(socket);

	char buff[MAX]; 
	bzero(buff,MAX);
	//char *filename;
	char ack[MAX_TCP_ACK] = {0};
	TCP_Read_String(socket, buff, MAX); 

	Send_ACK(socket);

	// Se ejecuta el comando




	TCP_Write_String(connfd, filename); Recv_ACK(connfd);
	TCP_Send_File(connfd,filename);

	close(socket); 

	printf("Se leyo %s\n",buff);

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(socket); 
} 

