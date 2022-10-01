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

void	t_env_underscore_key_reset(t_env *env, char **args)
{
	t_env	*tmp;
	int		len;

	len = ft_arrlen(args);
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "_"))
		{
			tmp->value = ft_strreplace(tmp->value, args[len - 1]);
			return ;
		}
		tmp = tmp->next;
	}
}

void	t_env_underscore_key_reset2(t_env *env, char *str)
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

int	t_env_exit_status_reset(t_env *env, int exit_status)
{
	char	*new_value;
	t_env	*tmp;

	new_value = ft_lltoa(exit_status);
	errno = exit_status;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "?"))
		{
			tmp->value = ft_strreplace(tmp->value, new_value);
			free(new_value);
			return (exit_status);
		}
		tmp = tmp->next;
	}
	return (-1);
}
