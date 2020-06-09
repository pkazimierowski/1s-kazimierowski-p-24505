#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>



int main(int argc, char *argv[])
{

  int pid,pidParent;
  pidParent = 0;

  pid = fork();

  if(pid < 0)
  {
    fprintf(stderr, "Fork Failed \n");
    return 1;
  }
  else if( pid == 0)
  {
    int fd;
    char filename[] = "plik.txt";
    fd = open(filename,O_CREAT|O_WRONLY, 0777);
    char buf[124];

    if (fd < 0)
    {
      perror("open file");
      exit(1);
    }

    for(int i = 9; i <=99; i+=3)
    {
        sprintf(buf, "%d", i);
        if(write(fd,buf,strlen(buf)) < 0 )
        {
          perror("write");
          exit(1);
        }
        if(write(fd," ",strlen(" ")) < 0 )
        {
          perror("write");
          exit(1);
        }
    }

    close(fd);
    exit(0);
  }
    pidParent = wait(&pid);
  if (WIFEXITED(pid))
  {
   printf("Chilld ended with status: %d \n", WEXITSTATUS(pid));
  }

return(0);
}
