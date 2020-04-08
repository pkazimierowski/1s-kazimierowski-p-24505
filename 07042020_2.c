#include <stdio.h>

int main(int argc, char *argv[])
{

  FILE *wp;
  int ch;
  unsigned long counter = 0;

  if(argc != 2)
  {
    printf("provide file Name!\n");
    return 1;
  }

  if ((wp = fopen(argv[1], "r")) == NULL)
  {
    perror("fopen");
    return 2;
  }

  while(  (ch = fgetc(wp)) != EOF )
  {
    fputc(ch, stdout);
    counter++;
  }

  fclose(wp);
  printf("\nWynik to: %lu \n", counter);

  return 0;
}

