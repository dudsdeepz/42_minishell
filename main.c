/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:49 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/25 21:36:11 by eduarodr         ###   ########.fr       */
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
		parser()->envp = dup_matrix(env);
		parser()->export_env = dup_matrix(env);
		parser()->was_hd = 0;
		sig_actions();
		while (1)
		{
			parser()->pause = 0;
			cwd = readline("minishell: ");
			if (!cwd)
				return (0);
			if (ft_strlen(cwd) > 0)
			{
				add_history(cwd);
				shell(cwd);
			}
			else
				free(cwd);
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

	parser()->tmp_matrix = NULL;
	parser()->free_stts = NULL;
	parser()->hd_free_2 = NULL;
	parser()->exp_var = NULL;
	tmp = get_prompt(cwd, malloc(ft_strlen(cwd) * 5));
	if (tmp)
		if (parsing(tmp))
			shell_output(tmp);
	if (parser()->was_hd)
	{
		free_matrix(parser()->hd_free_2);
		parser()->was_hd = !parser()->was_hd;
	}
	free(tmp);
	tmp = NULL;
}

int	ft_heredoc(char *a)
{
	int	fd[2];
	int	status;

	status = 0;
	parser()->hd_free = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, hd_signs);
	parser()->hd = 1;
	if (pipe(fd) == -1)
		printf("Error creating pipe\n");
	a = remove_quotes(a);
	if (fork() == 0)
		hd_loop(a, fd);
	free(a);
	sig_actions();
	waitpid(0, &status, 0);
	close(fd[1]);
	parser()->hd = 0;
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
		if (in)
			in = check_expansion(in, 0);
		if ((ft_strncmp(in, str, ft_strlen(str)) == 0) && \
			(ft_strlen(in) - 1 == ft_strlen(str)) && !check_dq(in))
			break ;
		write(fd[1], in, ft_strlen(in));
		free(in);
		in = NULL;
	}
	close(fd[1]);
	close(fd[0]);
	exit(0);
}
