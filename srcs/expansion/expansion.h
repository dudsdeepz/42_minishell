/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:47:08 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/25 19:56:09 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../../minishell.h"

char	*check_expansion(char *token, int tmp);
char	*search_env(char *str, char **env);
char	*get_expansion(char *token, int *i);
int		fk_quotes(char *token, int i);
char	*join_all(char **token);
int		check_sign(char *str, char c);
char	*remove_quotes(char *str);
int		quote_n(char *str);
int		fe_sign(char *str);
char	*exp_token(char *token, char *str, int i, int a);
int		difs(char *sign, char c);
int		*synt(void);
char	*free_da_str(char *str);
int		check_dq(char *str);
void	go_head(t_tokens **lst);
int		dq_aux(char *str, int i);
void	get_stts_utils(char *str, int i, char *val, char **res);
#endif
