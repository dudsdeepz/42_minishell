/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:27:18 by eduarodr          #+#    #+#             */
/*   Updated: 2023/11/21 15:46:46 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	shell_output(char *av)
{
	char 	**splited;
	t_tokens *token;
	splited = NULL;
	if (ft_strlen(av) > 0)
	{
		splited = ft_split(av, '\2');
		token = ft_lstnewtoken(token_size(splited, 0));
		token = init_lists(splited, token);
		// executor(token);
		// if (splited[0] && splited)
		// 	free_matrix(splited);
	}
	else
		parser()->exit_status = 0;
	return (0);
}

int	tokens_num(char **cwd)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (cwd[i])
	{
		if (is_sign(cwd[i]) || !cwd[i + 1])
			
		i++;
	}
	return (count);
}

void	print_dp(char **str)
{
	int i;

	i = 0;
	while (str[i] != 0)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

t_tokens *init_lists(char **av, t_tokens *token)
{
	int i;
	int j;
	char **tmp;

	j = 0;	
	i = -1;
	tmp = NULL;
	while (av && av[++i])
	{
		if (av[i][0] == '|' || !av[i + 1])
		{
			ft_lstadd_token(&token, ft_lstnewtoken(j));
			token->token = dup_matrix(tmp);
			print_dp(token->token);	
			free_matrix(tmp);
			if (token->next)
				token = token->next;
			j = 0;
		}
		else if (options(av[i]))
			redirections(av, &i, token);
		else
			tmp[j++] = ft_strdup(check_expansion(av[i], 0));
	}
	return (0);
}

int	is_sign(char *sign)
{
	if (!ft_strncmp(sign, "|", 1))
		return (1);
	else if(!ft_strncmp(sign, ">>", 2))
		return (1);
	else if(!ft_strncmp(sign, "<<", 2))
		return (1);
	else if(!ft_strncmp(sign, ">", 1))
		return (1);
	else if(!ft_strncmp(sign, "<", 1))
		return (1);
	return (0);
}

int	separeites_tokens(t_tokens **tokens, char **splited)
{
	int i;
	int j;
	int exp_tmp;

	i = -1;
	j = 0;
	exp_tmp = 0;
	go_head(tokens);
	while (splited[++i])
	{
		if (!is_sign(splited[i]) && splited[i])
		{
			(*tokens)->token[j++] = check_expansion(splited[i], exp_tmp);
			if (!splited[i + 1])
				(*tokens)->token[j] = 0;
		}
		else
		{
			(*tokens)->token[j] = 0;
			j = 0;
			(*tokens) = (*tokens)->next;
		}
	}
	return (0);
}


// void	list_vars(t_tokens *tokens)
// {

// }



int token_size(char **splited, int i)
{
	while (splited[i] && splited[i][0] != '|')
		i++;
	return (1);
}