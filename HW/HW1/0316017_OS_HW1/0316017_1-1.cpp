#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
 pid_t pid;
 /*fork another porcess*/
 int i;
 printf("Main process ID : %d\n\n",getpid());
 for(i=1;i<=3;i++)
 {
     pid = fork();
     if(pid<0) /*error occurred*/
     {
      fprintf(stderr, "Fork Failed");
      exit(-1);
     }
     else if(pid==0)//child
     {
         printf("fork %d. I'm the child %d, my parent is %d.\n",i,getpid(),getppid());
     }
     else//parent
     {
         wait(NULL);
             printf("fork %d.I'm the parent %d, my child is %d.\n",i,getpid(),pid);
     }

 }
 return 0;
}



