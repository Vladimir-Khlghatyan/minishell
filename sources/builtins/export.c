/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:34:32 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:34:33 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_env_print_sorted(t_env *env, int i);

static int	is_valid_identifier(char *s)
{
	int	i;

	if (!s)
		return (0);
	if (s[0] && ((s[0] >= 'A' && s[0] <= 'Z') || \
			(s[0] >= 'a' && s[0] <= 'z') || s[0] == '_'))
	{	
		i = 1;
		while (s[i] && ((s[i] >= 'A' && s[i] <= 'Z') || \
			(s[i] >= 'a' && s[i] <= 'z') || \
			(s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
			i++;
		if (s[i] == '=')
			return (1);
		if (s[i] == '\0')
			return (2);
	}
	return (0);
}

static int	t_env_key_reset(t_env *env, char *str)
{
	t_env	*tmp;
	char	**kv;

	kv = ft_split_equal(str);
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, kv[0]))
		{
			if (kv[1])
			{
				tmp->value = ft_strreplace(tmp->value, kv[1]);
				tmp->print_flag = 1;
			}
			ft_arrfree(kv);
			return (1);
		}
		tmp = tmp->next;
	}
	ft_arrfree(kv);
	return (0);
}

static void	t_env_add_new_key(t_env *env, char *str, int *rt_flag)
{
	t_env	*tmp;

	if (!is_valid_identifier(str))
	{
		error_message(env, ERR_EXPORT, str, 1);
		(*rt_flag) = 1;
	}
	else if (t_env_key_reset(env, str))
		;
	else
	{
		tmp = t_env_lstnew(str, is_valid_identifier(str));
		t_env_lstadd_back(&env, tmp);
	}
}

int	builtin_export(t_data *d, char **args)
{
	int		i;
	int		rt_flag;

	rt_flag = 0;
	if (ft_strcmp(args[0], "export"))
		return (0);
	if (!args[1])
	{
		t_env_print_sorted(d->env, 0);
		t_env_exit_status_reset(d->env, 0);
		return (0);
	}
	i = 0;
	while (args[++i])
		t_env_add_new_key(d->env, args[i], &rt_flag);
	t_env_exit_status_reset(d->env, rt_flag);
	return (rt_flag);
}
