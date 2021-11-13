#include "minishell.h"

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

int  main()
{
    char str[10] = "PATH=12345";
    int j = 4;
    char *tmp1;
    char *tmp2;
    char *tmp3;

    tmp1 = ft_substr(str, 0, j + 1);
    tmp2 = ft_substr(str, j + 1, ft_strlen(str) - (j + 1) - 1);
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
    printf("%s\n",tmp2);
    while (1);
    return(0);
    
}