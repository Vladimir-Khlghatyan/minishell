/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:43:33 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:43:34 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(char *s, int c)
{
	char	*str;
	int		i;

	str = (char *) s;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		i++;
	if (c == '\0')
		return (str + i);
	i = 0;
	while (str[i])
	{
		if (str[i] != (char) c)
			i++;
		else
			return (str + i);
	}
	return (NULL);
}
