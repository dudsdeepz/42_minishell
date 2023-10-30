/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:55:36 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/30 11:30:41 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char **av)
{
	//just setting oldpwd missing
	if (av[1])
	{		
		if (access(av[1], F_OK == -1))
			printf("cd: file or directory: %s\n", av[1]);
		else
			chdir(av[1]);
	}
	else
		chdir(getenv("HOME"));	
}