
char	*changecollectedcmd(char *string, int count)
{
	char	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	tmp = NULL;
	tmp = malloc(sizeof(char) * (ft_strlen(string) - count + 1));
	while (string[i] != '\0')
	{
		db_quotesreplace(&tmp, string, &c, &i);
		if (string[i] == '\'')
		{
			i++;
			if (string[i] == '\'')
				i++;
			else
			{
				while (string[i] != '\'' && string[i])
					tmp[c++] = string[i++];
				if (string[i] == '\'')
						i++;
			}
		}
		if (string[i] != '\0')
		{
		tmp[c] = string[i];
		c++;
		i++;
		}
	}
	tmp[c] = '\0';
	free(string);
	return(tmp);
