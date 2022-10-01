/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:39:52 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:39:53 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_inputs	*t_inputs_lstnew(char **tokens, int *i)
{
	t_inputs	*new_node;

	new_node = (t_inputs *)malloc(sizeof(t_inputs));
	if (!new_node || !tokens[(*i)])
		return (NULL);
	t_inputs_fill_new_nod(new_node, tokens, i, 0);
	new_node->quote_in_hd_limiter = 0;
	new_node->redir_is_last = 0;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_inputs	*t_inputs_lstlast(t_inputs *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static void	t_inputs_lstadd_back(t_inputs **lst, t_inputs *new)
{
	t_inputs	*last_element;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last_element = t_inputs_lstlast(*lst);
	last_element->next = new;
	new->prev = last_element;
}

t_inputs	*parser(t_env *env, char **tokens)
{
	t_inputs	*tmp;
	t_inputs	*inp;
	int			i;

	inp = NULL;
	i = 0;
	if (!tokens)
		return (NULL);
	while (tokens[i])
	{
		tmp = t_inputs_lstnew(tokens, &i);
		t_inputs_lstadd_back(&inp, tmp);
	}
	ft_arrfree(tokens);
	t_inputs_corrections(inp);
	t_inputs_dollar_sign_handler(env, inp);
	t_inputs_builtin_types_set(inp);
	t_inputs_hd_limiter_parse(inp);
	return (inp);
}
