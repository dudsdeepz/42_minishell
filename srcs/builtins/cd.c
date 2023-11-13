/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:55:36 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/10 09:42:58 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char **av)
{
	char *token;
	char *tmp;

	tmp = getcwd(NULL, 0);
	if (av[1])
	{		
		if (access(av[1], F_OK == -1))
			printf("cd: file or directory: %s\n", av[1]);
		else
		{
			parser()->envp = send_to_env(tmp, parser()->envp, "OLDPWD");
			token = oldpwd_aux("OLDPWD");
			parser()->export_env = send_to_exportenv(token, parser()->envp);
			free (token);
			chdir(av[1]);
		}
	}
	else
	{
		parser()->envp = send_to_env(tmp, parser()->envp, "OLDPWD");
		token = oldpwd_aux("OLDPWD");
		parser()->export_env = send_to_exportenv(token, parser()->envp);
		free (token);
		chdir(getenv("HOME"));	
	}
	free(tmp);
}


char	*oldpwd_aux(char *token)
{
	char *aux;
	char *aux2;
	char *tmp;
	
	aux = ft_strjoin(token, "=");
	tmp = getcwd(NULL, 0);
	aux2 = ft_strjoin(aux, tmp);
	free(tmp);
	free (aux);
	return (aux2);
}