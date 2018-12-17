// Program to get and format time in to SQL TIMESTAMP type

#include "get_SQL_timestamp.h"
#include <time.h>

char timestamp[80];

int get_time(void)
{
	time_t rawtime;
	struct tm *info;

	time( &rawtime );
	info = localtime( &rawtime );

	strftime(timestamp, 80, "%Y-%m-%d %H:%M:%S", info);
}
