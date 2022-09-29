/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:34:43 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:34:46 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*t_env_get_key_for_print(t_env *env, char *key, int *print_flag)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			*print_flag = tmp->print_flag;
			return (tmp->key);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*t_env_get_value_for_print(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	sort_array(char **array)
{
	char	*temp;
	int		len;
	int		i;

	len = ft_arrlen(array);
	while (len > 0)
	{
		i = -1;
		while (++i < len - 1)
		{	
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{	
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
		len--;
	}
}

static char	**keys_to_array_and_sort(t_env *env)
{
	int		i;
	char	**array;
	t_env	*tmp;

	tmp = env;
	array = (char **)malloc(sizeof(char *) * (t_env_len(env) + 1));
	if (!array)
		return (NULL);
	i = -1;
	while (tmp)
	{
		array[++i] = ft_strdup(tmp->key);
		tmp = tmp->next;
	}
	array[i + 1] = NULL;
	sort_array(array);
	return (array);
}

void	t_env_print_sorted(t_env *env, int i)
{
	char	**arr;
	char	*key;
	char	*value;
	int		print_flag;

	arr = keys_to_array_and_sort(env);
	print_flag = 0;
	while (arr[i])
	{
		key = t_env_get_key_for_print(env, arr[i], &print_flag);
		value = t_env_get_value_for_print(env, arr[i]);
		if (key && print_flag && ft_strcmp(key, "_"))
		{
			ft_putstr_fd("declare -x ", arr[i], NULL, 1);
			if (value)
				ft_putstr_fd("=\"", value, "\"\n", 1);
			else
				ft_putstr_fd("\n", NULL, NULL, 1);
		}
		i++;
	}
	ft_arrfree(arr);
}
