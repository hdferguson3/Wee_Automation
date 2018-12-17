// Main program to read sensor data and write data to database

#include <stdio.h>
#include <time.h>
#include "get_SQL_timestamp.h"

void main(void)
{
	get_time ();
	printf("Current time is %s\n", timestamp);
}
