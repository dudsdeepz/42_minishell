/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 14:21:00 by by eduarodr       #+#    #+#             */
/*   Updated: 2023/12/01 10:29:21 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	prompt_aux(bool *s, char i)
{
	(*s) = !(*s);
	return (i);
}

char	*get_prompt(char *av, char *newav)
{
	int		i;
	int		j;
	bool	s;
	char	tmp;

	s = false;
	i = -1;
	j = 0;
	tmp = 0;
	while (av[++i])
	{
		if ((av[i] == '\"' || av[i] == '\''))
		{
			if ((tmp == av[i]) || !tmp)
				tmp = prompt_aux(&s, av[i]);
		}
		if (s == false && (av[i] == ' ' || av[i] == '\t'))
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

	i = 0;
	parse = ft_split(av, '\2');
	if (parse[i] && !ft_strncmp(parse[i], "|", 2))
	{
		printf("Minishell: Syntax error!\n");
		free_matrix(parse);
		return (0);
	}
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

static int	check_tokens2(char **av, int *i)
{
	if ((!ft_strncmp(av[*i + 1], "|", 1) || \
		!ft_strncmp(av[*i + 1], ">>", 2) \
		|| !ft_strncmp(av[*i + 1], "<<", 2)))
		return (1);
	return (0);
}

int	parse_tokens2(char **av, int *i)
{
	if ((!ft_strncmp(av[*i], "|", 1) || !ft_strncmp(av[*i], ">", 1) \
		|| !ft_strncmp(av[*i], "<", 1) || !ft_strncmp(av[*i], ">>", 2) || \
		!ft_strncmp(av[*i], "<<", 2)) && (!av[*i + 1] || \
		(check_tokens2(av, i))))
		return (1);
	if (!ft_strncmp(av[*i], "|", 2))
		if (av[(*i) + 1] && !ft_strncmp(av[(*i) + 1], "|", 2))
			return (1);
	if (!ft_strncmp(av[*i], ">>", 2) || !ft_strncmp(av[*i], "<<", 2))
		if (av[(*i) + 1] && (!ft_strncmp(av[(*i) + 1], ">>", 2) || \
			!ft_strncmp(av[(*i) + 1], "<<", 2)))
			return (1);
	if (!ft_strncmp(av[*i], ">", 1) || !ft_strncmp(av[*i], "<", 1))
		if (av[(*i) + 1] && (!ft_strncmp(av[(*i) + 1], ">", 1) || \
			!ft_strncmp(av[(*i) + 1], "<", 1)))
			return (1);
	return (0);
}
