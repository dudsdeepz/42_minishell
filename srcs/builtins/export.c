/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:28:15 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/26 17:55:14 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    display_export(char **env)
{
    int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n",env[i]);
		++i;
	}
	return ;
}

void	ft_export(char **av)
{
	if (list_size(av) == 1)
		display_export(parser()->envp);
	return ;
}