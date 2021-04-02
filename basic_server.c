#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include "tcp.h"
#include "leercadena.h"

#define MAX 80

// Function designed for chat between client and server. 
char *func(int sockfd, char comando) 
{
	char *filename = "texto.txt";
  char comando2[BUFSIZ];
  strcpy(comando2, comando);
  printf("%s\n",comando2);
  
  //execvp(vector[0],vector);

  strcat(comando2," > texto.txt");

  printf("%s\n",comando2);

  system(comando2);

	return filename;
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

	while (1)
	{
		//char buff[MAX]; 
		//bzero(buff,MAX);
		//char *filename;
		char buff[BUFSIZ];
		bzero(buff,BUFSIZ);
		char ack[MAX_TCP_ACK] = {0};
		TCP_Read_String(connfd, buff, MAX); 

		Send_ACK(connfd);

		/*

		// Se ejecuta el comando
		pid_t pid, pid_temp;
		pid = fork();
					
		if(pid < 0){
		fprintf(stderr, "Error creating Child process \n");
		exit (1);
		}
					
		if (pid == 0) 
		{
			// Ejecución del comando
			printf("Ejecución comando");
			char *p = func(connfd, buff);
			printf("Salida comando");
			//Send_ACK(socket);
			// Envio del nombre
			TCP_Write_String(connfd, p);
			Recv_ACK(socket);
			//Envio del archivo
			TCP_Write_String(connfd, buff);
			//	Recv_ACK(connfd);
			TCP_Send_File(connfd,buff);
			break;
		}

		// Proceso padre espera por terminación de nuevo proceso
		// y continua esperando por otro comando.
		pid_temp = wait(NULL);
		assert(pid == pid_temp);
		*/
	}
	

	

/**


	TCP_Write_String(connfd, filename); Recv_ACK(connfd);
	TCP_Send_File(connfd,filename);

	close(socket); 

	printf("Se leyo %s\n",buff);

	// Function for chatting between client and server 
	func(connfd); 

	*/

	// After chatting close the socket 
	close(socket); 
} 

