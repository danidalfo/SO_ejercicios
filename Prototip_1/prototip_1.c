#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Pregunta al usuario el nombre de un jugador i devuelve el
// identificador y la fecha de las partidas que ha jugado.

int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	
// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;

// Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// Inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "dramatic_shark",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}

		char nombre [20];
	// Pregunto el nombre del jugador
	printf ("Dame el nombre del jugador\n"); 
	scanf ("%s", nombre);
	
	char consulta [80];
	strcpy (consulta,"SELECT partidas.id_p,partidas.fecha FROM jugadores,partidas,relacion WHERE jugadores.nombre = '");
	strcat (consulta, nombre);
	strcat (consulta,"' AND jugadores.id_j = relacion.jugador AND partidas.id_p = relacion.partida;");
	
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//recogemos el resultado de la consulta. 

	resultado = mysql_store_result (conn);
	
	// Obtenemos la primera fila que se almacena en una
	// variable de tipo MYSQL_ROW
	
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No ha jugado ahun.\n");
	else
		while (row !=NULL) {
			// la columna 0 contiene el id de la partida
			int id;
			id = atoi (row[0]);
			printf ("ID de la partida: %s, Fecha: %s\n", id , row[1]);
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
	}

	mysql_close (conn);
	exit(0);
}