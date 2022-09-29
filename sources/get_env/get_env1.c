/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:35:17 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:35:18 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*t_env_lstnew(char *str, int flag)
{
	t_env	*new_node;
	char	**kv;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	kv = ft_split_equal(str);
	new_node->print_flag = flag;
	new_node->key = ft_strdup(kv[0]);
	new_node->value = ft_strdup(kv[1]);
	ft_arrfree(kv);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_env	*t_env_lstlast(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!tmp->next)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	t_env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last_element;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_element = t_env_lstlast(*lst);
	last_element->next = new;
	new->prev = last_element;
}

t_env	*copy_environment(char **envp, char *prog_name)
{
	t_env	*tmp;
	t_env	*env;
	int		i;

	env = NULL;
	i = -1;
	while (envp[++i])
	{
		tmp = t_env_lstnew(envp[i], 1);
		t_env_lstadd_back(&env, tmp);
	}
	t_env_init_shlvl_and_underscore(env, prog_name);
	t_env_init_oldpwd(env);
	tmp = t_env_lstnew("?=0", 0);
	t_env_lstadd_back(&env, tmp);
	return (env);
}

int	ft_shlvl_max_check(int n)
{
	char	*value;

	if (n < 0)
		return (0);
	if (n < 1000)
		return (++n);
	n = n + 1;
	value = ft_lltoa(n);
	ft_putstr_fd("bash: warning: shell level (", value, \
		") too high, resetting to 1\n", 1);
	free(value);
	return (1);
}
