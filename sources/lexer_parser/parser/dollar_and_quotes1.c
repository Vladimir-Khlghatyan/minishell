/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_quotes1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:38:57 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:38:58 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*t_env_get_key(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(key, "$?") && !ft_strcmp(tmp->key, key + 1))
			return (tmp->key);
		if (!ft_strcmp(tmp->key, key + 1) && tmp->print_flag == 1)
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*join_arr_to_str(char **arr)
{
	int		i;
	char	*str;

	str = NULL;
	if (!arr)
		return (NULL);
	i = -1;
	while (arr[++i])
		str = ft_strjoin_free(str, arr[i]);
	ft_arrfree(arr);
	return (str);
}

char	*ft_to_be_split(char *str)
{
	char	**arr;
	char	*new_str;
	int		i;

	arr = ft_split(str, ' ');
	new_str = ft_strdup(arr[0]);
	i = 0;
	while (arr[++i])
	{
		new_str = ft_strjoin_free(new_str, "to_be_split");
		new_str = ft_strjoin_free(new_str, arr[i]);
	}
	ft_arrfree(arr);
	free(str);
	return (new_str);
}

char	*check_and_replace_str1(t_env *env, char *str)
{
	char	*key;
	char	*value;

	if (str[0] != '$')
		return (str);
	key = t_env_get_key(env, str);
	if (!key)
		return (ft_strreplace(str, ""));
	value = t_env_get_value_of_key(env, key);
	str = ft_strreplace(str, value);
	free(value);
	return (str);
}

char	*check_and_replace_str2(t_env *env, char *str, int split_flag)
{
	char	*key;
	char	*value;

	if (str[0] != '$')
		return (str);
	key = t_env_get_key(env, str);
	if (!key)
		return (ft_strreplace(str, ""));
	value = t_env_get_value_of_key(env, key);
	if (split_flag)
		value = ft_to_be_split(value);
	str = ft_strreplace(str, value);
	free(value);
	return (str);
}
