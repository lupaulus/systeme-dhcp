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
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

#define STDOUT 1
#define STDERR 2

#define MAX_PATH_LENGTH 4096

typedef struct arg_struct
{
   int* tab;
   int size;
} arg_struct;





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
 * @param tab 
 * @param size 
 */
void fillTab(int* tab, int size)
{
  for (int i=0; i<size;i++)
  {
    tab[i] =  rand();
  }
}

void* findMin(void* args)
{
  arg_struct *args1 = (arg_struct *)args;

  int* tab = args1->tab; 
  int size =  args1->size;

  long res = 0;
  if(size <= 0)
  {
    return (void*) res;
  }

  long value = tab[res];
  for(long i = 1;i<size;i++)
  {
    if(value>tab[i])
    {
      res = i;
      value = tab[i];
    }
  }
  return (void*) res;
}


void* findMax(void *args)
{
  arg_struct *args1 = (arg_struct *)args;

  int* tab = args1->tab; 
  int size =  args1->size;

  long res = 0;

  if(size <= 0)
  {
    return (void*) res;
  }
  
  long value = tab[res];
  for(long i = 1;i<size;i++)
  {
    if(value<tab[i])
    {
      res = i;
      value = tab[i];
    }
  }
  return (void*) res;
}

// int findMax(int* tab, int SIZE)
// {
//   if(SIZE <= 0)
//   {
//     return -1;
//   }
//   int res = 0;
//   int value = tab[res];
//   for(int i = 1;i<SIZE;i++)
//   {
//     if(value<tab[i])
//     {
//       res = i;
//       value = tab[i];
//     }
//   }
//   return res;
// }

double getDeltaTime(struct timeval* tStart)
{
  struct timeval* actual = malloc(sizeof(struct timeval));
  gettimeofday(actual, NULL);
  // Différence entre temps début et fin

  // Transformation en nbr à virgule
  double res = (actual->tv_sec - tStart->tv_sec) * 1000000 + (actual->tv_usec - tStart->tv_usec);
  
  return res/1000000;
}




#define SIZE (int)1e8

/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{

  srand(time(NULL));
  int* tab = malloc(sizeof(int)* SIZE);
  fillTab(tab,SIZE);
  struct timeval* tvStartMin = malloc(sizeof(struct timeval));
  struct timeval* tvStartMax = malloc(sizeof(struct timeval));


  

  pthread_t* threadMax= malloc(sizeof(pthread_t));
  pthread_t* threadMin= malloc(sizeof(pthread_t));
  arg_struct* args = malloc(sizeof(arg_struct));
  args->tab = tab;
  args->size = SIZE;

  void* indexPosMax;
  void* indexPosMin;

  // Max
  gettimeofday(tvStartMax, NULL);
  pthread_create(threadMax,NULL,findMax,args);
  
  // Min
  gettimeofday(tvStartMin, NULL);
  pthread_create(threadMin,NULL,findMin,args);
  
  pthread_join(*threadMax,&indexPosMax);
  double timeMax = getDeltaTime(tvStartMax);
  
  pthread_join(*threadMin,&indexPosMin);
  double timeMin = getDeltaTime(tvStartMin);


  printf("Le maximun trouvé en %lf sec (pos %ld)\n",timeMax, (long)indexPosMax);
  printf("Le minimun trouvé en %lf sec (pos %ld)\n",timeMin, (long)indexPosMin);

  return EXIT_SUCCESS;
}
