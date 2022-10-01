/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:36:47 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:36:48 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* from heredoc1.c */
int		ft_here_doc_util_continue(t_data *d, char *buffer, int fd);
void	ft_free_and_unlink_on_sigint(t_data *d);

void	ft_unlink(char *str, t_data *d)
{
	if (d->fdin != -1)
		close (d->fdin);
	d->fdin = -1;
	unlink(str);
	d->here_doc = 0;
}

static char	*ft_dollar_handle_in_hd(t_data *d, char *str, int flag)
{
	char	**tmp;
	int		i;

	if (flag == 0)
		return (str);
	tmp = ft_split_dollar(str, 0, -1);
	i = -1;
	while (tmp[++i])
			tmp[i] = check_and_replace_str2(d->env, tmp[i], 0);
	free(str);
	str = join_arr_to_str(tmp);
	return (str);
}

static int	here_doc_util(t_data *d, char *limiter, int hdflag)
{
	int		fd;
	char	*buffer;

	if (d->here_doc)
		ft_unlink(".here_doc", d);
	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (error_message(d->env, ERR_HEREDOC, NULL, 1));
	while (1)
	{
		signal(SIGINT, handler_signals2);
		signal(SIGQUIT, SIG_IGN);
		if (g_sigint_flag == 1)
		{
			ft_free_and_unlink_on_sigint(d);
			return (1);
		}
		buffer = readline("heredoc>");
		if (!buffer || !ft_strcmp(limiter, buffer))
			break ;
		buffer = ft_dollar_handle_in_hd(d, buffer, hdflag);
		ft_putstr_fd(buffer, "\n", NULL, fd);
		free(buffer);
	}
	return (ft_here_doc_util_continue(d, buffer, fd));
}

int	here_doc(t_data *d, char *limiter)
{
	int	exit_status;

	exit_status = here_doc_util(d, limiter, d->inp->quote_in_hd_limiter);
	if (!exit_status)
		t_env_exit_status_reset(d->env, 0);
	return (exit_status);
}
