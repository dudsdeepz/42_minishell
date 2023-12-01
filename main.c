/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:49 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 15:21:18 by eduarodr         ###   ########.fr       */
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
		shell_aux(env);
		sig_actions();
		while (1)
		{
			cwd = readline("minishell> ");
			if (!cwd)
			{
				free_aux(cwd);
				return (0);
			}
			if (ft_strlen(cwd) > 0)
				shell(cwd);
			else
				free(cwd);
		}
	}
	else
		ft_putstr_fd("too many arguments!\n", STDERR_FILENO);
	return (0);
}

int	ft_heredoc(char *a)
{
	int	status;
	int	flag;

	flag = 0;
	status = 0;
	parser()->pas_exp = 0;
	parser()->hd_free = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, hd_signs);
	parser()->hd = 1;
	if (pipe(parser()->hd_fd) == -1)
		printf("Error creating pipe\n");
	if (fork() == 0)
		hd_loop(a, parser()->hd_fd, flag);
	sig_actions();
	waitpid(0, &status, 0);
	parser()->hd = 0;
	close(parser()->hd_fd[1]);
	return (parser()->hd_fd[0]);
}

void	hd_loop(char *str, int *fd, int flag)
{
	char	*in;

	in = NULL;
	term_change();
	str = remove_quotes(str);
	while (1)
	{
		write(0, ">", 1);
		in = get_next_line(0);
		if (!in && heredoc_error(str))
			break ;
		if (in && !flag)
			in = check_expansion(in, 0);
		if ((ft_strncmp(in, str, ft_strlen(str)) == 0) && \
			(ft_strlen(in) - 1 == ft_strlen(str)))
			break ;
		write(fd[1], in, ft_strlen(in));
		free(in);
		in = NULL;
	}
	free(str);
	free_all_hd();
	close(fd[1]);
	close(fd[0]);
	exit(0);
}
