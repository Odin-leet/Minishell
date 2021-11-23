#include "minishell.h"
#include <string.h>

char    *getstringfromenv(t_vars *pl, char *string)
{
    int     i;
    int     count;
    char    *retustring;
    int     c;

    i = 0;
    while(pl->envprinc[i] != NULL)
    {
        count = ft_strlen(string);
        c = thereisequ(pl->envprinc[i]);
        if (c != -1)
        {
            if (count < c)
                count = c;
        }
        else
        {
            c = ft_strlen(pl->envprinc[i]);
            if (count < c)
                count = c;
        }
        if (strncmp(pl->envprinc[i], string, count) == 0)
            return(ft_substr(pl->envprinc[i], count + 1, ft_strlen(pl->envprinc[i]) - count ));
        i++;
    }
    return (NULL);
}
