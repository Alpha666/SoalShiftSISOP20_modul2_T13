#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>

int main (int argc, char *argv[]){

  time_t inivariabelwaktu = time(NULL);
  struct tm coba_coba = *localtime(&inivariabelwaktu);
  int detik,menit,jam;

  if (argc != 5) {
    printf("Argumen anda salah !");
  }

  int inivariabelstrcmpdetik = strcmp(argv[1],"*");
  int inivariabelstrcmpmenit = strcmp(argv[2],"*");
  int inivariabelstrcmpjam = strcmp(argv[3],"*");

  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDOUT_FILENO);
  close(STDIN_FILENO);
  close(STDERR_FILENO);

  while (1) {
    inivariabelwaktu = time(NULL);
    struct tm coba_coba = *localtime(&inivariabelwaktu);
    if ((coba_coba.tm_hour == atoi(argv[3]) || inivariabelstrcmpjam == 0)&&(coba_coba.tm_min = atoi(argv[2]) || inivariabelstrcmpmenit == 0)&&(coba_coba.tm_sec == atoi(argv[1]) || inivariabelstrcmpdetik == 0)) {
      if (fork() == 0) {
      char *bashv[] = {"bash",argv[4],NULL};
      execv("/bin/bash", bashv);
    }
  }
  }
}
