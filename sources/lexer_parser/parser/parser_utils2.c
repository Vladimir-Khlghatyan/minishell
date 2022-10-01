/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:40:04 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:40:05 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	t_inputs_free_node(t_inputs *node)
{
	if (node->args)
		ft_arrfree(node->args);
	node->args = NULL;
	if (node->type)
		free(node->type);
	node->type = NULL;
	node->prev = NULL;
	node->next = NULL;
	free(node);
}

static char	**del_first_string_from_arr(char **arr)
{
	char	**new_arr;
	int		i;
	int		len;

	if (!arr)
		return (NULL);
	len = ft_arrlen(arr);
	if (len == 1)
	{
		ft_arrfree(arr);
		return (NULL);
	}
	new_arr = (char **)malloc(sizeof(char *) * len);
	i = 0;
	while (arr[++i])
		new_arr[i - 1] = ft_strdup(arr[i]);
	new_arr[i - 1] = NULL;
	ft_arrfree(arr);
	return (new_arr);
}

void	t_inputs_heredoc_limiter_del(t_inputs *inp)
{
	while (inp)
	{
		if (!ft_strcmp(inp->type, CMD))
			if (inp->prev && !ft_strcmp(inp->prev->type, REDIR))
				inp->args = del_first_string_from_arr(inp->args);
		inp = inp->next;
	}
}

void	t_inputs_del_node(t_inputs **head, t_inputs **node)
{
	t_inputs	*remember;

	if (*node == NULL)
		return ;
	if (*node == *head)
		*head = (*head)->next;
	remember = *node;
	if ((*node)->next != NULL)
		(*node)->next->prev = (*node)->prev;
	if ((*node)->prev != NULL)
		(*node)->prev->next = (*node)->next;
	*node = (*node)->next;
	t_inputs_free_node(remember);
}
