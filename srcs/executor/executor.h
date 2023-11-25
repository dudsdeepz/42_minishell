/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:13:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/25 21:58:53 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../minishell.h"
# define REDIR_COMAND 1
# define PIPE_COMMAND 2

void	executor(t_tokens **tokens);
int		redirections(char **str, int i, t_tokens *tokens);
void	close_fds(t_tokens **tokens, int all);
void	exec_start(t_tokens *tokens);
void	exec_doit(t_tokens *tokens);
int		lstsize_tokens(t_tokens *lst);
int		check_double_red(char *av, int i);
int		total_tokens_size(t_tokens **tokens);
void	invalid_fds(t_tokens *token);
void	fds_caseclose(t_tokens *token);

#endif