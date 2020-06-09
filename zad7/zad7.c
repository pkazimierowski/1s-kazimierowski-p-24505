/*
Napisz program, który utworzy nowy plik z numerem PID aktualnego procesu.
Jeśli proces otrzyma sygnał SIGUSR1, PPID aktualnie działające procesu będzie dołączony do tego pliku.
Jeśli zostanie otrzymany sygnał SIGUSR2, plik jest czyszczony.
Po otrzymaniu któregokolwiek z tych sygnałów, program kończy działanie.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void my_hanlder(int signum)
{

  if (signum == SIGUSR1)
  {
    int fd;
    char filename[] = "plik.txt";

    printf("Przyszlo 1 \n");

    fd = open(filename,O_TRUNC | O_WRONLY);
    if (fd < 0)
    {
      perror("open file");
    }
    close(fd);
  }
  else if (signum == SIGUSR2)
  {
    printf("Przyszlo 2 \n");

    int ppid = getppid();
    char chppid[8];
    sprintf(chppid, "%d", ppid);
    int fd;
    char filename[] = "plik.txt";

    fd = open(filename, O_WRONLY | O_APPEND);
    if (fd < 0)
    {
      perror("open file");
    }
    if(write(fd,chppid,strlen(chppid)) < 0 )
    {
      perror("write");
    }
    printf("Gdzies jestem\n");
    close(fd);
  }
}

int main(int argc, char *argv[])
{
  int fd;
  int pid = getpid();
  int ppid = getppid();

  char chpid[8];
  char chppid[8];

  sprintf(chpid, "%d", pid);
  strcat(chpid, " ");
  sprintf(chppid, "%d", ppid);

  printf("PID: %s\nPPID: %s\n", chpid,chppid);
  signal(SIGUSR1, my_hanlder);
  signal(SIGUSR2, my_hanlder);
  char filename[] = "plik.txt";

  fd = open(filename,O_CREAT|O_WRONLY, 0777);
  if (fd < 0)
  {
    perror("open file");
    return 1;
  }
  if(write(fd,chpid,strlen(chpid)) < 0 )
  {
    perror("write");
    exit(1);
  }
  close(fd);
  pause();

  return 1;
}
