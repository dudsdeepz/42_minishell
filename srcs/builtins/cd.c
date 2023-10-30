/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:55:36 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/30 16:34:37 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char **av)
{
	if (av[1])
	{		
		if (access(av[1], F_OK == -1))
			printf("cd: file or directory: %s\n", av[1]);
		else
		{
			parser()->envp = send_to_env(getcwd(NULL, 0), parser()->envp, "OLDPWD");
			parser()->export_env = send_to_exportenv( \
				ft_strjoin(ft_strjoin("OLDPWD", "="), getcwd(NULL, 0)), parser()->envp);
			chdir(av[1]);
		}
	}
	else
	{
		parser()->envp = send_to_env(getcwd(NULL, 0), parser()->envp, "OLDPWD");
		parser()->export_env = send_to_exportenv( \
		ft_strjoin(ft_strjoin("OLDPWD", "="), getcwd(NULL, 0)), parser()->envp);
		chdir(getenv("HOME"));	
	}
}