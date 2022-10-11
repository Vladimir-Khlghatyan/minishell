/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs_for_proc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:41:59 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:42:00 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* from open_redirs.c */
int	ft_open_infile(t_data *d, char *filename, int fd_tmp);
int	ft_open_outfile_trunc_mode(t_data *d, char *filename);
int	ft_open_outfile_append_mode(t_data *d, char *filename);
int	ft_redirections(t_data *d);

int	ft_open_redirs_for_proc(t_data *d, t_inputs **inp)
{
	int			exit_status;

	exit_status = 0;
	while (*inp)
	{
		if (g_sigint_flag == 0)
		{
			if (!ft_strcmp((*inp)->type, REDIR))
			{
				exit_status = ft_redirections(d);
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
