/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:38:26 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:38:27 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed_quotes(char *str, int i, int q1, int q2)
{
	while (str[i])
	{
		if (str[i] == '\"')
		{
			q1++;
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] == '\"')
				q1++;
		}
		else if (str[i] == '\'')
		{
			q2++;
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				q2++;
		}
		if (str[i])
			i++;
	}
	return ((q1 % 2) + (q2 % 2));
}

int	double_quotes(char *str, int *i, int *cnt)
{
	if (str[(*i)] == '\"')
	{
		(*i)++;
		while (str[(*i)] && str[(*i)] != '\"')
			(*i)++;
		(*i)++;
		while (str[(*i)] && !ft_strchr(MC, str[(*i)]))
			(*i)++;
		(*cnt)++;
		return (1);
	}
	return (0);
}

int	single_quotes(char *str, int *i, int *cnt)
{
	if (str[(*i)] == '\'')
	{
		(*i)++;
		while (str[(*i)] && str[(*i)] != '\'')
			(*i)++;
		(*i)++;
		while (str[(*i)] && !ft_strchr(MC, str[(*i)]))
			(*i)++;
		(*cnt)++;
		return (1);
	}
	return (0);
}

int	metacharacters(char *str, int *i, int *cnt)
{
	if (ft_strchr(MC, str[(*i)]))
	{
		while (str[(*i)] && ft_strchr(MC, str[(*i)]))
			(*i)++;
		(*cnt)++;
		return (1);
	}
	return (0);
}

int	non_metacharacters(char *str, int *i, int *cnt)
{
	if (!ft_strchr(MC, str[(*i)]))
	{
		while (str[(*i)] && !ft_strchr(MC, str[(*i)]))
		{
			if (str[(*i)] == '\"')
			{
				(*i)++;
				while (str[(*i)] && str[(*i)] != '\"')
					(*i)++;
				(*i)++;
			}
			else if (str[(*i)] == '\'')
			{
				(*i)++;
				while (str[(*i)] && str[(*i)] != '\'')
					(*i)++;
				(*i)++;
			}
			else
				(*i)++;
		}
		(*cnt)++;
		return (1);
	}
	return (0);
}
