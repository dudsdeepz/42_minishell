/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:52:57 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/07 14:00:29 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char **linei)
{
	if (linei[1])
	{
		if (ft_strncmp(linei[1], "9223372036854775808", ft_strlen(linei[1])) > 0)
		{
			printf("exit\nexit: %s: numeric argument required.\n", linei[1]);
			exit(2);
		}
		else if (ft_strncmp(linei[1], "9223372036854775807", ft_strlen(linei[1])) > 0)
		{
			printf("exit\nexit: %s: numeric argument required.\n", linei[1]);
			exit(2) ;
		}
		else if (check_exit_str(linei[1]))
		{
			printf("exit\nexit: %s: numeric argument required.\n", linei[1]);
			exit(2) ;
		}
		else
			exit(ft_atoi(linei[1]));
	}
	else
		exit(0);
}

int check_exit_str(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
