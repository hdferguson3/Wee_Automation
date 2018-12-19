// Program to write to SQL Database

#include <stdio.h>
#include <mysql/mysql.h>
#include "SQL_write.h"

void Write_to_SQL(char query[])
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *server = "localhost";
	char *user = "pi";
	char *password = "raspberry";
	char *database = "welldb";
		
	conn = mysql_init(NULL);
	printf("fomated query is: %s...\n", query);	
		
	// Connect to database

	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		printf("Connection error...\n %s\n",stderr);
		mysql_close(conn);
		exit(1);
	}

	//Query database
 
	if (mysql_query(conn, query))
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}

	res = mysql_use_result(conn);
	printf("Query result: %s\n",res);

	//Close connection
	printf("Closing MYSQL connection...\n");
	mysql_free_result(res);
	mysql_close(conn);

}
