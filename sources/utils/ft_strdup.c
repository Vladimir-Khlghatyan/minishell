/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:43:49 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:43:51 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *src)
{
	char	*dst;
	int		i;

	if (!src)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strreplace(char *str, char *replace)
{
	if (str)
		free(str);
	return (ft_strdup(replace));
}

char	*ft_strdup_for_builtin_cd(char *src)
{
	char	*dst;
	int		i;

	if (!src)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	if (dst[0])
		ft_putstr_fd(dst, "\n", NULL, 1);
	return (dst);
}
