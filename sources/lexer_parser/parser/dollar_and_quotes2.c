/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_quotes2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:39:02 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:39:04 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_to_be_split_cnt(char *s, char *split)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (!ft_strncmp(s + i, split, ft_strlen(split)))
		{
			cnt++;
			i += ft_strlen(split);
		}
		else
			i++;
	}
	return (cnt);
}

int	ft_arr_new_size(char **arr)
{
	int	i;
	int	new_size;

	new_size = ft_arrlen(arr);
	i = -1;
	while (arr[++i])
		new_size += ft_to_be_split_cnt(arr[i], "to_be_split");
	return (new_size);
}

char	**ft_split_word(char *s1, char *s2)
{
	int		start;
	int		i;
	int		j;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (ft_to_be_split_cnt(s1, s2) + 2));
	if (!arr)
		return (NULL);
	start = 0;
	i = 0;
	j = -1;
	while (s1[i])
	{
		if (!ft_strncmp(s1 + i, s2, ft_strlen(s2)))
		{
			i += ft_strlen(s2);
			start += i;
		}
		while (s1[++i] && ft_strncmp(s1 + i, s2, ft_strlen(s2)))
			;
		arr[++j] = ft_substr(s1, start, i - start);
	}
	arr[++j] = NULL;
	return (arr);
}

char	**ft_check_for_to_be_split(char **arr)
{
	char	**new_arr;
	char	**tmp;
	int		i;
	int		j;
	int		k;

	if (ft_arrlen(arr) == ft_arr_new_size(arr))
		return (arr);
	new_arr = (char **)malloc(sizeof(char *) * (ft_arr_new_size(arr) + 1));
	if (!new_arr)
		return (NULL);
	i = -1;
	j = -1;
	while (arr[++i])
	{
		tmp = ft_split_word(arr[i], "to_be_split");
		k = -1;
		while (tmp[++k])
			new_arr[++j] = tmp[k];
		free(tmp);
	}
	new_arr[++j] = NULL;
	ft_arrfree(arr);
	return (new_arr);
}
