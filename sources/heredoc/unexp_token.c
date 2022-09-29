/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexp_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:36:58 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:36:59 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unexp_token_check(t_data *d)
{
	t_inputs	*tmp;

	tmp = d->inp;
	if (d->unexp_token)
	{
		while (tmp)
		{
			signal(SIGINT, handler_signals2);
			signal(SIGQUIT, SIG_IGN);
			if (!ft_strcmp(tmp->type, UNEXP) && !g_sigint_flag)
			{
				error_message(d->env, ERR_TOKEN, tmp->args[1], 258);
				break ;
			}
			else if (!ft_strcmp(tmp->type, HEREDOC) && !g_sigint_flag)
				here_doc(d, tmp->args[1]);
			tmp = tmp->next;
		}
	}
	ft_unlink(".here_doc", d);
	t_env_exit_status_reset(d->env, 258);
}
