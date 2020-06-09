#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{

  char buf[3];
  int file;
  if(argc != 2)
  {
    perror("argc");
    return 1;
  }


  file = open(argv[1],O_RDONLY);

  if(file < 0)
  {
    perror("open");
    return 1;
  }

  int strToInt;


  while(read(file,buf,sizeof(buf)))
  {
    //strToInt = strtol(buf, NULL, 10);
    sscanf(buf, "%d", &strToInt);
    printf("%d \n", strToInt*3 );
  }

close(file);



}
