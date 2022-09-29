/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:41:32 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:41:35 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_fdin(t_data *d)
{
	dup2(d->fdin, 0);
	close(d->fdin);
	d->fdin = -1;
}

void	ft_change_fdout(t_data *d)
{
	dup2(d->fdout, 1);
	close(d->fdout);
	d->fdout = -1;
}

void	ft_call_exeve(t_data *d)
{
	d->path_arr = get_path(d);
	d->cmd = check_cmd(d->path_arr, d->inp->args[0]);
	if (d->cmd == NULL)
		exit(error_message(d->env, ERR_CMD, d->inp->args[0], 127));
	d->env_arr = t_env_to_array(d->env);
	if (execve(d->cmd, d->inp->args, d->env_arr) == -1)
		exit(1);
}

void	call_process(t_data *d, int index)
{
	d->pid = fork();
	if (d->pid == -1)
		exit(error_message(d->env, ERR_FORK, NULL, 1));
	if (d->pid == 0)
	{
		if (d->fdin != -1)
			ft_change_fdin(d);
		else if (index != 0)
			dup2(d->pipefds[2 * index - 2], 0);
		if (d->fdout != -1)
			ft_change_fdout(d);
		else if (index != d->proc_cnt - 1)
			dup2(d->pipefds[2 * index + 1], 1);
		close_pipes(d);
		if (!d || !ft_strcmp(d->inp->type, PIPE))
			exit(0);
		else if (!ft_strcmp(d->inp->type, BUILTIN))
			exit(builtins(d, &(d->env), d->inp->args, d->inp->args[0]));
		else
			ft_call_exeve(d);
	}
}
