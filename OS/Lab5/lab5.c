#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void buildFileInfo(int* offsets, int* lengths, int fileDescriptor, int* number_of_lines)
{
 int lineIndex = 0;
 int offset = 0;
 int bytesRead = 1;
 char buf[BUFSIZ];

 while(bytesRead > 0)
 {
   bytesRead = read(fileDescriptor, buf, BUFSIZ);
   if(bytesRead == -1)
   {
     perror("Can't read the file\n");
     exit(0);
   }

   for(int i = 0; i < bytesRead; i++)
   {
     lengths[lineIndex] += 1;
     offset += 1;

     if(buf[i] == '\n')
     {
       offsets[lineIndex] = offset - lengths[lineIndex];
       lineIndex += 1;
     }
   }
 }
 *number_of_lines = lineIndex;
}

int main(int argc, char* argv[])
{
  int fileDescriptor = 0;

  if((fileDescriptor = open("/home/students/20200/e.vartazaryan/Lab5/txt", O_RDONLY)) == -1)
  {
    perror("File doesn't exist\n");
    return 0;
  }

  int offsets[256] = {0};
  int lengths[256] = {0};
  int number_of_lines = 0;

  buildFileInfo(offsets, lengths, fileDescriptor, &number_of_lines);

  printf("Enter line number from 1 to %d to print. Enter 0 to finish programm\n", number_of_lines - 1);
  int line_to_print = 1;
  while(true)
  {
    printf("Line: ");
    if(scanf("%d", &line_to_print) != 1)
    {
      printf("Incorrect input!\n");
      fflush(stdin);
      continue;
    }
    if(line_to_print == 0)
     break;
    if(line_to_print < 0 || line_to_print > (number_of_lines - 1))
    {
      printf("Incorrect input!\n");
      fflush(stdin);
      continue;
    }
    if(lseek(fileDescriptor, offsets[line_to_print], SEEK_SET) == -1)
    {
      perror("Couldn't change position in the file\n");
      continue;
    }
    
  char buf[BUFSIZ] = {0};
    if(read(fileDescriptor, &buf, lengths[line_to_print]) == lengths[line_to_print])
    {
      printf("%s", &buf);
    }
    else
    {
      printf("error while reading file\n");
    }
  }

  close(fileDescriptor);
  return 0;
}
