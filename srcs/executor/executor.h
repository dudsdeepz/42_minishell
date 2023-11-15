#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../../minishell.h"

void		executor(void);
void		p_heredoc(char *line);
int 		pipes(int tkid);
void		close_all(int *fd, int i, char *getp, char **comand);
void		argument(int *fd, char **av, int fd_num, int fd_type);
int 		redirections(int tkid, char *av);
int			check_redir(char **av, int i);
void		exec_system_cmd(char **tokens);
void 		one_command(int i);
void 		close_fds();
int			check_cmds_(char **linei);
int			signs(char *sign, int tkid);
void 		ft_dup(int *fd, int open, int closee, int fd_type);
void		create_pipes(void);

#endif