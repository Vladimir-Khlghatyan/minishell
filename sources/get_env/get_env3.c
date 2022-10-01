/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:35:22 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:35:23 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_progpath_key_value(void)
{
	char	*current_path;
	char	*key_value;

	current_path = getcwd(NULL, 0);
	current_path = ft_strjoin_free(current_path, "/minishell");
	key_value = ft_strjoin("PROGPATH=", current_path);
	free(current_path);
	return (key_value);
}

char	*t_env_progpath(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PROGPATH"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
