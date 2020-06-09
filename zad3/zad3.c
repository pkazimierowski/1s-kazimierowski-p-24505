
#include <stdio.h>
#include <string.h>

/* ----- Użyte funkcje

printf() - strumień wyjściowy do okna konsoli
scanf() - pobieranie od użytkownika danych
strcat() - funkcja od biblioteki string.h do łączenia ciągów znaków
perror() - wypisanie zrozumiałego komunikatu o błędzie
fopen() - otwarcie pliku
fputc() - pobieranie znaku z otwartego pliku
fgetc() - zapis znaku do pliku
fclose() - zamknięcie pliku


*/
int main(int argc, char *argv[])
{

  FILE *wp;
  FILE *wp2;
  int ch;
  char nazwa[80];
  unsigned long counter = 1;
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
  if ((wp = fopen(nazwa, "r")) == NULL)
  {
    perror("fopen");
    return 1;
  }

  //otwarcie drugiego pliku
  wp2 = fopen(str1, "w");

  if(wp2 == NULL)
  {
    perror("fopen");
    return 1;
  }

  //petla zapisujaca do drugiego pliku
  while((ch = fgetc(wp)) != EOF)
  {
    if((counter % 3) == 0)
      {
        fputc(ch, wp2);
      }
    counter++;
  }

//zamknięcie plików
  fclose(wp);
  fclose(wp2);

printf("Done!\n");

  return 0;
}
