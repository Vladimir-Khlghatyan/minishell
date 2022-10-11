/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:40:19 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:40:20 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// from parser_utils8.c //
void		t_inputs_redir_flags_set(t_inputs *inp);

static void	t_inputs_heredoc_limiter_add(t_inputs *inp)
{
	char	**new_args;

	while (inp)
	{
		if (!ft_strcmp(inp->type, REDIR))
		{
			new_args = (char **)malloc(sizeof(char *) * 3);
			new_args[0] = ft_strdup(inp->args[0]);
			if (inp->next == NULL)
			{
				new_args[1] = ft_strdup("newline");
				inp->type = ft_strreplace(inp->type, UNEXP);
			}
			else
				new_args[1] = ft_strdup(inp->next->args[0]);
			new_args[2] = NULL;
			ft_arrfree(inp->args);
			inp->args = new_args;
		}
		inp = inp->next;
	}
}

static void	t_inputs_heredoc_rename(t_inputs *inp)
{
	t_inputs	*tmp;

	tmp = inp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, REDIR) && \
			!ft_strcmp(tmp->args[0], "<<"))
			tmp->type = ft_strreplace(tmp->type, HEREDOC);
		tmp = tmp ->next;
	}
}

static void	t_inputs_cmd_join(t_inputs **head)
{
	t_inputs	*tmp;
	char		**tmp_args;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, CMD) && tmp->next && \
			!ft_strcmp(tmp->next->type, CMD))
		{
			tmp_args = ft_arrjoin(tmp->args, tmp->next->args);
			ft_arrfree(tmp->next->args);
			tmp->next->args = tmp_args;
			t_inputs_del_node(head, &tmp);
		}
		else
			tmp = tmp->next;
	}
}

static void	t_inputs_del_nulls(t_inputs **head)
{
	t_inputs	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->args == NULL)
			t_inputs_del_node(head, &tmp);
		else
			tmp = tmp->next;
	}
}

void	t_inputs_corrections(t_inputs *inp)
{
	t_inputs_heredoc_limiter_add(inp);
	t_inputs_heredoc_limiter_del(inp);
	t_inputs_del_nulls(&inp);
	t_inputs_replace_unexp_node(inp);
	t_inputs_heredoc_rename(inp);
	t_inputs_redir_flags_set(inp);
	t_inputs_tokens_sort(inp);
	t_inputs_cmd_join(&inp);
}
