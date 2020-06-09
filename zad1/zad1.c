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

  int file1;
  int file2;
  //int ch;
  char nazwa[80];
  char *buf;
  //unsigned long counter = 1;
  char str1[80] = "";

  //sprawdzam czy użytkownik podał argument do uruchomienia programu
  if(argc != 2)
  {

    printf("provide file Name!\n");
    scanf("%s", nazwa);
    strcat(str1, nazwa);
    strcat(str1, ".red");

  }else{
      strcat(nazwa, argv[1]);
      strcat(str1, argv[1]);
      strcat(str1, ".red");
  }

  //otwieram i sprawdzam czy plik się otworzył
  file1 = open(argv[1], O_RDONLY);
  if(file1 < 0)
  {
    perror("open first file");
    return 1;
  }

  //otwarcie drugiego pliku

  file2 = open(str1,O_CREAT | O_WRONLY,777);
  if (file2 < 0)
  {
    perror("open second file");
    return 1;
  }

  //petla zapisujaca do drugiego pliku
  read(file1,buf,sizeof(buf));
  printf("%s\n", buf);
  char temp;
  for(int i = 0; i < sizeof(buf); i+=3)
  {
    printf("%c",buf[i]);
    temp = buf[i];
    write(file2,&temp,sizeof(temp));
  }


//zamknięcie plików
  close(file1);
  close(file2);

printf("Done!\n");

  return 0;
}
