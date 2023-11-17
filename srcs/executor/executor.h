#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../../minishell.h"
# define REDIR_COMAND 1
# define PIPE_COMMAND 2

void	executor(t_tokens *tokens);
void	p_heredoc(char *line);
int 	pipes(int tkid);
int 	redirections(t_tokens *tokens);
void 	close_fds(t_tokens *tokens, int all);
void	create_pipes(t_tokens **tokens);
void	kawasaki(t_tokens *tokens);
void	ft_exec(char **token);
void 	kricko(t_tokens *tokens);
int		lstsize_tokens(t_tokens *lst);
void	estriper(t_tokens *tokens);
t_tokens	*lstlast_tokens(t_tokens *lst);
void 	ft_dup2(int input, int output);
int		check_double_red(char *av, int i);
int 	get_sign(t_tokens *tokens, int i, char *av);
int	    stokens_num(char **cwd, char *sign);
int	    total_tokens_size(t_tokens **tokens);

#endif