/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:38:17 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:38:19 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_or_operator_cnt(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!str)
		return (0);
	if (check_unclosed_quotes(str, 0, 0, 0) > 0)
		return (0);
	while (str[i])
	{
		double_quotes(str, &i, &cnt);
		single_quotes(str, &i, &cnt);
		if (metacharacters(str, &i, &cnt) == 0)
			non_metacharacters(str, &i, &cnt);
	}
	return (cnt);
}

static void	arr_of_ints_for_substr(char *str, int cnt, int **indexes)
{
	int	i;
	int	j;

	*indexes = (int *)malloc(sizeof(int) * (cnt + 1));
	if (!(*indexes))
		return ;
	i = 0;
	j = 0;
	**indexes = 0;
	while (str[i])
	{
		if (double_quotes(str, &i, &cnt))
			(*indexes)[++j] = i;
		if (single_quotes(str, &i, &cnt))
			(*indexes)[++j] = i;
		if (metacharacters(str, &i, &cnt))
			(*indexes)[++j] = i;
		else
			if (non_metacharacters(str, &i, &cnt))
				(*indexes)[++j] = i;
	}
}

static void	space_trim(char **tokens)
{
	int		i;

	i = -1;
	while (tokens[++i])
		tokens[i] = ft_strtrim_free(tokens[i], " ");
}

static char	**pipes_separation(char **tokens, int cnt, int i, int j)
{
	char	**newtoks;

	if (!tokens)
		return (NULL);
	while (tokens[++i])
		if (pipe_exist(tokens[i]))
			cnt++;
	if (cnt == 0)
		return (tokens);
	newtoks = (char **)malloc(sizeof(char *) * (ft_arrlen(tokens) + cnt + 1));
	if (!newtoks)
		return (ft_arrfree(tokens));
	i = -1;
	while (tokens[++i])
	{
		if (pipe_exist(tokens[i]))
		{
			newtoks[++j] = ft_strdup("|");
			newtoks[++j] = ft_substr(tokens[i], 1, 3);
		}
		else
			newtoks[++j] = ft_strdup(tokens[i]);
	}
	newtoks[++j] = (char *)ft_arrfree(tokens);
	return (newtoks);
}

char	**lexer(char *str)
{
	int		i;
	int		cnt;
	int		*indexes;
	char	**tokens;

	cnt = word_or_operator_cnt(str);
	if (cnt == 0)
		return (NULL);
	tokens = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!tokens)
		return (NULL);
	arr_of_ints_for_substr(str, cnt, &indexes);
	if (!indexes)
	{
		free(tokens);
		return (NULL);
	}
	i = -1;
	while (++i < cnt)
		tokens[i] = ft_substr(str, indexes[i], indexes[i + 1] - indexes[i]);
	tokens[i] = NULL;
	free(indexes);
	space_trim(tokens);
	tokens = remove_empty_tokens(tokens, -1, -1, cnt);
	return (pipes_separation(tokens, 0, -1, -1));
}
