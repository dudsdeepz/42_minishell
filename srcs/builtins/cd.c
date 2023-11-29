/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:55:36 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/29 16:23:07 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	cd_aux(char *tmp, char *token)
{
	char	**envp;
	char	**export_env;
	char	*oldpwd;

	(void)tmp;
	oldpwd = oldpwd_aux("OLDPWD");
	envp = send_to_env(parser()->envp, oldpwd);
	parser()->envp = envp;
	export_env = send_to_env(parser()->export_env, oldpwd);
	parser()->export_env = export_env;
	free (oldpwd);
	oldpwd = NULL;
	chdir(token);
}

void	_ft_cd(t_tokens **token)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if ((*token)->token[1])
	{
		if ((*token)->token[2])
			ft_putstr_fd("cd: too many arguments!\n", STDERR_FILENO);
		if (access((*token)->token[1], F_OK == -1))
		{
			parser()->exit_status = 1;
			printf("cd: %s: no such file or directory!\n", (*token)->token[1]);
		}
		else
			cd_aux(tmp, (*token)->token[1]);
	}
	else if (search_envvar("HOME"))
		cd_aux(tmp, getenv("HOME"));
	else
		printf("cd: invalid home path\n");
	free(tmp);
	tmp = NULL;
	close_fds(token, 0);
}

char	*oldpwd_aux(char *token)
{
	char	*aux;
	char	*aux2;
	char	*tmp;

	aux = ft_strjoin(token, "=");
	tmp = getcwd(NULL, 0);
	aux2 = ft_strjoin(aux, tmp);
	free(tmp);
	tmp = NULL;
	free (aux);
	aux = NULL;
	return (aux2);
}

int	search_envvar(char *str)
{
	int	i;

	i = 0;
	while (parser()->envp[i])
	{
		if (parser()->envp && !ft_strncmp(parser()->envp[i], str, \
			ft_strlen(str)) && ft_strlen(parser()->envp[i]) > 5)
			return (1);
		i++;
	}
	return (0);
}
