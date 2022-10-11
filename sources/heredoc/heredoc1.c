/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:36:42 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:36:44 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_and_close(char *buffer, int fd)
{
	free(buffer);
	close(fd);
}

void	here_doc_max_check(t_data *d)
{
	if (d->here_doc_cnt > 16)
	{
		error_message(d->env, ERR_HDMAX, NULL, 2);
		ft_inputsfree(d->inp);
		ft_envfree(d->env);
		free(d);
		exit (2);
	}
}

int	ft_here_doc_util_continue(t_data *d, char *buffer, int fd)
{
	ft_free_and_close(buffer, fd);
	d->fdin = open(".here_doc", O_RDONLY);
	if (d->fdin == -1)
		ft_unlink(".here_doc", d);
	if (d->fdin == -1)
		return (error_message(d->env, ERR_HEREDOC, NULL, 1));
	d->here_doc = 1;
	return (0);
}

void	ft_free_and_unlink_on_sigint(t_data *d)
{
	if (d->pipefds)
		free(d->pipefds);
	ft_unlink(".here_doc", d);
}
