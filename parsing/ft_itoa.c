/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 09:26:37 by aali-mou          #+#    #+#             */
/*   Updated: 2021/11/27 09:26:38 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*if3(long j)
{
	char	*dest;

	j = 0;
	dest = (char *)malloc(sizeof(char) * 2);
	if (dest == NULL)
		return (NULL);
	dest[j] = '0';
	dest[++j] = '\0';
	return (dest);
}

char	*if1(long j)
{
	int		i;
	long	c;
	char	*dest;

	j = -j;
	c = j;
	i = 1;
	while ((c / 10) != 0)
	{
		c = c / 10;
		i++;
	}
	dest = (char *)malloc(sizeof(char) * i + 2);
	if (dest == NULL)
		return (NULL);
	i = i + 1;
	dest[i] = '\0';
	while (j > 0)
	{
		i--;
		dest[i] = j % 10 + 48;
		j = j / 10;
	}
	dest[--i] = '-';
	return (dest);
}

char	*if2(long j)
{
	int		i;
	long	c;
	char	*dest;

	c = j;
	i = 1;
	while ((c / 10) != 0)
	{
		c = c / 10;
		i++;
	}
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	dest[i] = '\0';
	while (j > 0)
	{
		i--;
		dest[i] = j % 10 + 48;
		j = j / 10;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	long	j;
	char	*a;

	j = (long)n;
	if (j == 0)
	{
		a = if3(j);
	}
	else if (j < 0)
	{
		a = if1(j);
	}
	else
		a = if2(j);
	return (a);
}
