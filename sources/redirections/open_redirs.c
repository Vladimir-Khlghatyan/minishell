/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:41:53 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:41:55 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_infile(t_data *d, char *filename, int fd_tmp)
{
	if (d->here_doc && d->inp->redir_is_last == 0)
	{
		fd_tmp = open(filename, O_RDONLY);
		if (fd_tmp == -1)
		{
			ft_putstr_fd("minishell: ", filename, ": ", 2);
			if (d->pipefds)
				free(d->pipefds);
			return (error_message(d->env, strerror(errno), NULL, 1));
		}
		close(fd_tmp);
		return (0);
	}
	if (d->fdin != -1)
		close(d->fdin);
	d->fdin = open(filename, O_RDONLY);
	if (d->fdin == -1)
	{
		ft_putstr_fd("minishell: ", filename, ": ", 2);
		if (d->pipefds)
			free(d->pipefds);
		return (error_message(d->env, strerror(errno), NULL, 1));
	}
	return (0);
}

int	ft_open_outfile_trunc_mode(t_data *d, char *filename)
{
	if (d->fdout != -1)
		close(d->fdout);
	d->fdout = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (d->fdout == -1)
	{
		ft_putstr_fd("minishell: ", filename, ": ", 2);
		if (d->pipefds)
			free(d->pipefds);
		return (error_message(d->env, strerror(errno), NULL, 1));
	}
	return (0);
}

int	ft_open_outfile_append_mode(t_data *d, char *filename)
{
	if (d->fdout != -1)
		close(d->fdout);
	d->fdout = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (d->fdout == -1)
	{
		ft_putstr_fd("minishell: ", filename, ": ", 2);
		if (d->pipefds)
			free(d->pipefds);
		return (error_message(d->env, strerror(errno), NULL, 1));
	}
	return (0);
}

int	ft_redirections(t_data *d)
{
	if (!ft_strcmp(d->inp->args[0], "<"))
		return (ft_open_infile(d, d->inp->args[1], -1));
	if (!ft_strcmp(d->inp->args[0], ">"))
		return (ft_open_outfile_trunc_mode(d, d->inp->args[1]));
	if (!ft_strcmp(d->inp->args[0], ">>"))
		return (ft_open_outfile_append_mode(d, d->inp->args[1]));
	return (0);
}

int	ft_open_redirs(t_data *d)
{
	t_inputs	*tmp;
	int			exit_status;

	exit_status = 0;
	tmp = d->inp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, REDIR))
		{
			exit_status = ft_redirections(d);
			t_inputs_del_node(&(d->inp), &tmp);
			if (exit_status)
				return (exit_status);
		}
		else
			return (0);
	}
	return (0);
}
