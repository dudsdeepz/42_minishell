/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:47:08 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/20 12:33:57 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../../minishell.h"

void	expansion(void);
int		check_expansion(char *token);
char 	*search_in_env(char *str, char **env);
char 	*get_expansion(char *token);
int		expansion_wc(char *str);
int 	fk_quotes(char *token, int i);
char 	*join_all(char **token);
int		check_sign(char *str, char c);
char 	*quote_killa(char *str);
int		quote_n(char *str);
int 	expansion_size(char *str);

#endif