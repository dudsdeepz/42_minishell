/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:55:36 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/26 17:56:01 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char *av)
{
	char	*username;

	username = getenv("HOME");
	if (av)
	{
		if (chdir(av))
			printf("Directory not found!\n");
	}
	else
		chdir(username);	
}