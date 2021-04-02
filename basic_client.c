#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "tcp.h"
#include "leercadena.h"
#include "archivo.h"


void func(int sockfd) 
{ 
	char *buff = "hola mundo" + '\x0'; 
	TCP_Write_String(sockfd, buff); 
} 

int main(int argc, char* argv[]) 
{ 
	int socket, port; 
	char *host;

	char comando[BUFSIZ];

	if (argc != 3) {
		printf("Uso: %s <host> <puerto>\n",argv[0]);
		return 1;
	}
	host = argv[1];
	port = atoi(argv[2]);

	printf("Looking to connect at <%s,%d>\n",host,port);
	socket = TCP_Open(Get_IP(host),port);

	printf("Conexión exitosa\n");

	while (1)
	{
		pid_t pid, pid_temp;
		// Leer cadena
		printf("> ");
		bzero(comando, BUFSIZ);
		leer_de_teclado(BUFSIZ, comando);
		// si cadena == "exit" salir del ciclo
		if (!strcmp("exit", comando))
		{
			printf("Adios...\n");

			// close the socket 
			close(socket); 

			break;
		}
		
		// De lo contrario crear un nuevo proceso
		pid = fork();
		if (pid < 0)
		{
			fprintf(stderr, "Error al crear proceso hijo\n");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			char *filename = (char*)calloc(BUFSIZ,sizeof(char));
			assert(filename != NULL);
			// Envio el comando
			printf("Envío comando\n");
			TCP_Write_String(socket, comando);
			Recv_ACK(socket);
			printf("ACK recibido de envío comando.\n");
			
			// Espero por el nombre del archivo que tendra la salida del comando
			TCP_Read_String(socket, filename, BUFSIZ);
			printf("Nombre archivo recibido.\n");
			printf("Envío ACK recibido de nombre archivo.\n");
			Send_ACK(socket);
			/*
			// Recibo el archivo
			printf("Archivo a recibir [%s]\n",filename);
			TCP_Recv_File(sockfd, filename);
			Send_ACK(sockfd);
			// Muestra por pantalla el archivo
			cat_archivo(filename);
			// Se borra el archivo
			borrar_archivo(filename);
			*/
			break;
		}
		else
		{
			// Proceso padre espera por terminación de nuevo proceso
			// y continua esperando por otro comando.
			pid_temp = wait(NULL);
			assert(pid == pid_temp);
		}
		

		
		
		
	}

	return 0;
	
	// function for chat 
	//func(sockfd); 
} 

