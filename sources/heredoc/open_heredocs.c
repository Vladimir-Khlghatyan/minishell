/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:36:53 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:36:54 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_heredocs(t_data *d)
{
	t_inputs	*tmp;
	int			exit_status;

	exit_status = 0;
	tmp = d->inp;
	while (tmp)
	{
		if (g_sigint_flag == 0)
		{
			signal(SIGINT, handler_signals2);
			signal(SIGQUIT, SIG_IGN);
			if (!ft_strcmp(tmp->type, HEREDOC))
			{
				exit_status = here_doc(d, tmp->args[1]);
				t_inputs_del_node(&(d->inp), &tmp);
				if (exit_status)
					return (exit_status);
			}
			else
				return (0);
		}
		else
			return (1);
	}
	return (0);
}

int	ft_open_heredocs_for_proc(t_data *d, t_inputs **inp)
{
	int			exit_status;

	exit_status = 0;
	while (*inp)
	{
		if (g_sigint_flag == 0)
		{
			if (!ft_strcmp((*inp)->type, HEREDOC))
			{
				exit_status = here_doc(d, (*inp)->args[1]);
				t_inputs_del_node(&(d->inp), inp);
				if (exit_status)
					return (exit_status);
			}
			else
				return (0);
		}
		else
			return (1);
	}
	return (0);
}
