/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:44:40 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:44:41 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_there_is_pipe(t_inputs *inp)
{
	t_inputs	*tmp;

	tmp = inp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, PIPE))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	t_env_underscore_key_reset_util(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "_"))
		{
			tmp->value = ft_strreplace(tmp->value, str);
			return ;
		}
		tmp = tmp->next;
	}
}

void	t_env_underscore_key_reset(t_data *d)
{
	t_inputs	*tmp;

	tmp = d->inp;
	if (d->unexp_token)
		return ;
	if (d->single_builin)
		t_env_underscore_key_reset_util(d->env, \
			d->inp->args[ft_arrlen(d->inp->args) - 1]);
	else if (ft_there_is_pipe(d->inp) == 1)
		t_env_underscore_key_reset_util(d->env, "");
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (ft_strcmp(tmp->type, CMD))
			t_env_underscore_key_reset_util(d->env, "");
		else
			t_env_underscore_key_reset_util(d->env, \
				tmp->args[ft_arrlen(tmp->args) - 1]);
	}
}
