/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:49 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/24 14:37:35 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*cwd;

	(void)av;
	cwd = NULL;
	if (ac == 1)
	{
		sig_actions();
		parser()->envp = dup_matrix(env);
		parser()->export_env = dup_matrix(env);
		parser()->tmp_matrix = NULL;
		while (1)
		{
			if (getenv("SHLVL"))
				cwd = readline("minishell: ");
			if (!cwd)
				return (0);
			if (ft_strlen(cwd) > 0)
			{
				add_history(cwd);
				shell(cwd);
			}
		}
	}
	return (0);
}

int	list_size(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

void	shell(char *cwd)
{
	char	*tmp;

	tmp = get_prompt(cwd, malloc(ft_strlen(cwd) * 5));
	if (tmp)
		if (parsing(tmp))
			shell_output(tmp);
	free(tmp);
	tmp = NULL;
}

int	ft_heredoc(char *a)
{
	int	fd[2];
	int	status;

	status = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, hd_signs);
	if (pipe(fd) == -1)
		printf("Error creating pipe\n");
	if (fork() == 0)
		hd_loop(a, fd);
	sig_actions();
	waitpid(0, &status, 0);
	close(fd[1]);
	return (fd[0]);
}

void	hd_loop(char *str, int *fd)
{
	char	*in;

	in = NULL;
	term_change();
	while (1)
	{
		write(0, ">", 1);
		in = get_next_line(0);
		if (!in && heredoc_error(str))
			break ;
		if ((ft_strncmp(in, str, ft_strlen(str)) == 0) && \
			(ft_strlen(in) - 1 == ft_strlen(str)))
			break ;
		if (in)
			in = check_expansion(in, 0);
		write(fd[1], in, ft_strlen(in));
		free(in);
		in = NULL;
	}
	close(fd[1]);
	close(fd[0]);
	exit(0);
}
