/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:55:36 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/31 15:45:10 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char **av)
{
	char *token;

	if (av[1])
	{		
		if (access(av[1], F_OK == -1))
			printf("cd: file or directory: %s\n", av[1]);
		else
		{
			parser()->envp = send_to_env(getcwd(NULL, 0), parser()->envp, "OLDPWD", NULL);
			token = oldpwd_aux("OLDPWD");
			parser()->export_env = send_to_exportenv(token, parser()->envp);
			free (token);
			chdir(av[1]);
		}
	}
	else
	{
		parser()->envp = send_to_env(getcwd(NULL, 0), parser()->envp, "OLDPWD", NULL);
		token = oldpwd_aux("OLDPWD");
		parser()->export_env = send_to_exportenv(token, parser()->envp);
		free (token);
		chdir(getenv("HOME"));	
	}
}


char	*oldpwd_aux(char *token)
{
	char *aux;
	char *aux2;
	
	aux = ft_strjoin(token, "=");
	aux2 = ft_strjoin(aux, getcwd(NULL, 0));
	free (aux);
	return (aux2);
}