/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:41:20 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:41:23 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes(t_data *d)
{
	int	i;

	if (d->pipefds)
		free(d->pipefds);
	d->pipefds = (int *)malloc(sizeof(int) * d->pipefd_cnt);
	if (!d->pipefds)
		return (t_env_exit_status_reset(d->env, 1));
	i = -1;
	while (++i < (d->pipefd_cnt) / 2)
	{
		if (pipe(&(d->pipefds[2 * i])) == -1)
		{
			free(d->pipefds);
			d->pipefds = NULL;
			return (t_env_exit_status_reset(d->env, 1));
		}
	}
	return (0);
}

void	ft_close_fdin_and_fdout(int *fdin, int *fdout)
{
	if (*fdin != -1)
	{
		close(*fdin);
		*fdin = -1;
	}
	if (*fdout != -1)
	{
		close(*fdout);
		*fdout = -1;
	}
}

int	exec_processes(t_data *d, int index)
{
	t_inputs	*tmp;
	int			cp;

	cp = create_pipes(d);
	if (cp)
		return (error_message(d->env, ERR_PIPE, NULL, cp));
	tmp = d->inp;
	while (tmp)
	{
		if (ft_open_heredocs_for_proc(d, &tmp))
			return (t_env_exit_status_reset(d->env, 1));
		if (ft_open_redirs_for_proc(d, &tmp))
			return (t_env_exit_status_reset(d->env, 1));
		call_process(d, ++index);
		if (d->fdin != -1 || d->fdout != -1)
			ft_close_fdin_and_fdout(&(d->fdin), &(d->fdout));
		if (d->here_doc)
			ft_unlink(".here_doc", d);
		while (tmp && ft_strcmp(tmp->type, PIPE))
			t_inputs_del_node(&(d->inp), &tmp);
		if (tmp && !ft_strcmp(tmp->type, PIPE))
			t_inputs_del_node(&(d->inp), &tmp);
	}
	close_pipes(d);
	return (0);
}

void	wait_for_children(t_data *d)
{
	int	i;
	int	stat_loc;
	int	exit_status;

	exit_status = 0;
	i = -1;
	while (++i < d->proc_cnt)
		wait(&stat_loc);
	if (WIFEXITED(stat_loc))
		exit_status = WEXITSTATUS(stat_loc);
	if (g_sigint_flag == 1)
		t_env_exit_status_reset(d->env, 1);
	else if (g_sigint_flag == 131)
		t_env_exit_status_reset(d->env, 131);
	else if (!(d->single_builin) && !(d->unexp_token))
		t_env_exit_status_reset(d->env, exit_status);
}
