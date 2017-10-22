#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>


// Función para conectar a la base de datos.

int Conecta_base()
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n",mysql_errno(conn), mysql_error(conn));
		return -1;
	}
    
	conn = mysql_real_connect (conn, "localhost","root","mysql", "dramatic_shark",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		return -1;
	}
    
	else return 0;
}

// Función para buscar un jugador en la tabla.
// Devuelve 0 si esta en la tabla.
// Devuelve -1 si no ha podido consultar
// Devuelve -2 si el usuario no esta en la tabla

int Buscar_en_Tabla(char name[20],char password[20])

{
	char consulta[100];
	strcpy (consulta,"SELECT * FROM jugadores WHERE nombre = '"); 
	strcat (consulta, name);
	strcat (consulta,"' AND password = '");
	strcat (consulta, password);
	strcat (consulta, " '");
	
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	err=mysql_query (conn, consulta); 
	if (err!=0) 
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		return -1;
	}	
	resultado = mysql_store_result (conn); 
	row = mysql_fetch_row (resultado);
	
	if (row==NULL) 
		return -2;
	else
		return 0;
}


// Función para contar usuarios en la tabla

int Contar_Tabla()
{
	int cont=0;
	MYSQL_RES *resultado;
    MYSQL_ROW row;
	int err;	
	err=mysql_query (conn, "SELECT MAX(id_j) FROM jugadores"); 
	if (err!=0) 
	{printf("ERROR al contar");
		return -1;}
	else{
		resultado = mysql_store_result (conn); 
		row=mysql_fetch_row(resultado);
		cont=atoi(row[0]);
		printf("%d",cont);
		return cont;
	}
}

// Función para registrar un usuario.
// Devuelve 0 si ha funcionado.
// Devuelve -1 si no ha podido registrar.
// Devuelve -2 si el usuario ya existe.

int Registro(char name[20],char password[20]){
	int err;
	int b;
	char consulta[100];
	char ID [6];
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int id;
	
	b=Buscar_en_Tabla(name,password);
	
	if(b==-2)
	{
		
		id= Contar_Tabla();
		id++;
		
		strcpy (consulta,"INSERT INTO jugador VALUES("); 
		strcat (consulta, id); 		
		strcat (consulta,",'");
		strcat (consulta, name);
		strcat (consulta,"','");
		strcat (consulta, password);
		strcat (consulta,"')");
		printf("consulta = %s\n", consulta);
		err=mysql_query (conn, consulta);
		 
	
	if (err!=0) 
	{
		printf ("Error al añadir datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		return -1;
	}	
	else 
		return 0;
	}
	
	if (b==-1)
		return -1;
    
	if (b==0)
	printf ("El usuario ya existe!")
    return -2;
	
	else 
		return -1;
	
}

// MAIN

int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char buff[512];
	char buff2[512];
	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	// Fem el bind al port
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// escucharemos en el port 9050
	serv_adr.sin_port = htons(9050);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	//La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 2) < 0)
		printf("Error en el Listen");
	
	int i;
	// Atenderemos solo 5 peticione
	for(i=0;i<7;i++){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexi?n\n");
		//sock_conn es el socket que usaremos para este cliente
		
		// Ahora recibimos su nombre, que dejamos en buff
		ret=read(sock_conn,buff, sizeof(buff));
		printf ("Recibido\n");
		
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		buff[ret]='\0';
		
	
        
        char *p = strtok( buff, "/");
			int codigo =  atoi (p);

// Leemos el codigo y segun que numero nos envian hacemos una cosa o otra.            
		
        switch (codigo)
        {
            
		// Codigo 1 = Registrarse
        	case 1:
			
            int regi;	
                
             p = strtok( NULL, "/");
             char nombre[20];
             strcpy (nombre, p);
             p = strtok( NULL, "/");
             char password[20];
             strcpy (password, p);
             
             regi = Registro(nombre,password);
             
                if(regi==0)
					strcpy (buff2,"Registrado");
				if(regi==-2)
					strcpy (buff2,"Este usuario ya existe,");
				if(regi==-1)
					strcpy (buff2,"ERROR al registrar,");
                    
				break;































