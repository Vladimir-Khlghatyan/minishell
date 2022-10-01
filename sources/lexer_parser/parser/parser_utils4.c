/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:40:14 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:40:15 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	t_inputs_check_tokens_sort(t_inputs *inp)
{
	t_inputs	*tmp;

	tmp = inp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, CMD) && tmp->next != NULL)
			if (ft_strcmp(tmp->next->type, CMD) && \
				ft_strcmp(tmp->next->type, PIPE))
				return (0);
		if (!ft_strcmp(tmp->type, REDIR) && tmp->next != NULL)
			if (ft_strcmp(tmp->next->type, REDIR) && \
				ft_strcmp(tmp->next->type, CMD) && \
				ft_strcmp(tmp->next->type, PIPE))
				return (0);
		tmp = tmp->next;
	}
	return (1);
}

static void	t_inputs_swap_nodes(t_inputs *node)
{
	char	**args_tmp;
	char	*type_tmp;
	int		redir_is_last_tmp;

	if (!node || !node->next)
		return ;
	args_tmp = node->args;
	type_tmp = node->type;
	redir_is_last_tmp = node->redir_is_last;
	node->args = node->next->args;
	node->type = node->next->type;
	node->redir_is_last = node->next->redir_is_last;
	node->next->args = args_tmp;
	node->next->type = type_tmp;
	node->next->redir_is_last = redir_is_last_tmp;
}

void	t_inputs_tokens_sort(t_inputs *inp)
{
	t_inputs	*tmp;

	while (!t_inputs_check_tokens_sort(inp))
	{
		tmp = inp;
		while (tmp)
		{
			if (!ft_strcmp(tmp->type, CMD) && tmp->next != NULL)
				if (ft_strcmp(tmp->next->type, CMD) && \
					ft_strcmp(tmp->next->type, PIPE))
					t_inputs_swap_nodes(tmp);
			if (!ft_strcmp(tmp->type, REDIR) && tmp->next != NULL)
				if (ft_strcmp(tmp->next->type, REDIR) && \
					ft_strcmp(tmp->next->type, CMD) && \
					ft_strcmp(tmp->next->type, PIPE))
					t_inputs_swap_nodes(tmp);
			tmp = tmp->next;
		}
	}
}
