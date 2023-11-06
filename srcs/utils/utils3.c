/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:00:42 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/06 17:04:41 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*triple_strjoin(char *s1, char *s2, char *s3)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	while (*s3)
		res[i++] = *s3++;
	res[i] = 0;
	return (res);
}

void	print_tokens(char **av)
{
	int i;
	
	i = 0;
	while (av[i])
	{
		printf("%s\n", av[i]);
		i++;
	}
	printf("====\n");
}

void	ft_exit(char **linei)
{
	if (linei[1])
	{
		/*if (ft_isdigit(linei[1]))
		{
			printf("exit: numeric argument required.");
			return ;
		}*/
		if (linei[1])
		{
			if (ft_strncmp(linei[1], "9223372036854775808", ft_strlen(linei[1])) > 0)
			{
				printf("exit\nexit: %s: numeric argument required.\n", linei[1]);
				exit(2) ;
			}
		}
		else if (ft_strncmp(linei[1], "9223372036854775807", ft_strlen(linei[1])) > 0)
		{
			printf("exit\nexit: %s: numeric argument required.\n", linei[1]);
			exit(2) ;
		}
	}
	else
		exit(0);
}
