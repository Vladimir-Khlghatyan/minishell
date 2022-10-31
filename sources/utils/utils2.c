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

int	ft_empty_or_only_spaces_str(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}
