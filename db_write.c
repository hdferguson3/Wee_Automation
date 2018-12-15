/* Simple C program that connects to MySQL Database server*/
#include <mysql/mysql.h>
#include <stdio.h>

int main()
{
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;

   char *server = "localhost";
   char *user = "pi";
   char *password = "raspberry"; /* set me first */
   char *database = "demodb";

   conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   /* send SQL query */
   if (mysql_query(conn, "INSERT INTO data (sensor1,timestamp) VALUES ('01','12:00pm 12/15/18')"))
   {
    printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    exit(1);
   }

   res = mysql_use_result(conn);

   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
}

