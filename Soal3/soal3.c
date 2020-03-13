#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <wait.h>


int buatstatus(const char *lokasifile){
  struct stat pathDir;
  stat(lokasifile,&pathDir);
  return S_ISDIR(pathDir.st_mode);
}

int main(){
  pid_t pidbuata = fork();
  int pidbuatb = fork();
  int pidbuatc = fork();
  int status;

  if (pidbuatb > 0 && pidbuatc >0) {
    while ((wait(&status)) > 0);
    DIR *buka;
    struct dirent *directory;
    chdir("/home/andrew/modul2/jpg");
    buka = opendir(".");

    if (buka) {
      while ((directory = readdir(buka)) != NULL) {
        if (strcmp(directory->d_name,".")==0 || strcmp(directory->d_name, "..")==0)
          continue;
          if(buatstatus(directory->d_name)){
            if(fork()==0){
              char file[500];
              sprintf(file,"/home/andrew/modul2/jpg/%s",directory->d_name);
              char *pindah[] = {"mv",file, "/home/andrew/modul2/indomie/",NULL};
              execv("/bin/mv",pindah);
            }
            else {
              while ((wait(&status)) > 0);
              if(fork()==0){
                if(fork()==0){
                char coba_coba[500];
                FILE *file;;
                sprintf(coba_coba,"/home/andrew/modul2/indomie/%s/coba1.txt",directory->d_name);
                file = fopen(coba_coba,"w");
                fclose(file);
              }
              else {
                while ((wait(&status)) > 0) {
                  sleep(3);
                  char belum_berhasil[500];
                  FILE *file;
                  sprintf(belum_berhasil,"/home/andrew/modul2/indomie/%s/coba2.txt",directory->d_name);
                  file = fopen(belum_berhasil,"w");
                  fclose(file);
                  exit(0);
                }
              }
            }else {
                while ((wait(&status)) > 0);
                exit(0);
              }
          }
        }else {
            while ((wait(&status)) > 0);
            if (fork() == 0 ) {
              /* code */
              char iniberhasil[500];
              sprintf(iniberhasil,"/home/andrew/modul2/jpg/%s",directory->d_name);
              char *argumenlagi[] = {"mv",iniberhasil,"/home/andrew/modul2/sedaap/",NULL};
              execv("/bin/mv",argumenlagi);
            }
          }
      }
    }
  }
  else if (pidbuatb == 0 && pidbuatc >0){
    while((wait(&status)) > 0);
    if (pidbuata == 0 ) {
      /* code */
      char *bikin_indomie[] = {"mkdir","-p","/home/andrew/modul2/indomie",NULL};
      execv("/bin/mkdir",bikin_indomie);
    }
    else  {
      while((wait(&status)) > 0);
      sleep(5);
      char *bikin_sedaap[] = {"mkdir", "-p", "/home/andrew/modul2/sedaap",NULL};
      execv("/bin/mkdir",bikin_sedaap);
    }
  }
  else if (pidbuatb > 0 && pidbuatc == 0){
    char* buka_buka[] = {"unzip","-oq","/home/andrew/modul2/jpg.zip",NULL};
    execv("/usr/bin/unzip",buka_buka);
  }
  return 0;
}
