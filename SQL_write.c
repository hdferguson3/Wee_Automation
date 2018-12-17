// Program to write to SQL Database

#include <stdio.h>
#include <mysql/mysql.h>
#include "get_SQL_timestamp.h"

void main(void)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *server = "localhost";
	char *user = "pi";
	char *password = "raspberry";
	char *database = "welldb";
	int meter1 = 11.1;
	int meter2 = 22.2;
	int meter3 = 33.3;
	int press1 = 44.4;
	int pump1 = 0;
	char query[1024];

	conn = mysql_init(NULL);
	get_time ();
	sprintf(query, "INSERT INTO data (meter1,meter2,meter3,press1,pump1,timestamp) VALUES (%d, %d, %d, %d, %d, '%s')",meter1,meter2,
	meter3,press1,pump1,timestamp);
	printf("%s\n",query);

	// Connect to database

	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	//Query database
 
	if (mysql_query(conn, query))
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	res = mysql_use_result(conn);

	//Close connection

	mysql_free_result(res);
	mysql_close(conn);

}
