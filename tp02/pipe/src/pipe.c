/**
 * \file skeleton.c
 * \brief Basic parsing options skeleton.
 * \author Pierre L. <pierre1.leroy@orange.com>
 * \version 0.1
 * \date 10 septembre 2016
 *
 * Basic parsing options skeleton exemple c file.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>





#define STDOUT 1
#define STDERR 2

#define MAX_PATH_LENGTH 4096




/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
dprintf(1, "USAGE: %s\n\n", bin_name);
}





/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{


  int f;
  if(!(f = fork()))
  {
    
    printf("PID DU FILS %d\n",getpid());
    int oldout = dup(1);
    close(1);
    int descrip = mkstemp("/tmp/proc-exercise");
    dprintf(oldout,"Descriptor : %d\n", descrip);
    execl("/home/user/CNAM/FIP2/SysAvance/pipe1/bin/pipe1","test");
    
  }
  else
  {
    printf("PID DU PERE %d\n",getpid());
    wait(NULL);
    printf("That’s All Folks!\n");
  }

  return EXIT_SUCCESS;
}
