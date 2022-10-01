/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:40:19 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:40:20 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this function checks cases "<>" and "><" //

char	**ft_unxep_token_util(char **args)
{
	char	**new;

	if ((ft_strcmp(args[0], "<>") && ft_strcmp(args[0], "><")))
		return (args);
	new = (char **)malloc(sizeof(char *) * 3);
	if (!new)
		return (args);
	new[0] = ft_strdup(args[0]);
	if (args[0][1] == '<')
		new[1] = ft_strdup("<");
	else
		new[1] = ft_strdup(">");
	if (args[1] != NULL)
		new[1] = ft_strjoin_free(new[1], args[1]);
	new[2] = NULL;
	ft_arrfree(args);
	return (new);
}

char	**t_inputs_type_to_arr(t_inputs *inp)
{
	int		len;
	int		i;
	char	**types;

	len = t_inputs_len(inp);
	types = (char **)malloc(sizeof(char *) * (len + 1));
	if (!types)
		return (NULL);
	i = -1;
	while (inp)
	{
		types[++i] = ft_strdup(inp->type);
		inp = inp->next;
	}
	types[++i] = NULL;
	return (types);
}

void	t_inputs_types_reset(t_inputs *inp, char **arr)
{
	int		i;

	i = -1;
	while (inp)
	{
		inp->type = ft_strreplace(inp->type, arr[++i]);
		inp = inp->next;
	}
	ft_arrfree(arr);
}

static int	ft_redir_is_last(t_inputs *inp)
{
	t_inputs	*tmp;

	if (ft_strcmp(inp->args[0], "<"))
		return (0);
	tmp = inp;
	while (tmp)
	{
		if (!tmp->next || !ft_strcmp(tmp->next->type, PIPE))
			return (1);
		if (!ft_strcmp(tmp->next->type, HEREDOC))
			return (0);
		tmp = tmp->next;
	}
	return (0);
}

void	t_inputs_redir_flags_set(t_inputs *inp)
{
	t_inputs	*tmp;

	tmp = inp;
	while (tmp)
	{
		if (ft_strcmp(tmp->args[0], "<"))
			tmp = tmp->next;
		else
		{		
			tmp->redir_is_last = ft_redir_is_last(tmp);
			tmp = tmp->next;
		}
	}
}
