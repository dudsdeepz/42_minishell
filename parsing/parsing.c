/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.4\2.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: \20\23/09/01 14:\21:13 by eduarodr          #+#    #+#             */
/*   Updated: \20\23/10/04 18:01:44 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char 	*get_prompt(char *av, char *newav)
{
	int		i;
	int 	j;
	bool 	s;

	s = false;
	i = -1;
	j = 0;
	while (av[++i])
	{
		if ((av[i] == '\"' || av[i] == '\''))
		{
			s = !s;
			av[i] = '\1';
		}
		if (s == false && av[i] == ' ')
			av[i] = '\2';
		newav[j++] = av[i];
		if (s == false)
			j = check_pipe(av, newav, &j, &i);
	}
	free(av);
	newav[j] = 0;
	return (newav);
}

int	parsing(char *av)
{
	char **parse;
	int i;
	int j;

	i = -1;
	j = 0;
	parse = ft_split(av, '\2');
	while (parse[++i])
		printf("%s\n", parse[i]);
	i = 0;
	while (parse[++i])
	{
		if (parse[i][j] == '|' && parse[i][j + 1] == '|')
			return (printf("minishell: syntax error!"));
	}
	return (1);
}

