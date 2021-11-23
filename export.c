#include "minishell.h"
#include <string.h>
//typedef struct s_struct{
//	char **env1;
//	char **envprinc;
//	int value;
//	int key;
//}               t_struct;
//t_struct pl;

//int ft_isdigit(int c)
//{
//	unsigned char k;
//
//	k = (unsigned char)c;
//	if (c <= 57 && c >= 48)
//		return (1);
//	else
//		return (0);
//}
//
int ft_isalpha2(int c)
{
	unsigned char k;

	k = (unsigned char)c;
	if (c <= 90 && c >= 65)
		return (1);
		else if (c >= 97 && c <= 122)
			return(1);
	else
		return (0);
}
//size_t	ft_strlen(char *s)
//{
//	int i;
//
//	i = 0;
//	while (s[i] != '\0')
//		i++;
//	return (i);
//}

//char	*ft_strjoin(char *s1, char *s2)
//{
//	char			*dest;
//	unsigned long	i;
//	unsigned long	j;
//	size_t			res_len;
//
//	if (!(res_len = 0) && s1)
//		res_len = ft_strlen(s1);
//	j = 0;
//	if (!(dest = (char*)malloc(res_len + ft_strlen(s2) + 1)))
//		return (0);
//	i = -1;
//	if (s1 == 0 && s2 == 0)
//		return (0);
//	while (++i < res_len)
//		dest[i] = s1[i];
//	res_len = ft_strlen(s2);
//	while (j < res_len)
//		dest[i++] = s2[j++];
//	dest[i] = '\0';
//	//free(s1);
//	//free(s2);
//	return (dest);
//}
//char	*ft_substr(char *s, unsigned int start, size_t len)
//{
//	char			*dest;
//	char			*src;
//	unsigned long	j;
//
//	if (s == 0)
//		return (0);
//	//	if (start > ft_strlen(s))
//	//		return (dest = ft_calloc(1, 1));
//	else
//	{
//		j = 0;
//		src = (char*)s;
//		if (!(dest = (char*)malloc(len + 1)))
//			return (0);
//		while (*src && j < len)
//		{
//			dest[j] = src[start];
//			j++;
//			start++;
//		}
//		dest[j] = '\0';
//	}
//	//free(s);
//	return (dest);
//}
//char *traitement1(char *str, int j)
////{
////	char *tmp1;
////	char *tmp2;
////	char *tmp3;
////	char *str2;
////
////	str2 = malloc(sizeof(char) * 2);
////	str2[0] = '\"';
////	str2[1] = '\0';
////	tmp1 = ft_substr(str, 0, j +1);
////	tmp2 = ft_substr(str, j + 1, ft_strlen(str) - (j + 1) );
////	//free(str); decommenter quand str ca sera un string deja allouer 
////	tmp3 = tmp2;
////	tmp2 = ft_strjoin(str2, tmp2);
////	free(tmp3);
////    //free(str);
////	tmp3 = tmp2;
////	tmp2 =ft_strjoin(tmp2,str2);
////	free(tmp3);
////	tmp3 = tmp2;
////	tmp2 = ft_strjoin(tmp1, tmp2);
////	free(tmp3);
////	free(tmp1);
////    tmp3 = tmp2;
////	tmp2 = ft_strjoin("declare -x ", tmp2);
////    free(tmp3);
////	free(str2);
////	return(tmp2);
////
////}
////
////char *traitement2(char *str)
////{
////	char *tmp;
////
////	tmp = ft_strjoin("declare -x ", str);
////	return(tmp);
//}
//i//nt thereisequ(char *env)
//{//
//	int i;
//
//	i = 0;
//	while(env[i] != '\0')
//	{
//		if (env[i] == '=')
//			return(i);
//		i++;
//	}
//	return(-1);
//}//
////char **transferenv(char **tmp)
//{
//	int i;
//	int j;
//	char **tmp1 =NULL;
//
//	i = 0;
//	j = 0;
//	while(tmp[i])
//		i++;
//	tmp1 = malloc(sizeof(char*) * i +1);
//	i = 0;
//	while(tmp[i] != NULL)
//	{
//		if ((j = thereisequ(tmp[i])) != -1)
//		{
//			tmp1[i] = traitement1(tmp[i], j);
//		}
//		else
//			tmp1[i] = traitement2(tmp[i]);
//		i++;
//	}
//	tmp1[i] = NULL;
//	return(tmp1);
//}

int     checkifthereisenv(char **env, char *string)
{
	int i;
	int count;
	int count2;
	count2 = 0;
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

		j = 0;
        while (env[i][j] !='\0')
        {
            if(env[i][j] == '=')
            {
                count2 = j;
                break;
            }
            j++;
            if(env[i][j] == '\0')
                count2 = j;

        }
		if (count2 > count)
			count = count2;
		if (strncmp(tmp, env[i], count ) == 0)
		{
		//	 int c = 0;
		//while(env[c])
	 	//
		//	// printf("im here ||||||||||||%s\n",env[c]);
		//	 c++;
		//}
			free(tmp);
			return(1);
		}
		i++;
		 
        //******************** here i need to check with the len of the envi not the string cause when i add a string like "a"
        //******************** and there is before a string like "aaa" he traiting it like it s a old var
 	}
	// int c = 0;
	// while(env[c])
	// {
	//	 printf("||||||||||||%s\n",env[c]);
	//	 c++;
	// }
	 free(tmp);
	return(0);
}

void    replaceenv(t_vars *pl, char *string)
{
	int i;
	char *tmp;
	int j;
	int c;
	c = 0;
	j = 0;
	char *string1 = strdup(string);
	c = thereisequ(string);
	//if(strncmp(string, "declare -x", 6) != 0)
	//{
		tmp= traitement1(string1, c);
	//	j = thereisequ(tmp);

	//}
	//else
	//{
	//	tmp = string;
	//	j = c;
	//}
	i = 0;
	while(pl->env1[i])
	{

		j =  ft_strlen(pl->env1[i]);
		c = 0;
		while(pl->env1[i][c])
		{
			if (pl->env1[i][c] == '=')
				j = c;
			c++;
		}
		if (strncmp(tmp, pl->env1[i],  j) == 0)
		{   
			(free(pl->env1[i]));
			pl->env1[i] = NULL;
			pl->env1[i] = tmp;

		}
		i++;
	}
	i=0;
	while(pl->envprinc[i])
	{
		j =  ft_strlen(pl->envprinc[i]);
		c = 0;
		while(pl->envprinc[i][c] != '\0')
		{
			if (pl->envprinc[i][c] == '=')
				j =c;
			c++;
		}
	//	if (strncmp(string , "-n", len(string)));
		if (strncmp(string, pl->envprinc[i], j) == 0)
		{
			printf("akkiiiiadasdsa \n");
            (free(pl->envprinc[i]));
			pl->envprinc[i] = NULL;
			pl->envprinc[i] = string1;
		}
		i++;
	}
	i = 0;
	//free(tmp);
	//free(string1);

}
int     counttab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;

	return(i);
}
char **addenv2(char *string, t_vars *pl)
{
	int c;
	char *tmp;
	char **tmp1;
	char **tmp3;
	char *string1 = strdup(string);

	tmp3 =NULL;
	size_t j;
	j = 0;
	c = 0;
//	printf("%s \n",string);
//	printf("%d\n",thereisequ(string));

	if ((c = thereisequ(string1)) != -1)
	{
	    tmp = traitement1(string1, c);
		tmp1 = malloc(sizeof(char *) * (counttab(pl->env1) + 2));
		tmp3 = malloc(sizeof(char *) * (counttab(pl->envprinc) + 2));
		c = 0;
		while(pl->env1[c] != NULL)
		{
			tmp1[c] = malloc(sizeof(char) * (ft_strlen(pl->env1[c]) + 1));
			c++;
		}
		c= 0;
		while(pl->envprinc[c] != NULL)
		{
			tmp3[c] = malloc(sizeof(char) * (ft_strlen(pl->envprinc[c]) + 1));
			c++;
		}
		c = 0;
		while(pl->env1[c])
		{
			j = 0;
			while(pl->env1[c][j])
			{
				tmp1[c][j] = pl->env1[c][j];
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
		c = 0;
		while(pl->envprinc[c])
		{
			j = 0;
			while(pl->envprinc[c][j])
			{
				tmp3[c][j] = pl->envprinc[c][j];
				j++;
			}
			tmp3[c][j] = '\0';
			c++;
		}
		tmp3[c] = malloc(sizeof(char ) * (ft_strlen(string)+ 1));
		j = 0;
		while(j < ft_strlen(string))
		{
			tmp3[c][j] = string[j];
			j++;
		}
		tmp3[c][j] = '\0';
		tmp3[++c] = NULL;
        free(tmp);
		free(string1);

	}
    else{
        c = ft_strlen(string1);
         tmp = traitement2(string1);
		tmp1 = malloc(sizeof(char *) * (counttab(pl->env1) + 2));
		tmp3 = malloc(sizeof(char *) * (counttab(pl->envprinc) + 2));
		c = 0;
		while(pl->env1[c] != NULL)
		{
			tmp1[c] = malloc(sizeof(char) * (ft_strlen(pl->env1[c]) + 1));
			c++;
		}
		c= 0;
		while(pl->envprinc[c] != NULL)
		{
			tmp3[c] = malloc(sizeof(char) * (ft_strlen(pl->envprinc[c]) + 1));
			c++;
		}
		c = 0;
		while(pl->env1[c])
		{
			j = 0;
			while(pl->env1[c][j])
			{
				tmp1[c][j] = pl->env1[c][j];
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
		c = 0;
		while(pl->envprinc[c])
		{
			j = 0;
			while(pl->envprinc[c][j])
			{
				tmp3[c][j] = pl->envprinc[c][j];
				j++;
			}
			tmp3[c][j] = '\0';
			c++;
		}
		tmp3[c] = malloc(sizeof(char ) * (ft_strlen(string)+ 1));
		j = 0;
		while(j < ft_strlen(string))
		{
			tmp3[c][j] = string1[j];
			j++;
		}
		tmp3[c][j] = '\0';
		tmp3[++c] = NULL;
        free(tmp);
		free(string1);

    }
	int i = 0;
	while (pl->env1[i] != NULL)
	{
			//printf("|%s |\n",pl->env1[i]);

		free(pl->env1[i]);
		i++;
	}
	free(pl->env1);

    i = 0;
	while (pl->envprinc[i] != NULL)
	{
      //  printf("|||||||||||||||||||||%s\n",pl->envprinc[i]);
		free(pl->envprinc[i]);
              //  printf("|||||||||||||||||||||%s\n",pl->envprinc[i]);

		i++;
	}
	free(pl->envprinc);


	pl->env1= tmp1;
//    int p = 0;
  // while (pl->env1[p] != NULL)
  // {
  //     printf("%s\n", pl->env1[p]);
  //     p++;
  // }
	pl->envprinc = tmp3;
	return(NULL);
}

char **addenv(t_vars *pl, char *string)
{
	int i;
    int c;

    c = 0;

	i = 0;
    c = checkifthereisenv(pl->env1, string);
	if (c == 1)
	{
		while(string[i] )
		{
			if (string[i] == '=')
            {
				replaceenv(pl, string);
                c = -1;
            }

			i++;
		}
	}
	else{
             //   printf("asdasdsasdsasdsadasdas |||%d||\n",c);

		i = 0;

	//	while(string[i] )
		//{
		//	//if (string[i] == '=')
				addenv2(string, pl);

			//i++;
	//	}
	}
	return(NULL);
}
int 	checkifitscomp(char *string)
{
		int i = 0;
			if (i == 0 && string[i] == '=')
				return(1);
		while (string[i] != '\0' && string[i] != '=')
		{
			if (string[i] != '_' && (ft_isdigit(string[i]) == 0) && (ft_isalpha2(string[i]) == 0))
				return(1);
			i++;
		}
		return (0);
}	
int    export(t_vars *pl)
{
	//char **env1;
	int i = 1;
	if (pl->collected_cmd[1] == NULL)
	{
		i =0;
		while(pl->env1[i])
		{
			printf("%s \n",pl->env1[i]);
			i++;
		}
	}
	else{
	//  if (strncmp(env[0], "declare -x", 6) != 0)
	i = 1;
	while (pl->collected_cmd[i] != NULL)
	{
		if (checkifitscomp(pl->collected_cmd[i]) == 1)
			{
				printf("error of export\n");
				return(0);
			}
		else
	 		addenv(pl, pl->collected_cmd[i]);
		i++;
	}	
	}
	
	return(1);
	

}

int		env(t_vars *pl)
{
	int i;
	i = 0;
	if (pl->collected_cmd[1] != NULL)
	{
		printf("env: %s: No such file or directory\n",pl->collected_cmd[1]);
		return(0);
	}
	while(pl->envprinc[i] != NULL)
	{
		if ( thereisequ(pl->envprinc[i]) != -1)
			printf("%s\n",pl->envprinc[i]);
		i++;
	}
	return(1);
}
