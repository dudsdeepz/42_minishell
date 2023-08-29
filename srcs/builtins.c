/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:48:45 by eduarodr          #+#    #+#             */
/*   Updated: 2023/08/29 11:10:19 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_pwd(char *av)
{
	char	cwd[1024];
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
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (0);
}

void	clr_shell(void)
{
	const char	*clear = "\e[1;1H\e[2J";

	printf("%s", clear);
}

void	display_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n",env[i]);
		i++;
	}
	return ;
}

void	ft_cd(char **av)
{
	char	*username;

	username = getenv("USER");
	if (av[1])
	{
		if (chdir(av[1]))
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

void	ft_unset(char **av)
{
	char **var;
	char **new;
	int i;
	
	i = 0;
	new = tokens()->envp;
	while(new[i++] != 0)
	{
		var = ft_split(*new, '=');
		if (!ft_strncmp(var[0], av[1], ft_strlen(av[1])))	
		{
			printf("%s%s%s\n", RED, *new, DEFAULT);
			new[i] = 0;
			return ;
		}
	}
	while (new[i++])
		*tokens()->token = new[i];
	return ;
}
