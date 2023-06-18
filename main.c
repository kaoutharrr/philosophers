/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:29:29 by kkouaz            #+#    #+#             */
/*   Updated: 2023/06/18 23:49:59 by kkouaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	int	i = 0;
	int	*args;
	t_data data;

	if (ac < 2)
	{
		printf("%sError : ", RED);
		printf("%sinvalid arguments !!\n",CYAN);
		return(0);
	}
	args = ft_parse(ac , av, &data);
	if(!args)
		return(0);
	i = data.size;
	printf("%s size of arr ===== %d\n", YELLOW, i);
	//process(args, i);
	free(args);
	return (0);
}
