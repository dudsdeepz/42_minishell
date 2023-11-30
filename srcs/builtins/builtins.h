/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:29:53 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/30 12:11:03 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../../minishell.h"
# define IS_FILE 10

void	display_export(char **env);
void	_ft_cd(t_tokens **token);
void	_ft_pwd(t_tokens **token);
void	_ft_env(t_tokens **token);
void	_ft_exit(t_tokens **token);
void	_ft_echo(t_tokens **token);
void	_ft_export(t_tokens **token);
void	_ft_unset(t_tokens **token);
int		check_export_str(char *str);
char	**send_to_exportenv(char *token, char **env);
char	**send_to_env(char **env, char *find);
char	**new_env(char **env, char *find);
char	*oldpwd_aux(char *token);
char	**new_env_unset(char *token, char **env);
int		n_case(char *flag);
int		check_exit_str(char *str);
void	unset_uti(char *str);
void	export_util(char *str);
int		ft_path(char **tokens, t_tokens *token);
void	ft_cmds(t_tokens *token);
void	_ft_exec_cmd(t_tokens **token);
int		search_envvar(char *str);
char	**env_help(char **env, char *find);
char	*aux_envi(char *env, char *find);
int		cd_errors(char **token);

#endif
