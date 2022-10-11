/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:41:32 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:41:35 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	t_env_print_flag_one_cnt(t_env *env)
{
	t_env	*tmp;
	int		cnt;

	cnt = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->print_flag == 1)
			cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}
