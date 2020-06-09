 /*
 Program tworzy nowy katalog o nazwie results. W folderze utwórz dwa pliki: - pierwszy o nazwie etc_dir.out,
 który będzie zawierał wszystkie nazwy katalogów (i tylko katalogów, bez innych rodzajów plików)
 z katalogu /etc. - w drugim pliku o nazwie sysconfig.out
 powinny znajdować się wszystkie nazwy plików regularnych,
 które nie mają nadanych żadnych uprawnień dla innych (przykład: -rwxr-x---) w katalogu /etc/sysconfig/.
 */

#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  char dirName[] = "results";
  char dirEtcPatch[] = "/etc";
  char dirEtcPatchSysconfig[] = "/etc/sysconfig";
  char file1Name[] = "results/etc_dir.out";
  char file2Name[] = "results/sysconfig.out";
  char buf[128];
  char patchname[128] = "";

  int dird;
  int fd1;
  int fd2;

  DIR *dirEtc;
  struct dirent *pDirEtc;

  DIR *dirEtcSysconfig;
  struct dirent *pDirEtcSysconfig;
  struct stat file_stat;
  if(dird = mkdir(dirName, 0777)  != 0 && errno != EEXIST)
  {
    perror("mkdir");
    return 1;
  }

  if((dirEtc = opendir(dirEtcPatch)) == NULL)
  {
    perror("openDir: ");
    return 1;
  }
  fd1 = open(file1Name, O_CREAT|O_WRONLY, 0777);
  if (fd1 < 0)
  {
    perror("open file");
    return 1;
  }

  while ((pDirEtc = readdir(dirEtc)) != NULL)
  {
    if(pDirEtc->d_type == DT_DIR)
    {
    sprintf(buf, "%s\n", pDirEtc->d_name);
      if(write(fd1,buf,strlen(buf)) < 0 )
      {
        perror("write");
        return 1;
      }
    }
  }
  closedir (dirEtc);
  close(fd1);


  if((dirEtcSysconfig = opendir(dirEtcPatchSysconfig)) == NULL)
  {
    perror("openDir: ");
    return 1;
  }
  fd2 = open(file2Name, O_CREAT|O_WRONLY, 0777);
  if (fd2 < 0)
  {
    perror("open file");
    return 1;
  }

  while ((pDirEtcSysconfig = readdir(dirEtcSysconfig)) != NULL)
  {
    sprintf(patchname, "%s", "/etc/sysconfig/");
    strcat(patchname, pDirEtcSysconfig->d_name);
    if(pDirEtcSysconfig->d_type == DT_REG && !(file_stat.st_mode & S_IRWXO))
    {
    sprintf(buf, "%s\n", pDirEtcSysconfig->d_name);
      if(write(fd2,buf,strlen(buf)) < 0 )
      {
        perror("write");
        return 1;
      }
    }
  }
  closedir (dirEtcSysconfig);
  close(fd2);


return 0;
}
