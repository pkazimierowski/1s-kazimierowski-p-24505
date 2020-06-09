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
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

  if(argc != 2)
  {

    printf("Brak parametru!\n");
    return 1;
  }

  char fileName[256] = "zaliczenie/";
  strcat(fileName, argv[1]);
  FILE *wp; // wskaźnik do pliku

  DIR *dirEtc; // wskaźnik do otwarcia katalogu /etc
  struct dirent *pDirEtc; // struktura odpowiedzialna za odczyt zawartości katalogu

  int pid;


  pid = fork();

  if(pid < 0)
  {
    fprintf(stderr, "Fork Failed \n");
    exit(1);
  }
  else if(pid == 0)
  {
  //Tworze katalog "zaliczenie"
  if(mkdir("zaliczenie", 0744)  != 0 && errno != EEXIST)
  {
    perror("mkdir");
    exit(1);
  }
//otwieram  plik
  if ((wp = fopen(fileName, "w")) == NULL)
  {
    perror("fopen");
    exit(1);
  }
//otwieram katolg /etc
  if((dirEtc = opendir("/etc")) == NULL)
  {
    perror("openDir: ");
    exit(1);
  }
//pętla odczytuje pliki wewnątrz katalogu /etc oraz zapiosuje to do pliku
  while ((pDirEtc = readdir(dirEtc)) != NULL)
  {
    if(pDirEtc->d_type == DT_REG)
    {
    fputs(pDirEtc->d_name, wp);
    fputc('\n', wp);
    }
  }
  printf("pid dziecka: %d \npid rodzica: %d\n",getpid(),getppid());
//zamykanie pliku, katalogu i zamknięcie procesu
  closedir (dirEtc);
  fclose(wp);
  exit(0);
}
wait(&pid);
if (WIFEXITED(pid))
{
 printf("Proces dziecka został zakończony pomyślnie\n");
}
printf("Koniec programu\n");
  return 0;
}
