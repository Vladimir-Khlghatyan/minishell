/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:34:10 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:34:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	t_env_print(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->print_flag == 1)
		{
			ft_putstr_fd(tmp->key, "=", tmp->value, 1);
			ft_putstr_fd("\n", NULL, NULL, 1);
		}
		tmp = tmp->next;
	}
}

int	builtin_env(t_data *d, char **args)
{
	if (ft_strcmp(args[0], "env"))
		return (0);
	t_env_underscore_key_reset(d->env, args);
	if (args[1] != NULL)
		return (error_message(d->env, ERR_ENV, d->inp->args[1], 127));
	t_env_print(d->env);
	t_env_exit_status_reset(d->env, 0);
	return (0);
}
