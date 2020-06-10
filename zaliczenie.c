/*
Napisz program, który będzie spełniał następujące funkcje:

Nazwa pliku do utworzenia zostanie przekazana przez użytkownika jako parametr do wywołania programu.
Program stworzy nowy katalog zaliczenie, z uprawnieniami 0744
Plik będzie zawierał wszystkie nazwy plików regularnych z katalogu /etc. Zapis do pliku ma się odbywać przy pomocy buforowanych operacji I/O.
Powyższe operacje (tworzenie nowego katalogu, tworzenie pliku) odbywają się w procesie potomnym
Proces rodzica czeka na zakończenie procesu potomnego.
Przed zakończeniem programu wyświetl informację o numerze PID rodzica, dziecka, oraz to że program się zakończył.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char *argv[])
{

  if(argc != 2) // sprawdzam czy uzytkowinik podal parametr
  {
    printf("Brak parametru!\n");
    return 1;
  }
//definiowanie zmiennych

  char fName[256] = "zaliczenie/";
  strcat(fName, argv[1]);

  FILE *file;

  DIR *direntEtc;
  struct dirent *structDirentEtc;

  int pid;
  pid = fork();

  if(pid < 0)
  {
    fprintf(stderr, "Blad procesu \n");
    exit(1);
  }
  else if(pid == 0)
  {
  if(mkdir("zaliczenie", 0744)  != 0 && errno != EEXIST)
  {
    perror("mkdir");
    exit(1);
  }
  file = fopen(fName, "w");
  if (file  == NULL)
  {
    perror("fopen");
    exit(1);
  }
  direntEtc = opendir("/etc");
  if(direntEtc == NULL)
  {
    perror("openDir: ");
    exit(1);
  }

  while ((structDirentEtc = readdir(direntEtc)) != NULL)
  {
    if(structDirentEtc->d_type == DT_REG)
    {
    fputs(structDirentEtc->d_name, file);
    fputc('\n', file);
    }
  }
  printf("pid dziecka: %d \npid rodzica: %d\n",getpid(),getppid());

  closedir(direntEtc);
  fclose(file);
  exit(0);
}
wait(&pid);
if (WIFEXITED(pid))
{
  if (WEXITSTATUS(pid) == 0){
 printf("Proces dziecka został zakończony pomyślnie\n");
}else{
  printf("W procesie dziecka wystąpił błąd\n");
}
}
printf("Koniec programu\n");
  return 0;
}
