/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:44:08 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:44:10 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	int		len;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, s1[len]))
		len--;
	str = ft_substr((char *)s1, 0, len + 1);
	return (str);
}

char	*ft_strtrim_free(char *s1, char *set)
{
	int		len;
	char	*str;
	char	*tmp;

	tmp = s1;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, s1[len]))
		len--;
	str = ft_substr((char *)s1, 0, len + 1);
	free(tmp);
	return (str);
}
