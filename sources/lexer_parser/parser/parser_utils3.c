/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:40:08 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:40:10 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// from parser_utils8.c //
char		**ft_unxep_token_util(char **args);

static int	check_unexp_token_in_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[0] == '|' || str[0] == '<' || str[0] == '>')
			return (1);
	}
	return (0);
}

static int	check_unexp_token_in_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (check_unexp_token_in_str(arr[i]))
			return (1);
	}
	return (0);
}

static char	**replase_arr(char *str)
{
	char	**arr;
	int		i;

	arr = (char **)malloc(sizeof(char *) * 3);
	if (!arr)
		return (NULL);
	if ((str[1] && str[1] == ' ') || !ft_strcmp(str, "||"))
		i = 1;
	else
		i = 2;
	arr[0] = ft_substr(str, 0, i);
	while (str[i] == ' ')
		i++;
	if (str[i] && str[i] == '|')
		arr[1] = ft_substr(str, i, 1);
	else
		arr[1] = ft_substr(str, i, 2);
	arr[2] = NULL;
	return (arr);
}

static int	t_inputs_if_begins_or_ends_with_pipe(t_inputs **head)
{
	t_inputs	*tmp;
	t_inputs	*last;
	char		**new_args;

	last = *head;
	while (last && last->next)
		last = last->next;
	if ((*head && !ft_strcmp((*head)->type, PIPE)) || \
		(last && !ft_strcmp(last->type, PIPE)))
	{
		new_args = (char **)malloc(sizeof(char *) * 3);
		new_args[0] = ft_strdup("|");
		new_args[1] = ft_strdup("|");
		new_args[2] = NULL;
		if (!ft_strcmp((*head)->type, PIPE))
			tmp = *head;
		else
			tmp = last;
		ft_arrfree(tmp->args);
		tmp->args = new_args;
		tmp->type = ft_strreplace(tmp->type, UNEXP);
		return (1);
	}
	return (0);
}

void	t_inputs_replace_unexp_node(t_inputs *inp)
{
	int		i;
	char	**new_args;

	if (t_inputs_if_begins_or_ends_with_pipe(&inp))
		return ;
	while (inp)
	{
		if (!ft_strcmp(inp->type, CMD) && \
			check_unexp_token_in_arr(inp->args))
		{
			i = 0;
			while (!check_unexp_token_in_str(inp->args[i]))
				i++;
			new_args = replase_arr(inp->args[i]);
			new_args = ft_unxep_token_util(new_args);
			ft_arrfree(inp->args);
			inp->args = new_args;
			inp->type = ft_strreplace(inp->type, UNEXP);
			break ;
		}
		inp = inp->next;
	}
}
