#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <libgen.h>



#define FG 1    /* running in foreground */
#define BG 2    /* running in background */
#define ST 3    /* stopped */

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define DARY_GRAY "\033[1;30m"
#define RESET "\033[0m"
#define MAXPRC 2
using namespace std;
/* The array below will hold the arguments: args[0] is the command. */
static char* args[512];     //string array to store command
char UserName[64] ;         // used to print
char root_of_my[64];        //used to print

char shellPath[10000];

pid_t pid;
pid_t main_pid; /*********child id*****正在執行*********/
//pit_t main_parent_pid;  /*******parent id ****************/
int command_pipe[2];    //PIPE ARRAY

                           /**control c control v*/
void sigtstp_handler(int sig);
void sigint_handler(int sig);
void sigint_handler(int sig)
{       sig = pid;
    //	int jid = pid2jid(pid);
	// send fg job/ related process group signal
	    if (sig != 0) {
		kill(-sig, SIGINT);
		/*if (sig < 0){
			printf("Job [%d] (%d) terminated by signal %d\n", jid, pid, (-sig));
			deletejob(jobs, pid);
		}*/
	}
	return;
}
void sigtstp_handler(int sig)
{
	   sig = main_pid;
	   int this_pgid = getpgid(0);
	//int jid = pid2jid(pid);

	// send fg job/ related process group signal
	   if (sig != 0) {

	//	printf("Job [%d] (%d) Stopped by signal %d\n", jid, pid, sig);
	//	getjobpid(jobs, pid)->state = ST;
	  //  tcsetpgrp(STDIN_FILENO,this_pgid) == -1
		kill(-sig, SIGTSTP);
	}
 	return;
}
                            /**control c control v*/
/*
void sigtstp_handler(int sig)
{
    pid_t pid = main_pid;
    if (pid) {
        kill(-pid, sig);
    }
    return;
}*/













int back_ground;       /*********背景旗標 初始化為0******遇到　&　變成一　再回來０******/




bool bg;  	           // background flag
bool fg;	           // foregrund flag

pid_t fg_pid;	       // process id of foreground process
pid_t bg_pid;          // process id of background process

//pid_t main_pid; /*********child id*****正在執行*********/
//pit_t main_parent_pid;  /*******parent id ****************/
pid_t shell_pid;       // process id of the shell running this program

pid_t bproc[MAXPRC];   /*********需要一個背景 的陣列 用來存 background id  ************/

sig_atomic_t sig_flag = 0;
#define READ  0
#define WRITE 1

/*
 * Handle commands separatly
 * input: return value from previous command (useful for pipe file descriptor)
 * first: 1 if first command in pipe-sequence (no input from previous pipe)
 * last: 1 if last command in pipe-sequence (no input from previous pipe)
 *
 * EXAMPLE: If you type "ls | grep shell | wc" in your shell:
 *    fd1 = command(0, 1, 0), with args[0] = "ls"
 *    fd2 = command(fd1, 0, 0), with args[0] = "grep" and args[1] = "shell"
 *    fd3 = command(fd2, 0, 1), with args[0] = "wc"
 *
 * So if 'command' returns a file descriptor, the next 'command' has this
 * descriptor as its 'input'.
 */









  int mysh_fg(pid_t pid) {
     /* Implement fg command */

 }

 int mysh_bg(pid_t bpid) {
     /* Implement bg command */
   bool placed = false;
   int i;
   for(i = 0; i < MAXPRC; i++)
   {
      if(bproc[i] == 0)
      {
         bproc[i] = bpid;
         placed = true;
         break;
      }
   }
   return placed;
 }


/**************************B G******************/
int cmd_bg(int pgid){
     kill(pgid,SIGCONT);
     return 0;
 }







 bool rm_bg(pid_t bpid)
{
   bool removed = false;
   int i;

   for(i = 0; i < MAXPRC; i++)
   {
      if(bproc[i] == bpid)
      {
         bproc[i] = 0;
         removed = true;
         break;
      }
   }

   return removed;
}




 void my_kill(int target)
{
    kill(target, SIGKILL);
}


 /*void kill_all()
{
   int ret;
   int i;


   for(i = 0; i < MAXPRC; i++)
   {
      if(bproc[i] != 0)
      {
         ret = kill(bproc[i], SIGKILL);
         if(ret != 0)  // if kill failed, print out error message
         {
            printf("Kill Failed for PID: %d\n", bproc[i]);
         }
         else  // else set the background pid array element to zero
         {
            printf("Process with PID: %d killed\n", bproc[i]);
            bproc[i] = 0;
         }
      }
   }
}*/



   /*void print_bg_msg(int status, pid_t back_pid)
{
   printf("\nBackground process finished with PID: %d\n", back_pid);

   if(WIFEXITED(status))
      printf("Background Process exited normally with exit code: %d\n", WEXITSTATUS(status));
   else if(WIFSIGNALED(status))
      printf("Background Process terminated by signal: %d\n", WTERMSIG(status));
   else if(WIFSTOPPED(status))
      printf("Background Process stopped by signal: %d\n", WSTOPSIG(status));
   else
      printf("Status or exit code could not be interpreted\n");
}*/


/*void update_status()
{
   int i;
   int status;

   for(i = 0; i < MAXPRC; i++)
   {
      if(bproc[i] != 0)
      {
         if(waitpid(bproc[i], &status, WNOHANG) == bproc[i])
         {
            // we must sleep before printing out any messages so
            // that they don't interfere with current output
            sleep(1);
            print_bg_msg(status, bproc[i]);
            rm_bg(bproc[i]);
         }
      }
   }
}*/



void    shell_forground(int signum){
     signal(SIGTSTP,SIG_IGN);
     pid_t fg_pid = tcgetpgrp(0);//
     int this_pgid =  getpgid(0);
     //set parent to foreground
     if(tcsetpgrp(STDIN_FILENO,this_pgid) == -1){
         cerr << "tcsetpgrp error" <<endl;
         cerr << strerror(errno) <<endl;
     }
      if(tcsetpgrp(0,main_pid)==-1)
    {
        cerr << strerror(errno) << endl;
    }

    fflush(stdout);


    signal(SIGTSTP, shell_forground);
    return;
 }




void deal_with_zombie(int signum){
     //cout << "SIGCHILD handling" <<endl;
     int status = 0;
      signum = waitpid(-1,&status,WNOHANG);
   /*  if(signum == -1 ){
         cout << "error occures when dealing with zombie" <<endl;
         cout << strerror(errno) <<endl;
         return ;
     }*/
     if(signum == 0)
         return;
     args[0]=NULL;
     return;
 }













static int command(int input, int first, int last)
{
	/********Invoke pipe ********/
	     int pipettes[2];
	     pipe( pipettes );
	     pid = fork();
	     main_pid=getpid();

      //   main_parent_pid=getpgid();

     //   signal(SIGINT,  &sigint_handler);   /* ctrl-c */
     //   signal(SIGTSTP, &sigtstp_handler);
              /* ctrl-z */
      //   signal(SIGCHLD,&deal_with_zombie);
      //   signal(SIGTTIN,SIG_IGN);
     //    signal(SIGTTOU,SIG_IGN);
	/*

	 SCHEME:
	 	STDIN --> O --> O --> O --> STDOUT
	*/

	     if (pid == 0) {



          if(back_ground == 1)
       {   cout<<KGRN <<"command excuded by "<<main_pid<<"  in background "<<RESET<<endl;

           return 1;
       }
	     if( !strcmp(args[0],"cd") && args[1]!= NULL )                /********判斷 cd 指令**********/
                 {int cd=chdir(args[1]);
                  if(cd==-1)
                  cout<<args[1]<< "  Not such File in this path"<<endl;
                  }

         /***************BG*************/
         if( !strcmp(args[0],"bg"  ))
           {
                if( args[1]!=NULL){
                int pgid = atoi(args[1]);
                cout<<  pgid  <<endl;
                cmd_bg(pgid);
                }
           }
        /****************kill*****************/
         if( !strcmp(args[0],"kill"  ))
         {
             int val=atoi(args[1]);
             cout<<val<<endl;
             my_kill(val);

         }
         /***********print child id ********/


         cout<<KGRN <<"comman excude by pid   "<<main_pid<<RESET<<endl;

        /*********進入ＰＩＰＥ******/

		if (first == 1 && last == 0 && input == 0) {
			// First command
			dup2( pipettes[WRITE], STDOUT_FILENO );
		} else if (first == 0 && last == 0 && input != 0) {
			// Middle command
			dup2(input, STDIN_FILENO);
			dup2(pipettes[WRITE], STDOUT_FILENO);
		} else {
			// Last command
			dup2( input, STDIN_FILENO );
		}

		if (execvp( args[0], args) == -1)
            {
			_exit(EXIT_FAILURE);}
		else
		{int status;
       //  signal(SIGINT, sigChild);
        signal(SIGTSTP, &sigtstp_handler);
		 waitpid(main_pid, &status, 0);
		}
            // If child fails
	}
    else{   /****************PARARENT*************/


        //     signal(SIGINT,  sigint_handler);   /* ctrl-c */
	    //     signal(SIGTSTP, sigtstp_handler);  /* ctrl-z */




                 /*********暫時不用不確定******/

                                          // parent pid
           if( !strcmp(args[0],"cd") && args[1] !=NULL)                //判斷 cd 指令/////////////
                 { int cd=chdir(args[1]);
                 // if(cd==-1)
                  //cout<<args[1]<< "  Not such File in this path"<<endl;
                  }
             }




	if (input != 0)
		close(input);

	// Nothing more needs to be written
	close(pipettes[WRITE]);

	// If it's the last command, nothing more needs to be read
	if (last == 1)
    close(pipettes[READ]);

	return pipettes[READ];
}

/* Final cleanup, 'wait' for processes to terminate.
 *  n : Number of times 'command' was invoked.
 */
static void cleanup(int n)
{
	int i;
	for (i = 0; i < n; ++i)
		wait(NULL);
}

static int run(char* cmd, int input, int first, int last);



static char line[1024];
static int n = 0; /* number of calls to 'command' */


/*void make_shell_forground(int signum){
     cout << "what are you doing" <<endl;
     int this_pgid =  getpgid(0);
     //set parent to foreground
     if(tcsetpgrp(STDIN_FILENO,this_pgid) == -1){
         cerr << "tcsetpgrp error" <<endl;
         cerr << strerror(errno) <<endl;
     }
     return;
 }*/







int main()
{

	     cout<<"Welcome to my shell 0316327"<<endl;
         cout<<KRED<<"============BEGIN==============" <<RESET<<endl;
        // cout<<KRED<<"  BEFORE '|' need a  space    " <<RESET<<endl;
	     while (1) {
            back_ground=0;   /*************   AS FLAG   ******************/
		/* Print the command prompt */
		    getlogin_r(UserName, sizeof(UserName)-1); // user path 0316327
            getcwd(root_of_my,sizeof(root_of_my)-1);  // myname jeremyeu 0316327
            cout<<KCYN<<UserName<<RESET<<" in " << KYEL << root_of_my << RESET << endl;

		/* Print the command prompt */
		    cout<<DARY_GRAY<<"mysh > "<<RESET;

		    signal(SIGINT,  &sigint_handler);   /* ctrl-c */
    	    signal(SIGTSTP, &shell_forground);  /* ctrl-z */
            signal(SIGCHLD, &deal_with_zombie);
            signal(SIGTTIN,SIG_IGN);
            signal(SIGTTOU,SIG_IGN);



		 fflush(NULL);

		/* Read a command line */
		if (!fgets(line, 1024, stdin))
			return 0;
		int input = 0;
		int first = 1;
		char* cmd = line;
		char* next = strchr(cmd, '|'); /* Find first '|' */
		while (next != NULL) {
			/* 'next' points to '|' */
			 *next = '\0';
			 input = run(cmd, input, first, 0);
			 cmd = next + 1;
			 next = strchr(cmd, '|'); /* Find next '|' */
			 first = 0;
		}
		input = run(cmd, input, first, 1);
		if(!input  &&   ! signal(SIGINT,  sigint_handler))cout<<"command not found"<<endl;
		cleanup(n);
		n = 0;
	}
	return 0;
}














static void split(char* cmd);

static int run(char* cmd, int input, int first, int last)     //need split skipwhite
{
	   split(cmd);


	        if (args[0] != NULL) {

		    if (strcmp(args[0], "exit") == 0)
			{cout<<"GoodBye"<<endl;
             cout<<KRED<<"==============end================" <<RESET<<endl;
         //     free(args);
			 exit(0);
            }
/************************/
        if(args[0][strlen(args[0])-1]=='&')  //|| !strcmp(args[1], "&")  )
       {back_ground=1;
      //  args[0][strlen(args[0])-1]='\0';
       }
         else if (args[1] != NULL) {
           if(!strcmp(args[1], "&") )
                {back_ground=1;
                 args[1]=NULL;
                }
                                  }
          if (args[2] != NULL) {
           if(!strcmp(args[2], "&") )
                {back_ground=1;
                 args[2]=NULL;
                }
                                  }
  /*****************************/



/*    if(run_in_background) {
      switch(fork()) {
                    case -1:
						error("fork error");
						break;
					case 0: 				// execution in child process
						setenv("PARENT", shellPath, 1);
						runCommand();
						exit(0);			// quit the child process
						break;
				}
                                }*/
		    n += 1;
		return command(input, first, last);
	}
	return 0;
}

static char* skipwhite(char* s)
{
	while (isspace(*s)) ++s;
	return s;
}

static void split(char* cmd)
{
	cmd = skipwhite(cmd);
	char* next = strchr(cmd, ' ');
	int i = 0;

	while(next != NULL) {
		next[0] = '\0';
		args[i] = cmd;
		++i;
		cmd = skipwhite(next + 1);
		next = strchr(cmd, ' ');
	}

	if (cmd[0] != '\0') {
		args[i] = cmd;
		next = strchr(cmd, '\n');
		next[0] = '\0';
		++i;
	}

	args[i] = NULL;
}
