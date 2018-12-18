#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int main()
{
    char read_buffer[] = "11.0,12.1,13.2,14.3,1";
    char** tokens;
    char dataArray[5] = {'0.0','0.0','0.0','0.0','0','\0'};
    char *value;

    printf("read buffer %s\n\n", read_buffer);

    tokens = str_split(read_buffer, ',');

    if (tokens)
    {
        int i;
        for (i = 0; *(tokens + i); i++)
        {
            value = *(tokens+i);
            printf(" value is %s\n", value);
            //dataArray[i] = value;
	        free(*(tokens + i));
        }

        free(tokens);
    }
    //printf("Meter2 value is %d\n", dataArray[1]);
    char *array;
    const char delim = ",";
	array = strtok(read_buffer, delim);
		while(array != NULL)
	{
		printf("%s\n", array);
		array = strtok(NULL,delim);
	}
    return 0;
}
