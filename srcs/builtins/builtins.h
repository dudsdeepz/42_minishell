/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:29:53 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/31 15:43:55 by eduarodr         ###   ########.fr       */
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
int 	ft_echo_cases(char **av);
void	ft_export(char **av);
void	ft_unset(char **av);
int 	check_export_str(char *str);
char	**send_to_exportenv(char *token, char **env);
char	**send_to_env(char *token, char **env, char *find, char **freed);
char 	**new_env(char *token, char **env, char *find);
char	*oldpwd_aux(char *token);
char 	**new_env_unset(char *token, char **env);

#endif