 #include "minishell.h"

//void    add_back(void *data)
//{
//
//}

static	int		len_word(const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
    if (s[i] =='"')
    {
        len++;
        i++;
        while(s[i] != '"')
        {
            len++;
            i++;
        }
    }
	while (s[i] != c && s[i])
    {
        if (s[i] == '"')
        {
            len++;
            i++;
            while(s[i] != '"' )
        {
            len++;
            i++;
        }
        }
        else if (s[i] != c && s[i])
            len++;
            i++;
        
    } 
	return (len);
}
static	int		count_word(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		if (s[i] == '"')
		{
			i++;
			while(s[i] != '"')
			 i++;
		}
		while (s[i] != c && s[i + 1])
			i++;
		i++;
	}
	return (count);
}

//char **ft_split( char *s, char c)
//{
//    size_t	i;
//	size_t	j;
//	size_t	k;
//	char	**split;
//
//	i = 0;
//	k = 0;
//	if (!s || !(split = (char **)malloc(sizeof(char *)
//					* (count_word(s, c) + 1))))
//}
 int    main()
 {
     int i;
     char *buffer;
     int n;
  //   int j = 0;

    t_file *file;

    file = (t_file*)malloc(sizeof(t_file));

    i = 0;
   // while (1)
    // {
          write(1, "Minishell:0.0> ", 15);
       //   get_next_line(0, line, 1000);;
     buffer = malloc(sizeof(char) * (1025));
    n = read(STDIN_FILENO, buffer, 1024);
    buffer[n] = '\0';
   //while (buffer[i] != '\0')
   //{
   //    if (buffer[i] == '|' || buffer[i + 1] == '\0')
   //    {
   //       // arg.string = ft_substr(buffer,j , i - j);

   //        j = i++;
   //    }
   //    i++;
   //}
    printf("len == %d\n",len_word(buffer,' '));
    printf("%d\n",count_word(buffer,' '));
    buffer[i] = '\0';
   //arg.string = buffer;

   //printf("%s\n",arg.string);
 
 }
 