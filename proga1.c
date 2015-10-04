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

    char filename2[30];
    sprintf(filename2, "file_%d.txt", sonpid);
    FILE *mf2 = fopen(filename2, "wt");

    char file2[100];
    sprintf(file2, "fatherpid=%d\n", fatherppid);
    fputs(file2, mf2);
    fclose(mf2);
  }

}


