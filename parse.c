/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:29:42 by kkouaz            #+#    #+#             */
/*   Updated: 2023/06/18 23:49:28 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"header.h"

int	*ft_parse(int ac, char **av, t_data *data)
{
	char	**str;
	int		*arr;
	int	i;

	i = 0;
	ac = 0;
	str = ft_check(av, data);
	if(!str)
		return(NULL);
	while(str[i])
		i++;
	if (i != 4 && i != 5)
	{
		printf("i = %d-----\n", i);
		error("invalid arguments !!");
		return(NULL);
	}
	arr = fill_arr(str);
	return(arr);
}

char	**ft_check(char **av, t_data *data)
{
	int		i;
	int		j;
	char	**str;

	i = 1;
	str = ft_split_join(av);
	while (str[i])
	{
		j = 0;
		while(str[i][j])
		{
			if(!ft_isdigit(str[i][j]))
			{
				printf("%sError :", RED);
				printf("%s numeric arguments required !!\n",CYAN);
				return(NULL);
			}
			j++;
		}
		i++;
	}
	data->size= i;
	return(str);
}

int	*fill_arr(char **av)
{
	int	*arr;
	int	i;

	i = 1;
	while(av[i])
		i++;
	arr = (int *)malloc(i * (sizeof(int)));
	if(!arr)
		return(NULL);
	i = 1;
	while (av[i])
	{
		
		arr[i] = ft_atoi(av[i]);
		if (arr[i] == -1)
			return(NULL);
		i++;
	}
	return(arr);
}

char	**ft_split_join(char **av)
{
	int		i;
	char	*joined;
	char 	**str;
	
	i = 1;
	joined = ft_strdup("");
	while(av[i])
	{
		joined = ft_strjoin(joined, " ");
		joined = ft_strjoin(joined, av[i]);
		i++;
	}
	str = ft_split(joined , ' ');
return(str);
}