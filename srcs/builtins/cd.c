/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:55:36 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/22 17:48:49 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_ft_cd(t_tokens **token)
{
	char *oldpwd;
	char *tmp;

	tmp = getcwd(NULL, 0);
	if ((*token)->token[1])
	{		
		if (access((*token)->token[1], F_OK == -1))
			printf("cd: no such file or directory: %s\n", (*token)->token[1]);
		else
		{
			parser()->envp = send_to_env(tmp, parser()->envp, "OLDPWD");
			oldpwd = oldpwd_aux("OLDPWD");
			parser()->export_env = send_to_exportenv(oldpwd, parser()->envp);
			free (oldpwd);
			chdir((*token)->token[1]);
		}
	}
	else if (search_envvar("HOME"))
	{
		parser()->envp = send_to_env(tmp, parser()->envp, "OLDPWD");
		oldpwd = oldpwd_aux("OLDPWD");
		parser()->export_env = send_to_exportenv(oldpwd, parser()->envp);
		free (oldpwd);
		chdir(getenv("HOME"));
	}
	else
		printf("cd: invalid home path\n");
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

int	search_envvar(char *str)
{
	int i;

	i = 0;
	while (parser()->envp[i])
	{
		if (!ft_strncmp(parser()->envp[i], str, ft_strlen(str)) \
			&& ft_strlen(parser()->envp[i]) > 5)
			return (1) ;
		i++;
	}
	return (0);
}