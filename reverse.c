#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_BUFFER 20


void free_2darray(char **array, size_t size)
{

    for(int i = 0; i < size; ++i)
    {
        free(array[i]);
        array[i] = NULL;
    }

    free(array);
}

void expand_2dArray(char** array, int index, size_t size)
{

    array = (char**) realloc(array ,size * sizeof(char*));
    if(array == NULL)
    {
        fprintf(stderr, "Expand_2dArray : memory allocation failed\n");
        return;
    }

    for (int i = index; i < size; ++i)
    {
        array[i] = (char*)malloc(size * sizeof(char*));
        if(array[i] == NULL)
        {
            fprintf(stderr, "Expand_2dArray : memory allocation failed\n");
            return;
        }

    }

}

void reverse(char* in_name, char* out_name)
{
	char* buffer =  NULL;
	size_t len = INITIAL_BUFFER;
	size_t array2d_size = 20;
	size_t counter = 0;
	FILE* in_stream = fopen(in_name, "r");
	FILE* out_stream= fopen(out_name, "w+");

    if(in_stream == NULL || out_stream == NULL)
    {
        perror("FOPEN");
        return;
    }


	buffer = (char*)malloc(INITIAL_BUFFER * sizeof(char));
	char **array = (char**)malloc(array2d_size * sizeof(char*));
    for (int i = 0; i < array2d_size; ++i)
    {
        array[i] = (char*)malloc(array2d_size * sizeof(char*));
    }


	while(getline(&buffer, &len, in_stream) != -1)
	{
	    if(counter == array2d_size)
        {
	        array2d_size += 20;
            array = (char**) realloc(array ,array2d_size * sizeof(char*));
            for (int i = counter; i < array2d_size; ++i)
            {
                array[i] = (char*)malloc(array2d_size * sizeof(char*));
            }

        }
        strcpy(array[counter], buffer);
		counter += 1;
	}


	for(int i = counter; i >= 0; --i)
    {
    	fwrite(array[i], strlen(array[i]), sizeof(char), out_stream);
        //printf("%s", array[i]);
    }


    fclose(out_stream);
    fclose(in_stream);
    free_2darray(array, array2d_size);
	free(buffer);

}

int main(int argc, char* argv[]){

	if(argc <= 1)return 0;

	else if(argc > 3) return 1;

	else if(strcmp(argv[1], argv[2]) == 0)
	{
		fprintf(stderr, "Input and Output are the same file\n");
		return 1;
	}

	reverse(argv[1], argv[2]);

	return 0;
}