/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:35:00 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:35:02 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (s[i] == '\0')
			return (1);
	}
	return (0);
}

static char	*t_env_get_key(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	t_env_del_node(t_env **head, t_env **node)
{
	t_env	*remember;

	if (*node == NULL)
		return ;
	if (*node == *head)
		*head = (*head)->next;
	remember = *node;
	if ((*node)->next != NULL)
		(*node)->next->prev = (*node)->prev;
	if ((*node)->prev != NULL)
		(*node)->prev->next = (*node)->next;
	*node = (*node)->next;
	t_env_free_node(remember);
}

static void	t_env_delete_key(t_env **env, char *str)
{
	char	*key;
	t_env	*node_to_delete;

	key = t_env_get_key(*env, str);
	if (!key)
		return ;
	node_to_delete = *env;
	while (node_to_delete)
	{
		if (!ft_strcmp(node_to_delete->key, key))
			break ;
		node_to_delete = node_to_delete->next;
	}
	t_env_del_node(env, &node_to_delete);
}

int	builtin_unset(t_data *d, t_env **env, char **args)
{
	int		i;
	int		rt_flag;

	rt_flag = 0;
	if (ft_strcmp(args[0], "unset"))
		return (0);
	t_env_underscore_key_reset(d->env, args);
	i = 0;
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]))
		{
			error_message(d->env, ERR_UNSET, args[i], 1);
			rt_flag = 1;
		}
		else
			t_env_delete_key(&(d->env), args[i]);
	}
	t_env_exit_status_reset(d->env, rt_flag);
	*env = d->env;
	return (rt_flag);
}
