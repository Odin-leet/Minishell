#include "minishell.h"
#include <string.h>
typedef struct s_struct{
	char **env1;
	char **envprinc;
	int value;
	int key;
}               t_struct;
t_struct pl;

size_t	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*dest;
	unsigned long	i;
	unsigned long	j;
	size_t			res_len;

	if (!(res_len = 0) && s1)
		res_len = ft_strlen(s1);
	j = 0;
	if (!(dest = (char*)malloc(res_len + ft_strlen(s2) + 1)))
		return (0);
	i = -1;
	if (s1 == 0 && s2 == 0)
		return (0);
	while (++i < res_len)
		dest[i] = s1[i];
	res_len = ft_strlen(s2);
	while (j < res_len)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	//free(s1);
	//free(s2);
	return (dest);
}
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*dest;
	char			*src;
	unsigned long	j;

	if (s == 0)
		return (0);
	//	if (start > ft_strlen(s))
	//		return (dest = ft_calloc(1, 1));
	else
	{
		j = 0;
		src = (char*)s;
		if (!(dest = (char*)malloc(len + 1)))
			return (0);
		while (*src && j < len)
		{
			dest[j] = src[start];
			j++;
			start++;
		}
		dest[j] = '\0';
	}
	//free(s);
	return (dest);
}
int thereisequ(char *env)
{
	int i;

	i = 0;
	while(env[i] != '\0')
	{
		if (env[i] == '=')
			return(i);
		i++;
	}
	return(-1);
}

char *traitement1(char *str, int j)
{
	char *tmp1;
	char *tmp2;
	char *tmp3;
	char *str2;

	str2 = malloc(sizeof(char) * 2);
	str2[0] = '\"';
	str2[1] = '\0';
	tmp1 = ft_substr(str, 0, j + 1);
	tmp2 = ft_substr(str, j + 1, ft_strlen(str) - (j + 1) );
	//free(str); decommenter quand str ca sera un string deja allouer 
	tmp3 = tmp2;
	tmp2 = ft_strjoin(str2, tmp2);
	free(tmp3);
    //free(str);
	tmp3 = tmp2;
	tmp2 =ft_strjoin(tmp2,str2);
	free(tmp3);
	tmp3 = tmp2;
	tmp2 = ft_strjoin(tmp1, tmp2);
	free(tmp3);
	free(tmp1);
    tmp3 = tmp2;
	tmp2 = ft_strjoin("declare -x ", tmp2);
    free(tmp3);
	free(str2);
	return(tmp2);

}

char *traitement2(char *str)
{
	char *tmp;

	tmp = ft_strjoin("declare -x ", str);
	return(tmp);
}
char **transferenv(char **tmp)
{
	int i;
	int j;
	char **tmp1 =NULL;

	i = 0;
	j = 0;
	while(tmp[i])
		i++;
	tmp1 = malloc(sizeof(char*) * i +1);
	i = 0;
	while(tmp[i] != NULL)
	{
		if ((j = thereisequ(tmp[i])) != -1)
		{
			tmp1[i] = traitement1(tmp[i], j);
		}
		else
			tmp1[i] = traitement2(tmp[i]);
		i++;
	}
	tmp1[i] = NULL;
	return(tmp1);
}
int     checkifthereisenv(char **env, char *string)
{
	int i;
	int count;
	count= 0;
	int j;
	char *tmp;

	tmp = NULL;
	i = 0;
	tmp = ft_strjoin("declare -x ", string);

    i= 0;
    j = 0;
	while (env[i] != NULL)
	{   
        j = 0;
        while (env[i][j] !='\0')
        {
            if(env[i][j] == '=')
            {
                count = j;
                break;
            }
            j++;
            if(env[i][j] == '\0')
                count = j;

        }
		if (strncmp(tmp, env[i], count) == 0)
		{
			free(tmp);
			return(1);
		}
		i++;
 	}
    free(tmp);
	return(0);
}
int     counttab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;

	return(i);
}
void    unsetenv1(t_struct *pl, char *string)
{
    char **tmp1;
    char **tmp2;
    char *tmp;
    int count;
    int i;
    int c = 0;
    int j;

    i = 0;
    j = 0;

    tmp2 = malloc(sizeof(char *) * (counttab(pl->env1)));

    tmp1 = malloc(sizeof(char *) * (counttab(pl->envprinc)));
    tmp =  ft_strjoin("declare -x ", string);
    while (pl->env1[i] != NULL)
	{   
        j = 0;
        while (pl->env1[i][j] !='\0')
        {
            if(pl->env1[i][j] == '=')
            {
                count = j;
                break;
            }
            j++;
            if(pl->env1[i][j] == '\0')
                count = j;

        }
		if (strncmp(tmp, pl->env1[i], count) == 0)
        {
            count = i;
            break;
        }
		i++;
 	}
     i = 0;
     while(pl->env1[i] != NULL)
     {
         if (i == count)
          i++;
          else
          {
          tmp2[c] = malloc(sizeof(char) * (ft_strlen(pl->env1[i]) + 1));
            c++;
            i++;
          }
     }
  
    i = 0;
	c = 0;
    while(pl->env1[i] != NULL)
    {
        j = 0;
        if (i == count)
            i++;
        else
        {
        while(pl->env1[i][j] != '\0')
        {
            tmp2[c][j] = pl->env1[i][j];
            j++;
        }
        tmp2[c][j] = '\0';
        i++;
        c++;
        } 
    }
    tmp2[c] = NULL;
    /*dsadasdashjasdjas;ldjlasjdiasjdioasdjuoasdjioasdjioasdjioasjdas*/

  // i = 0;
  //  while (pl->envprinc[i] != NULL)
//{   
  //     j = 0;
  //     while (pl->envprinc[i][j] !='\0')
  //     {
  //         if(pl->envprinc[i][j] == '=')
  //         {
  //             count = j;
  //             break;
  //         }
  //         j++;
  //         if(pl->envprinc[i][j] == '\0')
  //             count = j;
  //     }
//	if (strncmp(string, pl->envprinc[i], count) == 0)
  //     {
  //         count = i;
  //         break;
  //     }
//	i++;
 //}
  //  i = 0;
  //  while(pl->envprinc[i] != NULL)
  //  {
  //      if (i == count)
  //       i++;
  //       else
  //       {
  //       tmp1[c] = malloc(sizeof(char) * (ft_strlen(pl->envprinc[i]) + 1));
  //         c++;
  //         i++;
  //       }
  //  }
  //
  // i = 0;
  // while(pl->envprinc[i] != NULL)
  // {
  //     j = 0;
  //     if (i == count)
  //         i++;
  //     else
  //     {
  //     while(pl->envprinc[i][j] != '\0')
    //  {0
  //         tmp1[c][j] = pl->envprinc[i][j];
  //         j++;
  //     }
  //     tmp1[][j] = '\0';
  //     i++;
  //     c++;
  //     } 
  // }
  // tmp1[c] = NULL;
    i = 0;
    while (pl->env1[i] != NULL)
    {
        free(pl->env1[i]);
        i++;
    }
    free(pl->env1);
    i = 0;
  //  while (pl->envprinc[i] != NULL)
  // {
  //     free(pl->envprinc[i]);
  //     i++;
  // }
  // free(pl->envprinc);
	free(tmp);
    pl->env1 = tmp2;
 //  pl->envprinc = tmp1;
    





}
void    unset(t_struct *pl, char *string)
{
    int i=0;

    if(checkifthereisenv(pl->env1, string) == 1)
    {
        unsetenv1(pl , string);
    }
    while(pl->env1[i])
    {
        printf("%s\n",pl->env1[i++]);
    }
}


int main(int argc, char **Argv, char **env)
{
    char **tmp;
	char *buffer;


	int i = 0;
	int j = 0;
	t_struct pl;

	i = 0;
	j = 0;
    
	while (env[i] != NULL)
		i++;
	pl.envprinc = malloc(sizeof (char *) * (i + 1));
	//printf("%d -- \n",i);
	i = 0;
	while(env[i])
	{
		j = 0;
		j = ft_strlen(env[i]);
		pl.envprinc[i] = malloc(sizeof(char) * (j  + 1));
		i++;
	}
	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			pl.envprinc[i][j] = env[i][j];
			j++;
		}
		pl.envprinc[i][j] = '\0';
		i++;
	}
	pl.envprinc[i] = NULL;
    pl.env1 =  transferenv(pl.envprinc);
	i = 0; 
	//(1)
	while(1)
	{
		buffer = readline("$");
		unset(&pl, buffer);
        
    }   
    //i = 0;
     while(pl.env1[i])
		{
			//printf("%d -- \n", i);
			free(pl.env1[i++]);
		}
			free(pl.env1);
		i = 0;
		while(pl.envprinc[i])
		{
//
			free(pl.envprinc[i++]);
		}	
		free(pl.envprinc);
		
    while (1);
    return(0);
}