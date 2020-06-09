/*
Napisz program, który tworzy nowy proces potomny.
Rodzic musi czekać na dziecko.
Nowy proces potomny, użyje wywołania systemowego exec, aby wywołać program
ls do wyświetlenia wszystkich elementów (plików i folderów) w aktualnym katalogu
 jako listę.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>


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
    execl("/bin/ls","ls","-l",NULL);
    perror("Blad funkcji exec");
    exit(0);
  }
    pidParent = wait(&pid);
return 0;
}
