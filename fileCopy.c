#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char **argv){
	
	int output_fd, input_fd;
	char buffer[BUF_SIZE];
	
	sszie_t ret_in, ret_out;
	
	if(argc != 3)
	{
			printf("Usage : %s file_origin file_dest\n", argv[0]);
			return 1;
	}
	
	input_fd = open(argv[1] O_RDONLY);
	if(input_fd == -1) 
	{	
		fprintf(stderr, "Error while opening file: %s\n", argv[1]);
		return 2;
	}
	
	output_fd = open(argv[2], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	
	//ret_in = read(input_fd,buffer);

	
	
	return 0;
}
