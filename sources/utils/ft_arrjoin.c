/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:42:47 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:42:48 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arrjoin(char **arr1, char **arr2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	**new_arr;

	len1 = ft_arrlen(arr1);
	len2 = ft_arrlen(arr2);
	new_arr = (char **)malloc(sizeof(char *) * (len1 + len2 + 1));
	if (!new_arr)
		return (NULL);
	i = -1;
	while (arr1[++i])
		new_arr[i] = ft_strdup(arr1[i]);
	j = -1;
	while (arr2[++j])
		new_arr[i + j] = ft_strdup(arr2[j]);
	new_arr[i + j] = NULL;
	return (new_arr);
}
