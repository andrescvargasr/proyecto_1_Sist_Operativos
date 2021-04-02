#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include "tcp.h"
#include "leercadena.h"

#define MAX 80

char buff[BUFSIZ];

// Function designed for chat between client and server. 
void func(int sockfd, char *comando, char *p) 
{
	char t[BUFSIZ]  = "texto.txt";
	p = t;
  char *comando2 = comando;
  //strcpy(comando2, comando);
  printf("%s\n",comando2);
  
  //execvp(vector[0],vector);

  strcat(comando2," > texto.txt");

  printf("%s\n",comando2);

  system(comando2);
} 

void archivo_a_variable(char *p)
{
	FILE *in_file  = fopen(p, "r"); // read only 
	printf("Acceder archivo: %s\n",p);

	// test for files not existing. 
	if (in_file == NULL) 
	{   
		printf("Error! Could not open file\n"); 
		exit(-1); // must include stdlib.h 
	}

	char dato1[BUFSIZ];
	bzero(dato1,BUFSIZ);
	//char dato2[BUFSIZ];
	bzero(buff,BUFSIZ); 
	fgets( dato1, BUFSIZ, in_file );    // stdin - keyboard 
	printf("Ver archivo:\n%s\n",dato1);

	while(fscanf(in_file, "%s", dato1)!=EOF){ 
		strcat(dato1, "\n");
		strcat(buff,dato1);
	}
	printf("%s ", buff );

	fclose(in_file);
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
		//char buff[BUFSIZ];
		bzero(buff,BUFSIZ);
		char ack[MAX_TCP_ACK] = {0};
		TCP_Read_String(connfd, buff, MAX); 

		//printf("Envío ACK de recibo de comando.\n");

		Send_ACK(connfd);

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
			printf("Ejecución comando:\n%s\n", buff);
			if (!strcmp("exit", buff))
			{
				printf("Adios...\n");

				// close the socket 
				close(socket); 

				break;
			}
			char p[BUFSIZ] = "texto.txt";
			func(connfd, buff, p);
			printf("Salida comando: %s\n", p);
			//Send_ACK(socket);
			// Envio del nombre
			TCP_Write_String(connfd, p);
			printf("Envío nombre\n");
			Recv_ACK(connfd);
			printf("Recibido ACK nombre.\n");
			
			//Envio del archivo
			bzero(buff,BUFSIZ);
			archivo_a_variable(p);
			printf("Imprimir archivo 2:\n\n\n%s\n", buff );
			TCP_Write_String(connfd, buff);
			//	Recv_ACK(connfd);
			//TCP_Send_File(connfd,p);
			printf("Envío archivo\n");
			Recv_ACK(connfd);
			printf("Recibido ACK archivo.\n");
			
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

