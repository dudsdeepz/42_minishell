/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 14:21:00 by by eduarodr       #+#    #+#             */
/*   Updated: 2023/10/18 11:02:06 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_prompt(char *av, char *newav)
{
	int		i;
	int		j;
	bool	s;

	s = false;
	i = -1;
	j = 0;
	while (av[++i])
	{
		if ((av[i] == '\"' || av[i] == '\''))
			s = !s;
		if (s == false && av[i] == ' ')
			av[i] = '\2';
		newav[j++] = av[i];
		if (s == false)
			j = parse_tokens(av, newav, &j, &i);
	}
	free(av);
	newav[j] = '\0';
	return (newav);
}

int	parsing(char *av)
{
	char	**parse;
	int		i;
	int		j;

	i = 0;
	j = 0;
	parse = ft_split(av, '\2');
	if (!ft_strncmp(parse[i], "|", 2))
		return (printf("Minishell: Syntax error!\n"));
	while (parse[i])
	{
		if (parse_tokens2(parse, &i))
		{
			printf("Minishell: Syntax error!\n");
			free_matrix(parse);
			return (0);
		}
		++i;
	}
	free_matrix(parse);
	return (1);
}

int	parse_tokens2(char **av, int *i)
{
	if ((!ft_strncmp(av[*i], "|", 2) || !ft_strncmp(av[*i], ">", 2) \
		|| !ft_strncmp(av[*i], "<", 2) || !ft_strncmp(av[*i], ">>", 2) || \
		!ft_strncmp(av[*i], "<<", 2)) && !av[(*i) + 1])
		return (1);
	if (!ft_strncmp(av[*i], "|", 2))
		if (av[(*i) + 1] && !ft_strncmp(av[(*i) + 1], "|", 2))
			return (1);
	if (!ft_strncmp(av[*i], ">", 2) || !ft_strncmp(av[*i], "<", 2))
		if (av[(*i) + 1] && (!ft_strncmp(av[(*i) + 1], ">", 2) || \
			!ft_strncmp(av[(*i) + 1], "<", 2)))
			return (1);
	if (!ft_strncmp(av[*i], ">>", 2) || !ft_strncmp(av[*i], "<<", 2))
		if (av[(*i) + 1] && (!ft_strncmp(av[(*i) + 1], ">>", 2) || \
			!ft_strncmp(av[(*i) + 1], "<<", 2)))
			return (1);
	return (0);
}
