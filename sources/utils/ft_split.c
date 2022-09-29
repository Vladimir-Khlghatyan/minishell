/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:43:22 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:43:23 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**tabfree(char **tab)
{
	int	i;

	if (!tab)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

static int	wordcount(char *s, char c)
{
	int	q;
	int	i;

	q = 1;
	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			q++;
		i++;
	}
	return (q);
}

static int	wordlen(char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		wc;
	int		i[2];

	if (!s)
		return (NULL);
	i[0] = -1;
	wc = wordcount(s, c);
	tab = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!tab)
		return (NULL);
	while (++i[0] < wc)
	{
		tab[i[0]] = (char *)malloc(sizeof(char) * (wordlen(s, c) + 1));
		if (!tab[i[0]])
			return (tabfree(tab));
		while (*s == c)
			s++;
		i[1] = 0;
		while (*s != c && *s)
			tab[i[0]][i[1]++] = *s++;
		tab[i[0]][i[1]] = '\0';
	}
	tab[i[0]] = NULL;
	return (tab);
}

char	**ft_split_equal(char *s)
{
	char	**tab;
	int		len;
	int		eq_sign;

	eq_sign = 0;
	if (ft_strchr(s, '='))
		eq_sign = 1;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (2 + eq_sign));
	if (!tab)
		return (NULL);
	len = ft_strlen(s) - ft_strlen(ft_strchr(s, '='));
	tab[0] = ft_substr(s, 0, len);
	if (!tab[0])
		return (ft_arrfree(tab));
	tab[1] = NULL;
	if (eq_sign == 1)
	{
		tab[1] = ft_substr(s, len + 1, ft_strlen(s) - len);
		if (!tab[1])
			return (ft_arrfree(tab));
		tab[2] = NULL;
	}
	return (tab);
}
