/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:34:55 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:34:56 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_set_directory(t_env *env)
{
	char	*underscore;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "_"))
		{
			underscore = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
			return (ft_strjoin(tmp->value, underscore));
		tmp = tmp->next;
	}
	return (NULL);
}

int	builtin_pwd(t_data *d, char **args)
{
	char	*directory;

	if (ft_strcmp(args[0], "pwd"))
		return (0);
	directory = getcwd(NULL, 0);
	if (!directory)
		directory = ft_set_directory(d->env);
	t_env_underscore_key_reset(d->env, args);
	ft_putstr_fd(directory, "\n", NULL, 1);
	t_env_exit_status_reset(d->env, 0);
	free(directory);
	return (0);
}
