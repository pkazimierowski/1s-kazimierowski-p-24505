#include <stdio.h>
#include <string.h>

#define MAX 41

int main(int argc, char *argv[])
{
  FILE *wp; //tworzymy wskaźnik pliku
  char word[MAX];

  wp = fopen("slowa.txt", "a+");
  if(wp == NULL)
  {
    perror("fopen");
    return 1;
  }

  fputs("Provide words to add the to a file", stdout);
  fputs("To end enter: #", stdout);

  while((fscanf(stdin, "%40s", word) == 1) && (word[0] != '#') )
  {

    fprintf(wp, "%s", word);
    fprintf(wp, "%s", " ");

  }
  puts("DONE!");
  rewind(wp);

  while(fscanf(wp, "%s\n", word) == 1)
  {

    printf("%s", word);


  }

  if(fclose(wp) != 0)
  {
    perror("fclose");
  }
  return 0;
}

