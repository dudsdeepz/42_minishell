/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:20:06 by eduarodr          #+#    #+#             */
/*   Updated: 2023/12/01 15:21:09 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_all_hd(void)
{
	t_tokens	*tokens;

	tokens = parser()->head_token;
	while (tokens->prev)
	{
		tokens = tokens->prev;
		free_matrix(tokens->token);
		free(tokens->next);
	}
	free(tokens);
	clear_history();
	free(parser()->newav);
	free_envs();
	free_matrix(parser()->splited);
}

void	shell(char *cwd)
{
	char	*tmp;
	char	*newav;

	add_history(cwd);
	newav = malloc(ft_strlen(cwd) * 3);
	parser()->newav = newav;
	aux_vars();
	parser()->splited = NULL;
	tmp = get_prompt(cwd, newav);
	if (tmp)
		if (parsing(tmp))
			shell_output(tmp, NULL);
	free(tmp);
	tmp = NULL;
}

int	list_size(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}
