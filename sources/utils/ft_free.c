/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:43:06 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:43:09 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arrfree(char **arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		if (arr[i])
			free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
	return (NULL);
}

void	ft_envfree(t_env *env)
{
	if (env)
	{
		while (env)
		{
			if (env->key)
				free(env->key);
			if (env->value)
				free(env->value);
			if (env)
				free(env);
			env = env->next;
		}
	}
}

void	t_env_free_node(t_env *node)
{
	if (node->key)
		free(node->key);
	node->key = NULL;
	if (node->value)
		free(node->value);
	node->value = NULL;
	node->prev = NULL;
	node->next = NULL;
	free(node);
}

void	ft_inputsfree(t_inputs *inp)
{
	if (inp)
	{
		while (inp)
		{
			if ((inp->args))
				ft_arrfree(inp->args);
			if (inp->type)
				free(inp->type);
			if (inp)
				free(inp);
			inp = inp->next;
		}
	}
}
