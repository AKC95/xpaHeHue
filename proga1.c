#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc,char *argv[])
{
  pid_t pid;
  pid = fork();

  if( pid )
  {
    pid_t fatherpid = getpid();
    pid_t sonpid = pid;

    printf("Родительский процесс\n");
    sleep(3);
    printf("fatherpid=%d\nsonpid=%d\n", fatherpid, sonpid);
    sleep(3);

    char filename[30];
    sprintf(filename, "file_%d.txt", fatherpid);
    FILE *mf = fopen(filename, "wt");

    char file1[100];
    sprintf(file1, "fatherpid=%d\nsonpid=%d\n", fatherpid, sonpid);
    fputs(file1, mf);
    fclose(mf);
    wait();
  }
  else
  {
    pid_t sonpid = getpid();
    pid_t fatherppid = getppid();

    sleep(5);
    printf("Дочерний процесс\n");
    sleep(3);
    printf("fatherpid=%d\n", fatherppid);
    sleep(3);
    printf("Файлы созданы\n");
    sleep(1);
    printf("Выход\n");
    sleep(1);

    char filename2[30];
    sprintf(filename2, "file_%d.txt", sonpid);
    FILE *mf2 = fopen(filename2, "wt");

    char file2[100];
    sprintf(file2, "fatherpid=%d\n", fatherppid);
    fputs(file2, mf2);
    fclose(mf2);
  }

}


