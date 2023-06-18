/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 23:07:20 by kkouaz            #+#    #+#             */
/*   Updated: 2023/06/18 23:14:24 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"header.h"

static char	**myfree(char **p)
{
	int	i;

	i = 0;
	if (!p)
		return (NULL);
	while (p[i])
	{
		free (p[i]);
		p[i] = (NULL);
		i++;
	}
	free(p);
	p = NULL;
	return (p);
}

int	count_words(char  *s, char c)
{
	int	i;
	int	count;

	i = 0;
	if (!s)
		return (0);
	count = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int	count_chars(char   *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
	{
	i++;
	}
	return (i);
}

char	**ft_split(char  *s, char c)
{
	char	**str;
	int		len;
	int		i;

	i = 0;
	len = count_words(s, c);
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	while (*s && i < len)
	{
		while (*s == c)
			s++;
		str[i] = ft_substr(s, 0, count_chars(s, c));
		if (!str)
		{
			return (myfree(str));
		}
		s = s + count_chars(s, c);
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	*ft_substr(char *s, int start, int len)
{
	int	i;
	char	*sub;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen_a(s))
		return (ft_strdup("\0"));
	if (len > ft_strlen_a(s) - start)
	len = ft_strlen_a(s) - start;
	sub = malloc(sizeof(char) *(len + 1));
	if (!sub)
		return (0);
	while (s && i < len)
	{
		sub[i++] = s[start++];
	}
	sub[i] = '\0';
	return (sub);
}
