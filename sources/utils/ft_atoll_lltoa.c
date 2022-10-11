/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_lltoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:42:54 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:42:55 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sign(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	if (str[0] == '-')
		return (-1);
	return (1);
}

long long	ft_atoll(char *str)
{
	int			sign;
	long long	num;
	int			i;

	sign = ft_sign(str);
	num = 0;
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * sign);
}

static int	ft_llnumlen(long long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len += 1;
		n = n / 10;
	}
	return (len);
}

char	*ft_lltoa(long long n)
{
	int		rem;
	int		len;
	char	*str;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = ft_llnumlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (--len >= 0)
	{
		rem = n % 10;
		n = n / 10;
		if (rem < 0)
			rem = -rem;
		str[len] = rem + '0';
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
