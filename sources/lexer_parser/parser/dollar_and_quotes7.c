/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_quotes7.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:39:15 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:39:20 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// from dollar_and_quotes4.c //
char	*dollar_str(char *s, int *index);
char	*non_dollar_str(char *str, int *index);

int	ft_split_dollar_cnt(char *str)
{
	char	*tmp;
	int		cnt;
	int		i;

	if (str[0] == '\0')
		return (0);
	cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			tmp = dollar_str(str + i, &i);
		else
			tmp = non_dollar_str(str + i, &i);
		cnt++;
		free (tmp);
	}
	return (cnt);
}
