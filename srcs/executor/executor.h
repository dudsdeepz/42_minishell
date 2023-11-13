#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../../minishell.h"

void		executor(void);
void		p_heredoc(char *line);
int 		pipes(int tkid);
void		close_all(int *fd, int i, char *getp, char **comand);
void		argument(int *fd, char **av, int fd_type, int fd_num);
void		check_type(char **token, int tkid);
int 		redirections(int tkid, int i, char **av);
int			check_redir(char **av, int i);

#endif