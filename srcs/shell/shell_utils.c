/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/06 16:50:05 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_tokens(char *av)
{
	int		i;
	int		a;
	int		j;
	char 	*str;

	i = 0;
	a = 0;
	j = 0;
	free_tokens();
	parser()->tokens_n = tokens_num(av);
	parser()->tokens = malloc(sizeof(t_tokens) * tokens_num(av));
	while (av[i] != '\0')
	{
		i++;
		if (av[i] == '|' || av[i] == '>' || av[i] == '<' || !av[i])
		{
			str = ft_subtokens(av, a, i - a);
			parser()->tokens[j].token =	ft_split(str, '\2');
			free (str);
			parser()->tokens[j].token_id = j + 1;
			a = i + 1;
			j++;
		}
	}
}

int	tokens_num(char *cwd)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (cwd[i])
	{
		if (cwd[i] == '|' || cwd[i] == '>')
			i++;
		while (!(cwd[i] == '|' || cwd[i] == '>') && cwd[i])
				i++;
		count++;
		}
	return (count);
}

void	print_dp(char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			write(1, &str[i][j], 1);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

void free_tokens(void)
{
	int i;

	i = -1;
	if (parser()->tokens)
	{
		while (++i < parser()->tokens_n)
			free_matrix(parser()->tokens[i].token);
		free(parser()->tokens);
	}
}