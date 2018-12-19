// Main program to read sensor data and write data to database

#include <stdio.h>
#include <time.h>
#include "get_SQL_timestamp.h"
#include "parse_buffer_1.h"
#include "SQL_write.h"

	int meter1 = 111;
	int meter2 = 222;
	int meter3 = 333;
	int press1 = 444;
	int pump1 = 0;
	char query_to_send[1024];
	
void main(void)
{
	get_time ();
	parse_buffer();
	meter1 = data[0];
	meter2 = data[1];
	meter3 = data[2];
	press1 = data[3];
	pump1 = data[4];
	sprintf(query_to_send, "INSERT INTO data (meter1,meter2,meter3,press1,pump1,timestamp) VALUES (%d,%d,%d,%d,%d,%s)",meter1,meter2,meter3,press1,pump1,time_stamp);
	Write_to_SQL(query_to_send);
	
}
