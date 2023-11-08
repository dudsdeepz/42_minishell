/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:29:53 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/08 11:48:46 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../../minishell.h"

void    display_export(char **env);
void	ft_cd(char **av);
int		print_pwd(char *av);
void	display_env(char **env);
void	ft_echo(char **av);
void	ft_export(char **av);
void	ft_unset(char **av);
int 	check_export_str(char *str);
char	**send_to_exportenv(char *token, char **env);
char	**send_to_env(char *token, char **env, char *find);
char 	**new_env(char *token, char **env, char *find);
char	*oldpwd_aux(char *token);
char 	**new_env_unset(char *token, char **env);
void 	n_case(char **av);
int 	check_exit_str(char *str);
void	unset_uti(char *str);
void 	export_util(char *str, char **tmp);

#endif
