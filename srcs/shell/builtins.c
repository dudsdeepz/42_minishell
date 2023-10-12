/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:48:45 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/12 14:36:01 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_pwd(char *av)
{
	char	cwd[2048];
	int		i;
	char	**line;

	i = 0;
	line = ft_split(av, ' ');
	while (line[i])
		i++;
	if (i > 1)
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	
	else
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (0);
}

void	display_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n",env[i]);
		++i;
	}
	return ;
}

void	ft_cd(char *av)
{
	char	*username;

	username = getenv("USER");
	if (av)
	{
		if (chdir(av))
			printf("Directory not found!\n");
	}
	else
		chdir(username);	
}

void	ft_echo(char **av)
{
	int i;

	i = 1;
	if (av[1])
	{
		if (ft_echo_cases(av) == 1 && av[2])
		{
			if (ft_echo_cases(av) == 2)
				printf("%s", av[1]);
			else if (!ft_echo_cases(av))
				return ;
			while (av[++i])
				printf("%s ", av[i]);
			printf("\b");
			return ;
		}
		else if (ft_echo_cases(av) == 1 && !av[2])
		{
			printf("\n");
			return ;
		}
		else
		{
			while (av[i])
				printf("%s ", av[i++]);
			printf("\n");
		}
	}
	else
		printf("\n");
}

void	ft_export(char **av)
{
	(void)av;
	// int proc;
	// char *export_var;
	
	// proc = fork();
	// export_var = 
}

int ft_echo_cases(char **av)
{
	int i = 0;

	if (av[1])
	{
		if (av[1][i] == '-')
			i++;
		while (av[1][i])
		{
			if (av[1][i] == 'n')
				i++;
			else if (ft_isalpha(av[1][i]))
				return (2);
			else
			{
				printf("Error command not found: %s\n", av[1]);
				return (0);
			}
		}
	}
	return (1);
}

// void	ft_unset(char **av)
// {
// 	char **new;
	
// 	if (!av[1])
// 		return ;
// 	new = dup_matrix(parser()->envp, av[1]);
// 	parser()->envp = new;
// 	free(new);
// 

void	ft_unset(char **av)
{
	int		p;
	char	**res;
	int 	j;

	if (!av[1])
		return ;
	p = 0;
	while (parser()->envp[p++] != 0)
		continue;
	j = 1;
	while (av[j++])
		continue ;
	res = malloc(sizeof(char *) * (p - j + 1));
	p = -1;
	j = 1;
	while (parser()->envp[++p])
	{
		if (!ft_strncmp(av[j], parser()->envp[p], ft_strlen(av[j])))
		{
			p++;
			j++;
		}
		res[p] = ft_strdup(parser()->envp[p]);
	}
	res[++p] = NULL;
	free_matrix(parser()->envp);
	parser()->envp = dup_matrix(res);
	free_matrix(res);
}

char **dup_matrix(char **src)
{
	int		p;
	char	**res;

	p = 0;
	while (src[p++] != 0)
		continue ;
	res = malloc(sizeof(char *) * (p + 1));
	p = -1;
	while (src[++p] != 0)
		res[p] = ft_strdup(src[p]);
	res[p++] = NULL;
	return (res);
}

void	free_matrix(char **mtx)
{
	int	p;

	p = 0;
	while (mtx[p])
		free(mtx[p++]);
	free(mtx);
}
