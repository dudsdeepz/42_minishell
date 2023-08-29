/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:49 by eduarodr          #+#    #+#             */
/*   Updated: 2023/08/28 16:26:15 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	args[BUFFER_SIZE];

	(void)av;
	tokens()->envp = env;
	if (ac == 1)
	{
		init_shell();
		sig_actions();
		while (1)
		{
			if (loop_pwd(args))
				continue ;
			cmd_parsing(args, ac);
		}
	}
	return (0);
}
