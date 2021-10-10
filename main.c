#include <stdlib.h>
#include <stdio.h>

static	size_t		count_word(const char *s, char c)
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

int main(int argc, char **argv)
{
    count_word()
}