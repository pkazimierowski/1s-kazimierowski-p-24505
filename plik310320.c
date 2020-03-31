#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])

{
	//variables section
	int input_fd, output_fd;
	ssize_t ret_in, ret_out;
	char buffer[BUF_SIZE];
	//end of variables section
	if(argc !=3 || strcmp(argv[1], "--help") ==0)
	{
		fprintf(stderr, "Usage: %s file_origin file_dest\n", argv[0]);
		return 1;
	}
	//open file for readnig
	input_fd = open(argv[1], O_RDONLY);
	
	if(input_fd== -1)
	{
		perror("open");
		return 2;
	}
	
	//open file for writing
	if((output_fd = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0644))== -1)
	{
		perror("create");
		return 2;
	}
	
	while((ret_in = read(input_fd, &buffer, BUF_SIZE))> 0)
	{
		ret_out=write(output_fd, &buffer, ret_in);
		if(ret_out != ret_in)
		{
			perror("copy");
			return 3;
		}
	}
	close(input_fd);
	close(output_fd);
	
	return 0;
	
}
