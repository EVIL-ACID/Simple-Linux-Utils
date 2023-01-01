#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>



size_t file_size(FILE* file)
{
	size_t size = 0;
	fseek(file, 0L,SEEK_END);
	size = ftell(file);
	fseek(file, 0L, SEEK_SET);

	return size;
}


void zip_file(char* fileName)
{

 	FILE* stream = fopen(fileName, "r");
	FILE* out_stream = fopen("zip_out.z", "wb+");
        char* buffer = NULL;
        size_t buffer_size = 0;
      
        buffer_size = file_size(stream);
        buffer = malloc(buffer_size + 1);
        fread(buffer, buffer_size, sizeof(char), stream);

   
	int counter = 1;
	char ch = buffer[0];

	for (int i = 0; i < buffer_size; ++i)
	{
		if(buffer[i] != buffer[i + 1])
		{
			fputc(counter, out_stream);
			fputc(buffer[i], out_stream);
			ch = buffer[i];
			counter = 1;
		}
		else{
			counter++;
		}
	}

	free(buffer);
	buffer = NULL;
	fclose(stream);
	fclose(out_stream);
}

void uzip_file(char* fileName)
{

	FILE* stream = fopen(fileName, "rb");
        
	int num;
	int ch;
	do{
		num = fgetc(stream);
		ch = fgetc(stream); 
		for(int i = 0; i < num; ++i)
		{
			printf("%c", ch);
		}
	}while(ch != EOF || num != EOF);

	fclose(stream);
}

int main(int argc, char* argv[]){

	if(argc == 1) return 1;
	
	if(strcmp(argv[1], "zip") == 0)
	{
		zip_file(argv[2]);
	}
	else if(strcmp(argv[1], "unzip") == 0)
	{

		uzip_file(argv[2]);

	}	
	
	return 0;
}	
