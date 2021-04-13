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
void crear_archivo(int sockfd, char *comando, char *p) 
{
	char t[BUFSIZ]  = "texto.txt";
	char output[3] = "-v";
	output[strlen(output) - 1] = '\x0';
	p = t;
  char *comando2 = comando;


	char buffer[BUFSIZ];
	bzero(buffer,BUFSIZ);

	strcpy(buffer, comando2);


  //printf("%s\n",comando2);
  
  //execvp(vector[0],vector);

	//char **vector;
	//vector = de_cadena_a_vector(comando);
	//printf("%s\n",vector[0]);
	//printf("%ld\n",strlen(vector[0]));
	//char size_0[BUFSIZ];
	//bzero(size_0,BUFSIZ);
	//strcpy(size_0,vector[0]);

	// Verificar rm
	char verifica_rm[2] = "rm";
	//int comp = strncmp(size_0,verifica_rm,2);

	int comp = strncmp(buffer,verifica_rm,2);
	char *buffer2 = strndup(comando2, 2);
	printf("Point: %s\n", buffer2);

	// Si el comando es "rm", se agrega la bandera -v
	if (comp == 0)
	{
		printf("Verifica rm\n");

		char buffer3[BUFSIZ];

		strcpy(buffer3, (char *)(buffer + 2));

		printf("Buffer: %s\n", buffer3);
		
		
		//fgets(buffer, BUFSIZ, comando2);
		strcat(buffer2, " -v ");
		//printf("Buffer 2: %s\n", buffer2);
		strcat(buffer2, buffer3);
		//printf("New Buffer: %s\n", buffer2);
		strcpy(comando2, buffer2);

	}
	
  strcat(comando2," > texto.txt");
  printf("%s\n",comando2);
  system(comando2);
}

void archivo_a_variable(char *p)
{
	FILE *in_file  = fopen(p, "r"); // read only 
	//printf("Acceder archivo: %s\n",p);

	// test for files not existing. 
	if (in_file == NULL) 
	{   
		printf("Error! No se puede abrir el archivo.\n"); 
		exit(-1); // must include stdlib.h 
	}

	char dato1[BUFSIZ];
	bzero(dato1,BUFSIZ);

	// Limpiar la variable global
	bzero(buff,BUFSIZ); 

	fgets( dato1, BUFSIZ, in_file );    // stdin - keyboard 
	//printf("Ver archivo:\n%s\n",dato1);

	while(fscanf(in_file, "%s", dato1)!=EOF){ 
		strcat(dato1, "\n");
		strcat(buff,dato1);
	}
	//printf("%s ", buff );

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
		// Limpiar variable global buff
		bzero(buff,BUFSIZ);

		char ack[MAX_TCP_ACK] = {0};

		// Leer mensaje
		TCP_Read_String(connfd, buff, MAX); 

		//printf("Envío ACK de recibo de comando.\n");
		Send_ACK(connfd);

		// Se ejecuta el comando en un child y el parent
		// espera por la respuesta
		pid_t pid, pid_temp;
		pid = fork();
					
		if(pid < 0){
		fprintf(stderr, "Error creating Child process \n");
		exit (1);
		}
					
		if (pid == 0) 
		{
			// Ejecución del comando
			//printf("Ejecución comando:\n%s\n", buff);
			if (!strcmp("exit", buff))
			{
				printf("Adios...\n");

				// close the socket 
				close(socket); 

				break;
			}
			char p[BUFSIZ] = "texto.txt";
			char p_client[BUFSIZ] = "texto2.txt";
			crear_archivo(connfd, buff, p);
			//printf("Salida comando: %s\n", p);
			//Send_ACK(socket);

			// Envio nombre del archivo
			TCP_Write_String(connfd, p_client);
			//printf("Envío nombre\n");
			Recv_ACK(connfd);
			//printf("Recibido ACK nombre.\n");
			
			// Envio del archivo
			bzero(buff,BUFSIZ);
			//archivo_a_variable(p);
			//printf("Imprimir archivo 2:\n\n\n%s\n", buff );
			//TCP_Write_String(connfd, buff);
			TCP_Send_File(connfd,p);
			printf("Envío archivo\n");
			Recv_ACK(connfd);
			//printf("Recibido ACK archivo.\n");
			
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
	// After chatting close the socket 
	close(socket); 
	return 0;
} 

