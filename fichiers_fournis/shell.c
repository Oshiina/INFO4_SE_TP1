


#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "readcmd.h"



int main(){
  printf("shell> ");

  while(1){
    struct cmdline *l;
    int status;
    int i = 0;
    int n = 0;

    l = readcmd();

    if (!l) {
      printf("exit\n");
      exit(0);
    }

    if (l->err) {
      printf("error: %s\n", l->err);
      continue;
    }

    while(l->seq[n] != NULL){
      n++;
    }

    int p[n][2];

    for (int j = 0; j<n; j++){
        pipe(p[j]);
    }

    while(i < n){
      if(fork() == 0){
        if(l->in!=NULL && i==0){
          int f = open(l->in,O_RDONLY | O_CREAT, S_IRWXU);
          dup2(f,STDIN_FILENO);
          close(f);
        }
        if(l->out!=NULL && i == n-1){
          int f = open(l->out,O_WRONLY | O_CREAT, S_IRWXU);
          dup2(f,STDOUT_FILENO);
          close(f);
        }

        if (i+1 != n){
          dup2(p[i][1],STDOUT_FILENO);
        }
        if(i>0){
          dup2(p[i-1][0],STDIN_FILENO);
        }
        for (int j = 0 ; j<n; j++){
            close(p[j][0]);
            close(p[j][1]);
        }
        if (execvp(l->seq[i][0],l->seq[i]) == -1){
          printf("coucou\n");
          exit(-1);
        }
      }
      else{
        i++;
      }
    }
    for (int j = 0 ; j<n; j++){
        close(p[j][0]);
        close(p[j][1]);
      }

      for(int j=0;j<n;j++){
          wait(&status);
      }


      printf("shell> ");
  }
}
