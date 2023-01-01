#include <stdio.h>
#include <errno.h>


#define BUFFER_SIZE (4096)
int open_file(char* filename)
{
	
	FILE* file = fopen(filename, "r");
	char buffer[BUFFER_SIZE];

	if(file == NULL)
	{
		perror("Failed to open file");
		return 1;
	}

	
	while(fgets(buffer, BUFFER_SIZE, file))
	{
	
		printf("%s", buffer);	

	}
	
	fclose(file);
}



int main(int argc, char *argv[])
{

	if(argc == 1)
		return 0;

	for(int i = 1; i < argc; ++i)
	{
		open_file(argv[i]);
		printf("END OF FILE ----\n\n");
	}

	
	return 0;
}		
