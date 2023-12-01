/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:55:36 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 15:19:02 by eduarodr         ###   ########.fr       */
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
	if (chdir(token) == -1)
	{
		parser()->exit_status = 1;
		return (perror(" "));
	}
	oldpwd = oldpwd_aux("PWD");
	envp = send_to_env(parser()->envp, oldpwd);
	parser()->envp = envp;
	export_env = send_to_env(parser()->export_env, oldpwd);
	parser()->export_env = export_env;
	free (oldpwd);
	oldpwd = NULL;
}

void	_ft_cd(t_tokens **token)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if ((*token)->token[1])
	{
		if (cd_errors((*token)->token))
		{
			free(tmp);
			tmp = NULL;
			close_fds(token, 0);
		}
		else
		{
			parser()->exit_status = 0;
			cd_aux(tmp, (*token)->token[1]);
		}
	}
	else if (search_envvar("HOME"))
		cd_aux(tmp, getenv("HOME"));
	else
		printf("cd: invalid home path\n");
	free(tmp);
	tmp = NULL;
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

int	cd_errors(char **token)
{
	if (token[2])
	{
		parser()->exit_status = 1;
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
