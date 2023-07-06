/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:29:42 by kkouaz            #+#    #+#             */
/*   Updated: 2023/06/25 16:00:23 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"header.h"

int	*ft_parse(int ac, char **av)
{
	char	**str;
	int		*arr;
	int		i;

	i = 0;
	ac = 0;
	str = ft_check(av);
	if (!str)
		return (NULL);
	arr = fill_arr(str);
	return (arr);
}

char	**ft_check(char **av)
{
	int		i;
	int		j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("%sError :", RED);
				printf("%s numeric arguments required !!\n", CYAN);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	return (av);
}

int	*fill_arr(char **av)
{
	int	*arr;
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (av[i])
		i++;
	arr = (int *)malloc(i * (sizeof(int)));
	if (!arr)
		return (NULL);
	i = 1;
	while (av[i])
	{
		arr[j] = ft_atoi(av[i]);
		if (arr[j] == -1 || arr[j] == 0)
			return (NULL);
		i++;
		j++;
	}
	return (arr);
}
