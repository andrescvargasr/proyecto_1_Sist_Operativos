# Shell remoto

En este repositorio se encuentra la solución de primer miniproyecto de Sistemas Operativos y Servicios de Red, dictada por el profesor John Sanabria, el cual desarrolla un shell remoto que sigue el esquema cliente/servidor. 

Realizado por:

- Maria Camila Montaño Polania.
- Andres Camilo Vargas Román.

---

La siguiente gráfica muestra lo que se espera sea la interacción entre el shell cliente y el servidor. 

<img src="figures/MiniShellRemoto.png" alt="Mini Shell Remoto Cliente/Servidor" width="650"/>

Al lado derecho de la gráfica se observa el servidor quien está esperando por peticiones de un cliente.
Este servidor espera recibir comandos a través de la red de parte de un proceso cliente.

El cliente es un proceso que está en espera de leer por teclado un comando y una vez recibido ese comando, se envía al servidor.
El cliente creará un hijo quien se encarga de interactuar con el servidor, enviar el comando y esperar por la respuesta del comando.
Una vez este proceso hijo reciba la respuesta del servidor, imprime la respuesta y termina su ejecución.
El cliente (padre) volverá a presentar el *prompt* (`>`) y quedará en espera del siguiente comando por parte del usuario.

El servidor al recibir una solicitud a través de la red, crea un proceso hijo quien se encargará de procesar dicha solicitud. 
El proceso hijo recibe la solicitud y la ejecuta con la función `execvp` o alguna de las funciones miembros de la familia `exev*`.
El proceso (padre) toma la salida del proceso hijo y la envía al lado del cliente.

---

A continuación, se da una descripción de la ejecución del proyecto:

## Vagrant

En el proyecto se emplea Vagrant y VBoxManage para crear una máquina virtual Ubunut Xenial que usa un núcleo de la CPU y 1024 MB de memoria.

Para iniciar la máquina virtual, digite en la terminal:

```bash
vagrant up
```

Una vez se inicie la máquina virtual, se accede a ella a través de SSH mediante el comando:

```bash
vagrant ssh
```

Con el propósito de usar el modelo cliente/servidor, se recomienda en otro terminal, ejecutar el mismo comando, de modo que se acceda desde dos espacios de usuarios.

## Repositorio

Una vez se encuentre en la máquina virtual, se puede acceder a la carpeta del proyecto en ambas sesiones, mediante el comando:

```
cd proyecto_1_Sist_Operativos
```

## `basic_client.c` y `basic_server.c`

En esta carpeta, se han creado los archivos principales del proyecto conocidos como `basic_client.c` y `basic_server.c` los cuales ejecutan el cliente y el servidor. Para usar estos archivos, primero se deben compilar y crear la aplicación, lo cual se hace empleando el comando

```bash
make basic_client_server
```

Este comando se encargará de crear todos los archivos *.o necesarios y hará en enlace que permitirá tener los ejecutables del proyecto.

### Run `basic_client` y `basic_server` 

Para ejecutar el servidor ejecute el comando:

```bash
./basic_server 12358
``` 

En la otra terminal ejecute el cliente de la siguiente manera:

```bash
./basic_client localhost 12358
```

El cliente envía la cadena `hola mundo` y esta es recibida por el servidor quien lo imprime en su pantalla.

<!--### `file_client` y `file_server` 

Para ver en operación este ejemplo se debe ejecutar el comando `make file_client_server` que se encarga de compilar los archivos objeto que requiere este aplicativo (`tcp.o`) y el cliente (`file_client`) y el servidor (`file_server`). 

Para ejecutar el servidor ejecute el comando `file_server 12358 tcp.c`. 
El servidor apenas reciba una solicitud, enviará el archivo `tcp.c` al cliente.

Abra otra terminal y en ella ejecute el cliente de la siguiente manera `./file_client localhost 12358 demo.c`.
Una vez se ejecute, el cliente recibirá el archivo del servidor y lo almacenará con el nombre `demo.c`.
-->

<!--
## Elementos que quedan pendientes

* Manejar los errores que se puedan presentar a la hora de ejecutar un comando al lado del servidor. El cliente debe ver ese error.

* Se debe implementar el cambio de directorio emitido desde el cliente y este se vea reflejado en el servidor. Es decir, que se posibilite el cambio de directorio.

* Brindar soporte para la ejecución de comandos compuestos y unidos por el *pipe* (`|`).

* Brindar soporte para la redirección de la salida de la ejecución de un comando. Esta redirección deberá residir al lado del cliente. Quizá se requiera un preprocesamiento del lado del cliente de modo que se haga conciencia que la salida no irá a pantalla sino a un archivo.
-->

