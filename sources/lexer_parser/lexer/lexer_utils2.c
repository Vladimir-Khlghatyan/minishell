/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:38:37 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:38:39 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_before_remove_spaces(char *str)
{
	int	i;

	if (!str || !str[0] || str[0] != '|')
		return (0);
	i = 1;
	while (str[i] == ' ')
		i++;
	if (ft_strlen(str + i) <= 2)
		return (1);
	return (0);
}

static char	*remove_spaces_after_pipe(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	if (str[0] != '|' || !ft_check_before_remove_spaces(str))
		return (str);
	i = 1;
	while (str[i] == ' ')
		i++;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 2));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	j = 0;
	new_str[0] = '|';
	i--;
	while (str[++i])
		new_str[++j] = str[i];
	new_str[++j] = '\0';
	free(str);
	return (new_str);
}

char	**remove_empty_tokens(char **tokens, int i, int j, int cnt)
{
	int		empty;
	char	**new_tokens;

	empty = 0;
	while (tokens[++i])
		if (tokens[i][0] == '\0')
			empty++;
	new_tokens = (char **)malloc(sizeof(char *) * (cnt - empty + 1));
	i = -1;
	while (tokens[++i])
	{
		if (tokens[i][0] == '\0')
			free(tokens[i]);
		else
			new_tokens[++j] = remove_spaces_after_pipe(tokens[i]);
	}
	new_tokens[++j] = NULL;
	free(tokens);
	return (new_tokens);
}

int	pipe_exist(char *str)
{
	if (!ft_strcmp(str, "|<") || !ft_strcmp(str, "|>") || \
		!ft_strcmp(str, "|<<") || !ft_strcmp(str, "|>>"))
		return (1);
	return (0);
}
