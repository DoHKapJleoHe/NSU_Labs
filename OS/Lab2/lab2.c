#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
extern char *tzname[];
int main()
{
        time_t now;
        struct tm *sp;

        setenv("TZ","America/Los_Angeles", 1); // this function sets time zone. if name alredy exist, then function owerrites it, if last argument is not 0
        (void)time(&now); // function time returns time starting from 1 January of 1970 00:00:00 UTC

        printf("%s", ctime(&now)); // ctime returns adress of symbol. This adress is an adress of the begining of character string, which ends with zero symbol

        /*sp = localtime(&now);
        printf("%d/%d/%02d %d:%02d %s\n",
               sp->tm_mon + 1, sp->tm_mday,
               sp->tm_year, sp->tm_hour,
               sp->tm_min, tzname[sp->tm_isdst]);*/
        exit(0);
}
