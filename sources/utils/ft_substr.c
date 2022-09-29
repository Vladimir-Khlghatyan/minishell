/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:44:16 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:44:17 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		s_len;
	char	*substr;

	s_len = ft_strlen(s);
	if (s_len < start)
	{
		substr = malloc(sizeof(*s) * 1);
		substr[0] = '\0';
		return (substr);
	}
	if (s_len - start >= len)
		substr = malloc(sizeof(*s) * (len + 1));
	else
		substr = malloc(sizeof(*s) * (s_len - start + 1));
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
}
