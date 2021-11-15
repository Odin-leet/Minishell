#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct s_struct{
    int **env1;
    //int **env1;
}               t_struct;

void    pass2tofunc(t_struct *pl)
{
            int i;
    i = 0;
     int j;
     j = 0;
    while(i < 4)
    {
        j = 0;
        while (j < 4){
            pl->env1[i][j] = 2;
            j++;
        }
        i++;
    }
}


void    passtofunc(t_struct *pl)

{
    int i;
    i = 0;
     int j;
     j = 0;
    while(i < 4)
    {
        j = 0;
        while (j < 4){
            pl->env1[i][j] = 1;
            j++;
        }
        i++;
    }
    pass2tofunc(pl);
}

int main()
{
    int A[4][4];
    int i;
    t_struct pl;



    i = 0;
   pl.env1= malloc(sizeof(int *) * 4);
   while(i < 4)
   {
       pl.env1[i] = malloc(sizeof(int) * 4);
       i++;
   }
   i = 0;
    int j;
    while(i < 4)
    {
        j = 0;
        while (j < 4){
            pl.env1[i][j] = 0;
            j++;
        }
        i++;
    }
    i = 0;
        passtofunc(&pl);

    while (i <  4)
    {
        j = 0;
        while ( j < 4)
        {
            printf("%d",pl.env1[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }

    //A={1,2,3};
}