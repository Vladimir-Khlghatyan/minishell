/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_quotes4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:39:15 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:39:20 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// from dollar_and_quotes7.c //
int	ft_split_dollar_cnt(char *str);

char	*dollar_str(char *s, int *index)
{
	int		i;
	int		cnt;
	char	*new_str;

	i = 0;
	cnt = 1;
	if (!ft_strncmp(s, "$?", 2))
		cnt = 2;
	else if (s[++i] && ((s[i] >= 'A' && s[i] <= 'Z') || \
			(s[i] >= 'a' && s[i] <= 'z') || s[i] == '_'))
	{
		cnt++;
		while (s[++i] && ((s[i] >= 'A' && s[i] <= 'Z') || \
			(s[i] >= 'a' && s[i] <= 'z') || \
			(s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
			cnt++;
	}
	new_str = ft_substr(s, 0, cnt);
	(*index) += cnt;
	return (new_str);
}

char	*non_dollar_str(char *str, int *index)
{
	int		i;
	int		cnt;
	char	*new_str;

	i = -1;
	cnt = 0;
	while (str[++i] && str[i] != '$')
		cnt++;
	new_str = ft_substr(str, 0, cnt);
	(*index) += cnt;
	return (new_str);
}

static char	**empty_arr(void)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 2);
	arr[0] = ft_strdup("");
	arr[1] = NULL;
	return (arr);
}

char	**ft_split_dollar(char *str, int i, int j)
{
	char	**arr;

	if (str[0] == '\0')
		return (empty_arr());
	arr = (char **)malloc(sizeof(char *) * (ft_split_dollar_cnt(str) + 1));
	while (str[i])
	{
		if (str[i] == '$')
			arr[++j] = dollar_str(str + i, &i);
		else
			arr[++j] = non_dollar_str(str + i, &i);
	}
	arr[++j] = NULL;
	return (arr);
}

char	**quotedstrtoarr(char *str)
{
	int		*idx;
	char	**arr;
	int		cnt;
	int		i;

	cnt = ft_strcnt(str);
	if (cnt == 0)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!arr)
		return (NULL);
	idx = ft_intarr_for_split(str, 0, 0);
	if (!idx)
	{
		free(arr);
		return (NULL);
	}
	i = -1;
	while (++i < cnt)
		arr[i] = ft_substr(str, idx[i], idx[i + 1] - idx[i]);
	arr[i] = NULL;
	free(idx);
	return (arr);
}
