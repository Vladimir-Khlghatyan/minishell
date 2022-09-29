/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:39:59 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:40:00 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	t_inputs_check_if_operator(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "|"))
		return (1);
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, ">") || \
		!ft_strcmp(str, "<<") || !ft_strcmp(str, ">>"))
		return (2);
	return (0);
}

static char	*t_inputs_type(int n)
{
	if (n == 1)
		return (ft_strdup(PIPE));
	if (n == 2)
		return (ft_strdup(REDIR));
	return (NULL);
}

void	t_inputs_fill_new_nod(t_inputs *new, char **toks, int *i, int len)
{
	int	j;

	j = 0;
	if (t_inputs_check_if_operator(toks[(*i)]))
	{
		(new->args) = (char **)malloc(sizeof(char *) * 2);
		(new->args)[0] = ft_strdup(toks[*i]);
		(new->args)[1] = NULL;
		new->type = t_inputs_type(t_inputs_check_if_operator(toks[(*i)]));
		(*i)++;
	}
	else
	{
		while (toks[(*i)] && !t_inputs_check_if_operator(toks[(*i)]))
		{
			(*i)++;
			len++;
		}
		new->args = (char **)malloc(sizeof(char *) * (len + 1));
		(new->args)[len] = NULL;
		while ((--len >= 0) && ++j)
			(new->args)[len] = ft_strdup(toks[*i - j]);
		new->type = ft_strdup(CMD);
	}
}
