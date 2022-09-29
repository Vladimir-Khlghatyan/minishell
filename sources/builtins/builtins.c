/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:33:20 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:33:21 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(t_data *d, t_env **env, char **args, char *builtin)
{
	if (!ft_strcmp(builtin, "echo"))
		return (builtin_echo(d, args));
	if (!ft_strcmp(builtin, "env"))
		return (builtin_env(d, args));
	if (!ft_strcmp(builtin, "export"))
		return (builtin_export(d, args));
	if (!ft_strcmp(builtin, "pwd"))
		return (builtin_pwd(d, args));
	if (!ft_strcmp(builtin, "unset"))
		return (builtin_unset(d, env, args));
	if (!ft_strcmp(builtin, "cd"))
		return (builtin_cd(d, args));
	if (!ft_strcmp(builtin, "exit"))
		return (builtin_exit(d, args));
	return (0);
}

int	single_builtins(t_data *d, t_env **env)
{
	int	exit_status;
	int	fd_stdout;

	fd_stdout = dup(1);
	exit_status = ft_open_heredocs(d);
	if (exit_status == 0)
	{
		exit_status = ft_open_redirs(d);
		if (exit_status == 0)
		{
			if (d->fdin != -1)
				close(d->fdin);
			if (d->fdout != -1)
			{
				dup2(d->fdout, 1);
				close(d->fdout);
			}
			exit_status = builtins(d, env, d->inp->args, d->inp->args[0]);
			dup2(fd_stdout, 1);
			if (d->here_doc)
				ft_unlink(".here_doc", d);
			return (t_env_exit_status_reset(d->env, exit_status));
		}
	}
	return (t_env_exit_status_reset(d->env, exit_status));
}
