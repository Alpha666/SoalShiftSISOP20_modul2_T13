# SoalShiftSISOP20_modul2_T13

## Soal 1

Code : 

```
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
```
## Penjelasan Code

Untuk soal nomer 1 saya mengambil template yang ada pada modul 2 yaitu template daemon yang disediakan oleh asisten pada saat tatap muka asistensi komunal. Yang dirubah dari codingan nya adalah bagaimana caranya agar ```int main``` bisa menerima argumen. Cara yang saya gunakan adalah menggunakan ```int main (int argc, char *argv[])``` dimana ```argc``` adalah argumen counter dimana dia akan menghitung argumen yang diterima sedangkan argv adalah untuk menerima argumen yang ada dan menyimpan dalam array.

```
  time_t inivariabelwaktu = time(NULL);
  struct tm coba_coba = *localtime(&inivariabelwaktu);
  int detik,menit,jam;
```

Disini saya declare terlebih dahulu time nya untuk mengambil waktu sekarang pada virtual machine dan juga declare variabel untuk menyimpan detik, menit dan juga jam.

Karena pada soal 1 diminta argumen yang dimasukkan ada 4 meliputi detik, menit, jam dan juga file bash yang akan di eksekusi dan akan menampilkan error jika argumen yang diberikan tidak benar maka saya menggunakan code 

```
if (argc != 5) {
    printf("Argumen anda salah !");
  }
```
Pada program di atas adalah melakukan pengecekan apakah ```argc``` tidak sama dengan 5 karena argumen yang di isi adalah 4 buah argumen maka ditulis disini berupa 5 karena argumen nya mulai dari argumen 0.


```
  int inivariabelstrcmpdetik = strcmp(argv[1],"*");
  int inivariabelstrcmpmenit = strcmp(argv[2],"*");
  int inivariabelstrcmpjam = strcmp(argv[3],"*");
```

Disini saya melakukan compare terhadap argumen yang dimasukkan oleh pengguna menggunakan ```strcmp``` apakah argumen yang dimasukkan sama dengan ```*``` dan jika tidak maka akan me-return ```False``` dan jika sama dengan ```*``` maka akan me-return ```True```


```
while (1) {
    inivariabelwaktu = time(NULL);
    struct tm coba_coba = *localtime(&inivariabelwaktu);
    if ((coba_coba.tm_hour == atoi(argv[3]) ||      inivariabelstrcmpjam == 0)&&(coba_coba.tm_min = atoi(argv[2]) || inivariabelstrcmpmenit == 0)&&(coba_coba.tm_sec == atoi(argv[1]) || inivariabelstrcmpdetik == 0)) {
      if (fork() == 0) {
      char *bashv[] = {"bash",argv[4],NULL};
      execv("/bin/bash", bashv);
    }
  }
  }
```
Pada code di atas program akan melakukan pengecekan apakah pengecekan yang kita lakukan sebelumnya ```True``` atau ```False``` dan kita menggunakan logic OR karena ketika user menginputkan angka maka akan langsung kita rubah menggunakan atoi dari string menjadi integer atau jika input tidak sama dengan ```*``` Jika memenuhi kondisi maka akan melakukan ```Fork``` dimana isi dari ```Fork``` tersebut adalah kita menjalankan bash yang ada pada ```/bin/bash``` dengan script yang diinputkan oleh user.

## Soal 2

Untuk soal 2 saya masih belum sempat mencoba karena waktunya untuk mengerjakan kurang dan juga bobot soal nomer 2 lumayan rumit sehingga saya memutuskan untuk fokus ke soal 1 dan juga soal 3. Soal nomer 2 akan saya kerjakan pada saat revisi.


## Soal 3

Code : 

```
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
```

Secara sederhana program akan melakukan pengecekan terhadap direktori pada virtual machine apakah ada file bernama ```sedaap``` dan juga ```indomie``` dan jika tidak aka maka akan melakukan extract file ```jpg.zip``` dimana isi dari ```jpg.zip``` adalah file gambar, text dan juga direktori atau yang biasa kita kenal dengan sebutan folder.

```
int buatstatus(const char *lokasifile){
  struct stat pathDir;
  stat(lokasifile,&pathDir);
  return S_ISDIR(pathDir.st_mode);
}
```
Disini kita declare terlebih dahulu fungsi untuk melakukan pengecekan apakah file tersebut berupa directory atau bukan dan jika merupakan directory akan mereturn ```non-zero```

```
if (pidbuatb > 0 && pidbuatc >0) {
    while ((wait(&status)) > 0);
    DIR *buka;
    struct dirent *directory;
    chdir("/home/andrew/modul2/jpg");
    buka = opendir(".");
```
Pada program ini kita merubah directori kita ke ```/home/andrew/modul2/jpg```

```
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
```
Setelah itu maka jika directory ```.``` atau ```..``` ada maka program akan lanjut dan jika tidak maka program akan memindah folder ke dalam folder ```indomie```
```
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
```
Dan jika setelah memindah folder ke dalam folder ```indomie``` maka akan membuat file ```coba1.txt``` ke dalam tiap-tiap folder lalu program akan ```sleep``` selama 3 detik dan akan melanjutkan membuat file ```coba2.txt``` .
```
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
```
Setelah itu, file yang tersisa akan langsung di pindahkan ke folder ```sedaap``` dimana isinya adalah file text dan juga gambar.

