#include "minishell.h"
#include <string.h>

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
char *traitement1(char *str, int j)
{
    char *tmp1;
    char *tmp2;
    char *tmp3;

    tmp1 = ft_substr(str, 0, j + 1);
    tmp2 = ft_substr(str, j + 1, ft_strlen(str) - (j + 1) );
    //free(str); decommenter quand str ca sera un string deja allouer 
    tmp3 = tmp2;
    tmp2 = ft_strjoin("\"", tmp2);
    free(tmp3);
    tmp3 = tmp2;
    tmp2 =ft_strjoin(tmp2, "\"");
    free(tmp3);
    tmp3 = tmp2;
    tmp2 = ft_strjoin(tmp1, tmp2);
    free(tmp3);
    free(tmp1);
    tmp2 = ft_strjoin("declare -x ", tmp2);

    return(tmp2);

}

char *traitement2(char *str)
{
    char *tmp;

    tmp = ft_strjoin("declare -x ", str);
    return(tmp);
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
    j= 0;
    if (strchr(string, '=') != NULL)
    {
        while (tmp[j])
        {
            if(tmp[j] == '=')
            {
                count = j;
                break;
            }
            j++;
        }
    }
     else 
        count = ft_strlen(tmp);
    while (env[i] != NULL)
    {
            if (strncmp(tmp, env[i], count) == 0)
                return(1);
       
        i++;
    }
    return(0);
}

void    replaceenv(char **env, char **envprinc, char *string)
{
    int i;
    char *tmp;
    int j;
    int c;
    c = 0;
    j = 0;

     c = thereisequ(string);
     if(strncmp(string, "declare -x", 6) != 0)
     {
        tmp= traitement1(string, c);
             j = thereisequ(tmp);

     }
    else
        {
            tmp = string;
            j = c;
        }
    i = 0;
    while(env[i])
    {
          //  printf("looooool im here \n");
            //printf("tmp == |%c|\n",tmp[j]);
           // printf("%s -- %s -- %d -- %zu -- %lu\n",tmp, env[i], j , ft_strlen(tmp), ft_strlen(tmp) - j);
        if (strncmp(tmp, env[i],  j) == 0)
        {   
            (free(env[i]));
            env[i] = NULL;
            env[i] = tmp;
          //  printf("waaaaa%s++\n",env[i]);
        }
        i++;
    }
    i=0;
 while(envprinc[i])
 {
 if (strncmp(string, envprinc[i], c) == 0)
 {
       //   printf("%s -- %s -- %d\n", string, envprinc[i], c);

    // (free(envprinc[i]));
     envprinc[i] = NULL;
     envprinc[i] = string;
 }
     i++;
 }
 i = 0;
  // while(envprinc[i])
  //{
  //    printf("%s\n",envprinc[i]);
  //    i++;
  //}

}
int     counttab(char **tab)
{
    int i;
    
    i = 0;
    while(tab[i])
     i++;
    
    return(i);
}
char **addenv2(char *string, char **envpric , char **env)
{
    int c;
    char *tmp;
    char **tmp1;
    char **tmp3;

    tmp3 =NULL;
    int j;
    j = 0;
    c = 0;
                printf("%s \n",string);
                printf("%d\n",thereisequ(string));

    if ((c = thereisequ(string)) != -1)
    {
        tmp = traitement1(string, c);
        tmp1 = malloc(sizeof(char *) * (counttab(env) + 2));
        c = 0;
        while(env[c] != NULL)
        {
            tmp1[c] = malloc(sizeof(char) * (ft_strlen(env[c]) + 1));
            c++;
        }
        c = 0;
        while(env[c])
        {
            j = 0;
            while(env[c][j])
            {
                tmp1[c][j] = env[c][j];
                j++;
            }
            tmp1[c][j] = '\0';
            c++;
        }
        tmp1[c] = malloc(sizeof(char ) * (ft_strlen(tmp)+ 1));
        j = 0;
        while(j < ft_strlen(tmp))
        {
            tmp1[c][j] = tmp[j];
            j++;
        }
        tmp1[c][j] = '\0';
        tmp1[++c] = NULL;

    }
    int i;
    i = 0;
    while(tmp1[i])
    {
        printf("%s \n",tmp1[i]);
        i++;
    }
   // printf("saddd poooooooooooooooooop \n");
    env= tmp1;
    return(NULL);
}

char **addenv(char **env,char **envprinc, char *string)
{
    int i;

    i = 0;
    if (checkifthereisenv(env, string) == 1)
    {
               // printf("asdasdasdasdasdasdasdasdas\n");

        while(string[i] )
        {
            if (string[i] == '=')
                replaceenv(env, envprinc, string);
            
            i++;
        }
    }
    else{
        i = 0;
       
       while(string[i] )
        {
            if (string[i] == '=')
                addenv2(string, envprinc, env);
            
            i++;
        }
    }
    return(NULL);

}

void    export(char **env, char *string)
{
    char **env1;
    int i = 0;
    char **env2;

  //  if (strncmp(env[0], "declare -x", 6) != 0)
        env1 =  transferenv(env);
    env2 = addenv(env1, env, string);
  // while(env1[i])
  // {
  //     printf("%s \n",env1[i]);
  //     i++;
  // }
}

int main(int argc , char **argv, char **env)
{
    char **tmp;
    char *buffer;
    char **envprinc;

    int i = 0;
    int j = 0;

    while (env[i] != NULL)
         i++;
    envprinc = malloc(sizeof (char *) * (i + 1));
    printf("%d -- \n",i);
    i = 0;
    while(env[i])
    {
        j = 0;
        j = ft_strlen(env[i]);
        envprinc[i] = malloc(sizeof(char) * (j  + 1));
        i++;
    }
    i = 0;
    while (env[i] != NULL)
    {
        j = 0;
        while (env[i][j] != '\0')
        {
            envprinc[i][j] = env[i][j];
            j++;
        }
        envprinc[i][j] = '\0';
        i++;
    }
    envprinc[i] = NULL;
     i = 0; 
    while(1)
    {
            //tmp = env;
            buffer = readline("$");
            export(env, buffer);
    } 
     //export(env,"a");

    // int i = 0;
    // int j = 0;
     //while (tmp[i] != NULL)
     //{
     //    printf("%s\n",tmp[i]);
     //    i++;
     //}
     return(0);
}