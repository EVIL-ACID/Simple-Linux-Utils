#include <stdio.h>
#include <errno.h>
#include <string.h>
#define BUFFER_SIZE (4096)
int open_file(char* filename, char* search)
{

        FILE* file = fopen(filename, "r");
        size_t len = 0;
	char buffer[BUFFER_SIZE];

        if(file == NULL)
        {
                perror("Failed to open file");
                return 1;
        }


        while(fgets(buffer, BUFFER_SIZE, file))
        {

		char* found = strstr(buffer, search);
		if(found)
                        printf("%s", buffer);

        }

        fclose(file);
}



int main(int argc, char *argv[])
{

        if(argc == 1)
                return 0;

     
        open_file(argv[2], argv[1]);
        printf("END OF FILE ----\n\n");


        return 0;
}

