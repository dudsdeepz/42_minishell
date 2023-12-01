/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:32:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 14:01:28 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	shell_aux(char **env)
{
	parser()->envp = dup_matrix(env);
	parser()->export_env = dup_matrix(env);
	parser()->was_redir = 0;
	parser()->exit_status = 0;
}

void	aux_shelloutput(t_tokens *token)
{
	if (token)
	{
		fds_caseclose(token);
		free_tokens(token);
	}
	free(parser()->exp_var);
}

void	aux_vars(void)
{
	parser()->pause = 0;
	parser()->tmp_matrix = NULL;
	parser()->free_stts = NULL;
	parser()->hd_free_2 = NULL;
	parser()->exp_var = NULL;
	parser()->pas_exp = 0;
	parser()->free_pas_ex = NULL;
}

void	builtins_close(t_tokens *tokens)
{
	close(1);
	fds_caseclose(tokens);
}

void	create_pipes(t_tokens *tokens)
{
	go_head(&tokens);
	while (tokens->next)
	{
		pipe(tokens->fd);
		tokens = tokens->next;
	}
}
