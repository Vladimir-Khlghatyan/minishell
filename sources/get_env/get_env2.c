/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:35:22 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:35:23 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*t_env_get_value_of_key(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	t_env_change_val_and_flag(t_env *env, char *key, char *nv, int nf)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			tmp->value = ft_strreplace(tmp->value, nv);
			tmp->print_flag = nf;
			break ;
		}
		tmp = tmp->next;
	}
}

void	t_env_init_shlvl_and_underscore(t_env *env, char *str)
{
	char	*value;
	char	*new_value;
	int		n;

	t_env_change_val_and_flag(env, "_", str, 1);
	value = t_env_get_value_of_key(env, "SHLVL");
	if (!value || !value[0])
		return ;
	n = ft_atoll(value);
	free (value);
	if (n == 999)
	{
		t_env_change_val_and_flag(env, "SHLVL", "", 1);
		return ;
	}
	n = ft_shlvl_max_check(n);
	new_value = ft_lltoa(n);
	t_env_change_val_and_flag(env, "SHLVL", new_value, 1);
	free(new_value);
}

void	t_env_init_oldpwd(t_env *env)
{
	t_env	*oldpwd_key;
	t_env	*tmp;

	oldpwd_key = env;
	while (oldpwd_key)
	{
		if (!ft_strcmp(oldpwd_key->key, "OLDPWD"))
			break ;
		oldpwd_key = oldpwd_key->next;
	}
	if (oldpwd_key)
		t_env_change_val_and_flag(env, "OLDPWD", "", 0);
	else
	{
		tmp = t_env_lstnew("OLDPWD=", 0);
		t_env_lstadd_back(&env, tmp);
	}
}
