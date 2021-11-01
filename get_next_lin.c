#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include<fcntl.h>


//#define BUFFER_SIZE

char    *ft_strchr(char *s, char c)
{
    int     i;
    while (*s)
    {
        if (*s == c)
            return s;
        s++;
    }
    return(NULL);
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*dest;
	size_t	i;

	if (!(dest = (char*)malloc(count * size)))
		return (0);
	i = 0;
	while (i < (count * size))
		dest[i++] = 0;
	return (dest);
}

size_t	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*dest;
	char			*src;
	unsigned long	j;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (dest = ft_calloc(1, 1));
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
	return (dest);
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
	free(s1);
	return (dest);
}



char *ft_strdup(char *s, size_t i)
{
   // int     i;
    int     n;
    int     k;
    int j;
    char *dest;
    k = 0;

    j = i;
    while (s[j] != '\0')
    {
        j++;
    }
    k = j;
    n = 0;
    dest = malloc(sizeof(char) * (k + 1));
    while (s[i] != '\0')
    {
        dest[n] = s[i];
        n++;
        i++;
    }
    dest[n] = '\0';
    return(dest);

}

char    *res_handel(char **res, char *line, int n, char *buffer)
{
    
    char *tmp;

             n = ft_strchr(*res, '\n') - *res;
            // printf("||||%d||\n",n);
            line = ft_substr(*res, 0, n);
            tmp = *res;
            *res = ft_strdup(*res, n+ 1);
            line = ft_strjoin(line, "\n");
            free(tmp);
            if (buffer)
                free(buffer);
    return (line);

}

char *get_next_line(int fd)
{
    char *buffer;
    static char *res;
    static int i;
    char *line;
    int     n;

    if (fd < 0)
        return (NULL);
    if(res == NULL)
        res = ft_strdup("",0);
    else if (ft_strchr(res, '\n') != NULL)
    {
        line = res_handel(&res, line, n, NULL);
        return(line);
    }
    buffer = malloc (sizeof(char) * BUFFER_SIZE + 1);
    while ((n = read(fd,buffer, BUFFER_SIZE)) > 0 )
    {
        buffer[n] = '\0';    
        if (n > 0)
        {
            res = ft_strjoin(res, buffer);
            if (ft_strchr(buffer, '\n'))
                {
                    line = res_handel(&res, line, n ,buffer);
                                line = ft_strjoin(line, "\n");
                    return(line);
                }
        }
        else if (ft_strchr(res, '\n') != NULL)
        {
           line =  res_handel(&res, line, n, buffer);
                       line = ft_strjoin(line, "\n");
                    return(line);
        }
        else{
            line = ft_strdup(res , 0);
            return(line);
        }
    }
    free(buffer);
    free(res);
    return (NULL);
}

int main()
{
    int     fd;
    char    *line;
    int i = 0;
    fd = open("get_next_line.c", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        if(i == 204)
            continue;
        printf("%s",line);
        i++;
    }
}