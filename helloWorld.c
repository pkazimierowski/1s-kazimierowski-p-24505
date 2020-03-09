#include <stdio.h>

int main(int argc, char *argv[]){
	
	
	int i = 0;

	for(i = 0 ; i < argc; i++){
	
	if ( i == 0 ){
		
		printf("Program name is %s\n", argv[i]);
		continue;
		}
	printf("Arg %d has value %s\n", i, argv[i]);
	
	}
	
	
	//printf("Hello World \n");
	
	return 0;
}


