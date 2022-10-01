/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:42:26 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:42:27 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_unexp_token(t_inputs *inp)
{
	t_inputs	*tmp;

	tmp = inp;
	if (!inp)
		return (0);
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, UNEXP))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	ft_single_builtin(t_inputs *inp)
{
	t_inputs	*tmp;

	tmp = inp;
	if (!inp)
		return (0);
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, PIPE))
			return (0);
		tmp = tmp->next;
	}
	tmp = inp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, BUILTIN))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	ft_here_doc_cnt(t_inputs *inp)
{
	t_inputs	*tmp;
	int			here_doc_cnt;

	here_doc_cnt = 0;
	tmp = inp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, HEREDOC))
			here_doc_cnt++;
		tmp = tmp->next;
	}
	return (here_doc_cnt);
}

static int	ft_pipefd_cnt(t_inputs *inp)
{
	t_inputs	*tmp;
	int			pipefd_cnt;

	pipefd_cnt = 0;
	tmp = inp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, PIPE))
			pipefd_cnt++;
		tmp = tmp->next;
	}
	return (pipefd_cnt * 2);
}

void	t_data_update(t_data *d, t_env *env, t_inputs *inp)
{
	d->env = env;
	d->inp = inp;
	d->here_doc = 0;
	d->fdin = -1;
	d->fdout = -1;
	d->exit_flag = -1;
	d->pipefd_cnt = ft_pipefd_cnt(inp);
	d->proc_cnt = d->pipefd_cnt / 2 + 1;
	d->here_doc_cnt = ft_here_doc_cnt(inp);
	d->unexp_token = ft_unexp_token(inp);
	d->single_builin = ft_single_builtin(inp);
	g_sigint_flag = 0;
	d->pipefds = NULL;
}
