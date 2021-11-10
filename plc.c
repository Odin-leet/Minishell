#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main()
{
    DIR *dir;
    struct dirent *sd;
    dir = opendir("/bin/");
    if (dir == NULL)
    {
        printf("there is no command echo\n");
        return(0);
    }
    while ((sd = readdir(dir)) !=  NULL)
    {
        if (strncmp(sd->d_name , "echo", 5) == 0)
            printf("there is echo\n");
        printf(">> %s\n",sd->d_name);
    }
    return(1);
}