#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char* argv[])
{
 uid_t r_uid = getuid();
 uid_t e_uid = geteuid();

  printf("real: %d\neffective: %d\n", r_uid, e_uid);

  FILE* f = fopen("/home/students/20200/e.vartazaryan/Lab3/file","r");
  if(f == NULL)
  {
    perror("Couldn't open file:");
  }
  else
  {
    printf("I can open file !\n");
    fclose(f);
  }

  printf("Changing uid...\n");
  setuid(r_uid);

  r_uid = getuid();
  e_uid = geteuid();

  printf("real: %d\neffective: %d\n", getuid(), geteuid());

  FILE* n = fopen("/home/students/20200/e.vartazaryan/Lab3/file", "r");

  if(n == NULL)
  {
    perror("Couldn't open file:");
  }
  else
  {
    printf("I can open file !\n");
    fclose(n);
  }

return 0;
