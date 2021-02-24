#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <fcntl.h>

using namespace std;

#define READ_END 0
#define WRITE_END 1

int main()
{
    int fd[2],fd2[2],fd3[2];
    pid_t pid;
    printf("Main process ID : %d\n\n",getpid());
    cerr<<"-------------------------------------\n";
    int i,allsum=0,parentflag=0,num;
    char temp[30];
    char temp2[30];
    char temp3[30];
    if(pipe(fd)<0)
    {
        fprintf(stderr, "Pipe1 Failed");
        return 1;
    }
    if(pipe(fd2)<0)
    {
        fprintf(stderr, "Pipe2 Failed");
        return 1;
    }
    if(pipe(fd3)<0)
    {
        fprintf(stderr, "Pipe3 Failed");
        return 1;
    }

    pid = fork();
    if(pid<0)
    {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(pid==0)
    {

        close(fd[READ_END]);
        dup2(fd[WRITE_END],STDOUT_FILENO);
        cerr<<"I'm the child "<<getpid()<<".\n";
        cerr<<"I can receive input! Please enter a number.\n\n";
        execl("caculate.out","./caculate.out",(char*)0);
    }
    else
    {
        wait(0);
        close(fd[WRITE_END]);
        read(fd[READ_END],temp,30);
        num=atoi(temp);
        cerr<<"-------------------------------------\n";
        allsum=allsum+num;
        pid=fork();
        if(pid<0)
        {
            fprintf(stderr, "Fork Failed");
            exit(-1);
        }
        else if(pid==0)
        {
            cerr<<"I'm the child "<<getpid()<<".\n";
            cerr<<"I can receive input! Please enter a number.\n\n";
            close(fd2[READ_END]);
            dup2(fd2[WRITE_END],STDOUT_FILENO);
            execl("caculate.out","./caculate.out",(char*)0);
        }
        else
        {
            wait(0);
            close(fd2[WRITE_END]);
            read(fd2[READ_END],temp2,30);
            num=atoi(temp2);
            cerr<<"-------------------------------------\n";
            allsum=allsum+num;
            pid=fork();
            if(pid<0)
            {
                fprintf(stderr, "Fork Failed");
                exit(-1);
            }
            else if(pid==0)
            {
                cerr<<"I'm the child "<<getpid()<<".\n";
                cerr<<"I can receive input! Please enter a number.\n\n";
                close(fd3[READ_END]);
                dup2(fd3[WRITE_END],STDOUT_FILENO);
                execl("caculate.out","./caculate.out",(char*)0);
            }
            else
            {
                wait(0);
                close(fd3[WRITE_END]);
                read(fd3[READ_END],temp3,30);
                num=atoi(temp3);
                cerr<<"-------------------------------------\n";
                allsum=allsum+num;
                cout<<"I'm the parent "<<getpid()<<".\n";
                cout<<"Sum of results from threechild processes : "<<allsum<<endl;
            }
        }
    }
    /*for(i=1;i<=3;i++)
    {
        parentflag=0;
         if(pipe(fd)<0)
         {
            fprintf(stderr, "Pipe Failed");
            return 1;
         }
         if(pid<0) //error occurred
         {
          fprintf(stderr, "Fork Failed");
          exit(-1);
         }
         else if(pid==0)//child
         {
             cerr<<"I'm the child "<<getpid()<<".\n";
             close(fd[READ_END]);
             dup2(fd[WRITE_END],STDOUT_FILENO);
             execl("caculate.out","./caculate.out",(char*)0);
         }
         else//parent
         {
             wait(NULL);
             close(fd[WRITE_END]);
             read(fd[READ_END],temp,1024);
             printf("read %s 2\n",temp);
             //allsum=allsum+temp;
             parentflag=1;
         }
         if(parentflag==1&&i!=3)
         {
             cout<<"HI"<<getpid()<<endl;
             pid = fork();
         }
    }*/

}


