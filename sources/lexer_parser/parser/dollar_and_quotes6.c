/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_quotes6.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:39:42 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:39:43 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* dollar_and_quotes1.c */
char	*t_env_get_key(t_env *env, char *key);
char	*ft_to_be_split(char *str);

static char	*handle_(t_env *env, char *str, int flag)
{
	char	**tmp;
	int		j;

	str = ft_strtrim_free(str, "\"");
	tmp = ft_split_dollar(str, 0, -1);
	j = -1;
	while (tmp[++j])
	{
		if (flag == 1)
			tmp[j] = check_and_replace_str1(env, tmp[j]);
		if (flag == 2)
			tmp[j] = check_and_replace_str2(env, tmp[j], 1);
	}
	if (str)
		free(str);
	str = join_arr_to_str(tmp);
	return (str);
}

static char	**check_and_replace_arr(t_env *env, char **arr)
{
	int		i;

	if (!arr)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		if (arr[i][0] == '\'')
			arr[i] = ft_strtrim_free(arr[i], "\'");
		else if (arr[i][0] == '\"')
			arr[i] = handle_(env, arr[i], 1);
		else
			arr[i] = handle_(env, arr[i], 2);
	}
	return (arr);
}

char	*str_dollar_sign_handler(t_env *env, char *str)
{
	char	**arr;
	char	*new_str;

	arr = quotedstrtoarr(str);
	arr = check_and_replace_arr(env, arr);
	new_str = join_arr_to_str(arr);
	free(str);
	return (new_str);
}
