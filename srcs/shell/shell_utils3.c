/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:32:35 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/26 13:34:02 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    shell_aux(char **env)
{
	parser()->envp = dup_matrix(env);
	parser()->export_env = dup_matrix(env);
	parser()->was_hd = 0;
}
