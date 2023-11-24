/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:55:36 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/24 12:07:53 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	cd_aux(char *oldpwd, char *tmp, char *token)
{
	char	**envp;
	char	**export_env;

	envp = parser()->envp;
	export_env = parser()->export_env;
	envp = send_to_env(tmp, envp, "OLDPWD");
	oldpwd = oldpwd_aux("OLDPWD");
	export_env = send_to_exportenv(oldpwd, envp);
	free (oldpwd);
	oldpwd = NULL;
	chdir(token);
}

void	_ft_cd(t_tokens **token)
{
	char	*oldpwd;
	char	*tmp;

	oldpwd = NULL;
	tmp = getcwd(NULL, 0);
	if ((*token)->token[1])
	{
		if (access((*token)->token[1], F_OK == -1))
			printf("cd: no such file or directory: %s\n", (*token)->token[1]);
		else
			cd_aux(oldpwd, tmp, (*token)->token[1]);
	}
	else if (search_envvar("HOME"))
		cd_aux(oldpwd, tmp, getenv("HOME"));
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
