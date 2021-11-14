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
    if (strchr(string, '=') != NULL)
    {
        while (string[j])
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
    tmp= traitement1(string, c);
    j = thereisequ(tmp);
    i = 0;
    while(env[i] != NULL)
    {
          //  printf("looooool im here \n");
            //printf("tmp == |%c|\n",tmp[j]);
           // printf("%s -- %s -- %d -- %zu -- %lu\n",tmp, env[i], j , ft_strlen(tmp), ft_strlen(tmp) - j);
        if (strncmp(tmp, env[i],  j) == 0)
        {   
            (free(env[i]));
            //env[i] = NULL;
            env[i] = tmp;
          //  printf("waaaaa%s++\n",env[i]);
        }
        i++;
    }
    i=0;
 while(envprinc[i] != NULL)
 {
 if (strncmp(string, envprinc[i], c) == 0)
 {
       //   printf("%s -- %s -- %d\n", string, envprinc[i], c);

    (free(envprinc[i]));
     //envprinc[i] =;
     envprinc[i] = tmp;
 }
     i++;
 }
    while(envprinc[i] != NULL)
   {
       printf("%s\n",envprinc[i]);
       i++;
   }

}

char **addenv2(char *string, char **envpric , char **env)
{
    
}
char **addenv(char **env,char **envprinc, char *string)
{
    int i;

    i = 0;
    if (checkifthereisenv(env, string) == 1)
    {
        while(string[i] )
        {
            if (string[i] == '=')
                replaceenv(env, envprinc, string);
            
            i++;
        }
    }
    else{
       addeven2(string, envprinc, env);
    }
    return(NULL);

}

void    export(char **env, char *string)
{
    char **env1;
    int i = 0;
    char **env2;

    env1 =  transferenv(env);
    env2 = addenv(env1, env, string);
 while(env1[i])
 {
     printf("%s \n",env1[i]);
     i++;
 }
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
  // while (envprinc[i] != NULL)
  // {
  //printf("%s\n",envprinc[i]);
  //i++;
  //  }
   i = 0;
    while(i  < 5)
    {
           // if (i == 1)
           // {
           //     printf("asdasd");
           //     i++;
           //    // continue;
           // }
                
           // buffer = readline("$");
            export(env, "a=make");
            i++;
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