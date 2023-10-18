/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:47:08 by eduarodr          #+#    #+#             */
/*   Updated: 2023/10/17 16:36:16 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../../minishell.h"

void	expansion(void);
int		check_expansion(char **token);
char 	*search_in_env(char *str, char **env);
char 	**get_expansion(char **token);
#endif