/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_quotes3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:39:08 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:39:10 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unquoted_str(char *str, int *i, int *cnt)
{
	if (str[(*i)] != '\'' && str[(*i)] != '\"')
	{
		while (str[*i] && str[(*i)] != '\'' && str[(*i)] != '\"')
			(*i)++;
		(*cnt)++;
		return ((*i));
	}
	return (-1);
}

static int	single_quoted_str(char *str, int *i, int *cnt)
{
	if (str[(*i)] == '\'')
	{
		(*i)++;
		while (str[(*i)] != '\'')
			(*i)++;
		(*i)++;
		(*cnt)++;
		return ((*i));
	}
	return (-1);
}

static int	double_quoted_str(char *str, int *i, int *cnt)
{
	if (str[(*i)] == '\"')
	{
		(*i)++;
		while (str[(*i)] != '\"')
			(*i)++;
		(*i)++;
		(*cnt)++;
		return ((*i));
	}
	return (-1);
}

int	ft_strcnt(char *str)
{
	int	i;
	int	cnt;

	if (!str)
		return (0);
	i = 0;
	cnt = 0;
	while (str[i])
	{
		unquoted_str(str, &i, &cnt);
		single_quoted_str(str, &i, &cnt);
		double_quoted_str(str, &i, &cnt);
	}
	return (cnt);
}

int	*ft_intarr_for_split(char *str, int i, int cnt)
{
	int	*nmbs;
	int	j;

	if (ft_strcnt(str) == 0)
		return (NULL);
	nmbs = (int *)malloc(sizeof(int) * (ft_strcnt(str) + 1));
	if (!nmbs)
		return (NULL);
	nmbs[0] = 0;
	j = 0;
	while (str[i])
	{
		if (unquoted_str(str, &i, &cnt) != -1)
			nmbs[++j] = i;
		if (single_quoted_str(str, &i, &cnt) != -1)
			nmbs[++j] = i;
		if (double_quoted_str(str, &i, &cnt) != -1)
			nmbs[++j] = i;
	}
	nmbs[++j] = i;
	return (nmbs);
}
