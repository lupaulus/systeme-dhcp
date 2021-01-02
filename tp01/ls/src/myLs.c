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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h> 
#include <fcntl.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define STDOUT 1
#define STDERR 2

#define MAX_PATH_LENGTH 4096


#define USAGE_SYNTAX "[SPECIFIC PATH]"

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
  dprintf(1, "USAGE: %s %s\n", bin_name, USAGE_SYNTAX);
}


/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* to_free pointer to an allocated mem
 * \see man 3 free
 * \return void
 */




/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{
  char *curr_dir = NULL; 
  DIR *dp = NULL; 
  struct dirent *dptr = NULL; 
  unsigned int count = 0; 

  if(argc == 1) // Local ls
  {
    // Get the value of environment variable PWD 
    curr_dir = getenv("PWD");  
  }
  else if(argc == 2) // Specific LS
  {
    curr_dir = argv[1];
  }
  else // BAD PARAMS
  {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }
  

  if(NULL == curr_dir) 
    { 
        printf("\n ERROR : Could not get the working directory\n"); 
        return EXIT_FAILURE; 
    }
  

  // Open the current directory 
  dp = opendir((const char*)curr_dir); 
  if(NULL == dp) 
  { 
      printf("\n ERROR : Could not open the working directory\n"); 
      return -1; 
  } 

  printf("%-30s %-15s %-15s %-15s %15s %-15s\n","Filename","Permissions",
  "Owner","Group","Size","Last Update");
  // Go through and display all the names (files or folders) 
  // Contained in the directory. 
  for(count = 0; NULL != (dptr = readdir(dp)); count++) 
  { 
      // STAT
      struct stat statInfo;
      if (stat(dptr->d_name, &statInfo) == -1)
      {
          perror(strerror(errno));
          continue;
      }
      
      // Set structs usefull for obtaining data reguarding the current file
      struct passwd *pwd_s;
      if ((pwd_s = getpwuid(statInfo.st_uid)) == NULL)
      {
          perror(strerror(errno));
          continue;
      };
      struct group *grp_s;
      if ((grp_s = getgrgid(statInfo.st_gid)) == NULL) 
      {
          perror(strerror(errno));
          continue;
      }
      struct tm *time_s;
      if ((time_s = localtime(&statInfo.st_mtim)) == NULL) 
      {
          perror(strerror(errno));
          continue;
      };

      // Print informations
      printf("%-30s %-1s%-1s%-1s%-1s%-1s%-1s%-1s%-1s%-1s%-6s %-15s %-15s %15ld %02d/%02d/%04d %02d:%02d:%02d\n", 
      dptr->d_name,
      (S_ISDIR(statInfo.st_mode)) ? "d" : "-",
      (statInfo.st_mode & S_IRUSR) ? "r" : "-",
      (statInfo.st_mode & S_IWUSR) ? "w" : "-",
      (statInfo.st_mode & S_IXUSR) ? "x" : "-",
      (statInfo.st_mode & S_IRGRP) ? "r" : "-",
      (statInfo.st_mode & S_IWGRP) ? "w" : "-",
      (statInfo.st_mode & S_IXGRP) ? "x" : "-",
      (statInfo.st_mode & S_IROTH) ? "r" : "-",
      (statInfo.st_mode & S_IWOTH) ? "w" : "-",
      (statInfo.st_mode & S_IXOTH) ? "x" : "-",
      (pwd_s->pw_name),
      (grp_s->gr_name),
      (statInfo.st_size),
      time_s->tm_mday,
      time_s->tm_mon + 1,
      time_s->tm_year + 1900,
      time_s->tm_hour,
      time_s->tm_min,
      time_s->tm_sec
      ); 
  } 

  return EXIT_SUCCESS;
}
