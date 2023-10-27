/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:26:46 by diomari           #+#    #+#             */
/*   Updated: 2023/10/26 17:50:58 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executor(void)
{
	int i;

	i = 0;
	while (i < parser()->tokens_n)
	{
		// print_dp(parser()->tokens[i].token);
		if (!(check_cmds(parser()->tokens[i].token)))
			exec_system_cmd(parser()->tokens[i].token, parser()->envp, i);
		i++;
	}
}

void p_heredoc(char *line)
{
	char *new_content;

	new_content = malloc(ft_strlen(parser()->heredoc->h_content) + ft_strlen(line) + 2);
	ft_strcpy(new_content, parser()->heredoc->h_content);
	ft_strcat(new_content, line);
	ft_strcat(new_content, "\n");
	free(parser()->heredoc->h_content);
	parser()->heredoc->h_content = new_content;
}