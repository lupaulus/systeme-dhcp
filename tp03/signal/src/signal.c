/**
 * \file skeleton.c
 * \brief Basic parsing options skeleton.
 * \author Pierre L. <pierre1.leroy@orange.com>
 * \version 0.1
 * \date 10 septembre 2016
 *
 * Basic parsing options skeleton exemple c file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>

#define STDOUT 1
#define STDERR 2

#define MAX_PATH_LENGTH 4096

int scoreFather = 0;
int scoreSon = 0;
int pidFils;
sigset_t* sig_signal1;
sigset_t* sig_signal2;


/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
dprintf(1, "USAGE: %s\n", bin_name);
}

/**
 * @brief 
 * 
 * @param signum 
 */
void handlerPlayerFather(int signum)
{
  if (signum == SIGUSR1)
  { 

    printf("Received Father SIGUSR1!\n");
    if((rand() % 3) < 2)
    {
      kill(pidFils,SIGUSR1);
    }
    else
    {
      kill(pidFils,SIGUSR2);
    }
    sigsuspend(sig_signal2);
  }
  else if(signum == SIGUSR2)
  {
    scoreFather++;
    printf("Received Father SIGUSR2! Score +1\n");
    printf("Score Pere %d\n",scoreFather);
    if(scoreFather < 10)
    {
      kill(pidFils,SIGUSR1);
      sigsuspend(sig_signal2);
    }
  }
   
}

/**
 * @brief 
 * 
 * @param signum 
 */
void handlerPlayerSon(int signum)
{
  if (signum == SIGUSR1)
  {
    printf("Received Son SIGUSR1!\n");
    if((rand() % 6) < 2)
    {
      kill(getppid(),SIGUSR1);
    }
    else
    {
      kill(getppid(),SIGUSR2);
    }
    sigsuspend(sig_signal1);
  }
  else if(signum == SIGUSR2)
  {
    scoreSon++;
    printf("Received Son SIGUSR2! Score +1\n");
    printf("Score Fils %d\n",scoreSon);
    if(scoreSon < 10)
    {
      kill(getppid(),SIGUSR1);
      sigsuspend(sig_signal1);
    }
  }
}

struct sigaction* createSigStruct(sigset_t* sigset)
{
    struct sigaction* sig2 = malloc(sizeof(struct sigaction));
    sig2->sa_mask=*sigset;
    sig2->sa_flags=0;
    return sig2;
}


/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{
  srand(time(NULL));
  if((pidFils = fork()) == 0)
  {
    //fils
    sig_signal1 = malloc(sizeof(sigset_t));
    sigemptyset(sig_signal1);

    struct sigaction* sig1 = createSigStruct(sig_signal1);
    sig1->sa_handler = handlerPlayerSon;
    
    // Emettre le signal
    kill(getppid(),SIGUSR1);

    sigaction(SIGUSR1,sig1,0);
    sigaction(SIGUSR2,sig1,0);
    sigsuspend(sig_signal1);
    
  }
  // pere
  else
  {

    sig_signal2 = malloc(sizeof(sigset_t));
    sigemptyset(sig_signal2);
    struct sigaction* sig2 = createSigStruct(sig_signal2);
    sig2->sa_handler = handlerPlayerFather;
    
    
    
    sigaction(SIGUSR1,sig2,0);
    sigaction(SIGUSR2,sig2,0);
    sigsuspend(sig_signal2);
  
  }
  

  return EXIT_SUCCESS;
}
