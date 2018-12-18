#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parse_buffer_1.h"
#include "SerialPort_read.h"

//int size=atoi(token);
int data[];

int parse_buffer()
{
	
	read_serial();

	// Returns first token 
	char *token = strtok(read_buffer, ","); 
	int i=0;
	data[i]=atoi(token);

	// Keep printing tokens while one of the 
	// delimiters present in str[]. 
	while (token != NULL) 
	{ 
		//printf("%s\n", token); 
		token = strtok(NULL, ","); 
		if(token !=NULL){
		data[i+1]=atoi(token);
		i=i+1;
		}
	}		  
}

