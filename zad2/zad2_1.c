
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

  if(argc != 2)
  {
    perror("argc");
    return 1;
  }

  int i, startTime;
  time_t tt;
  startTime = time(&tt);
  srand(startTime);

  int file;
  char buf[124];


  file = open(argv[1],O_WRONLY | O_CREAT);

  if(file < 0)
  {
    perror("open");
    return 1;
  }


  for(i = 1; i<=10; i++)
  {
    sprintf(buf, "%d", rand()%90 + 10);
    printf("%d.Random number is: %s \n", i,buf);

    if(write(file,&buf,strlen(buf)) < 0)
    {
      perror("open");
      return 1;
    }

    if(write(file," ",strlen(" ")) < 0)
    {
      perror("open");
      return 1;
    }
  }

  close(file);

  return 0;


}
