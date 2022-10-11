/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:34:18 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:34:22 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_long_long_limits(char *str)
{
	char		*new_str;
	int			i;
	int			start;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] == '0')
		i++;
	if (!str[i])
		return (1);
	new_str = ft_lltoa(ft_atoll(str));
	start = 0;
	if (ft_sign(str) == -1)
		start = 1;
	if (!ft_strcmp(str + i, new_str + start))
	{
		free(new_str);
		return (1);
	}
	free(new_str);
	return (0);
}

static int	exit_args_check(char **args)
{
	if (!args[1])
		return (0);
	if (!ft_sign(args[1]) || !ft_check_long_long_limits(args[1]))
		return (1);
	if (ft_arrlen(args) > 2)
		return (2);
	return (0);
}

static int	ft_exit_status(char *str)
{
	long long	num;
	int			exit_status;

	num = ft_atoll(str);
	if (num < 0)
		exit_status = 256 + (num % 256);
	else
		exit_status = num % 256;
	return (exit_status);
}

int	builtin_exit(t_data *d, char **args)
{
	int	exit_status;

	if (ft_strcmp(args[0], "exit"))
		return (0);
	if (exit_args_check(args) == 1)
	{
		d->exit_flag = 255;
		return (error_message(d->env, ERR_EXIT1, d->inp->args[1], 255));
	}
	if (exit_args_check(args) == 2)
	{
		d->exit_flag = 1;
		return (error_message(d->env, ERR_EXIT2, NULL, 1));
	}
	if (!args[1])
	{
		t_env_exit_status_reset(d->env, 0);
		d->exit_flag = 0;
		return (0);
	}
	exit_status = ft_exit_status(args[1]);
	t_env_exit_status_reset(d->env, exit_status);
	d->exit_flag = exit_status;
	return (exit_status);
}

void	ft_exit_check(t_data *d)
{
	if (d->exit_flag != -1 && d->exit_flag != 1)
	{
		ft_envfree(d->env);
		free(d);
		write(1, "exit 💚\n", ft_strlen("exit 💚\n"));
		exit(d->exit_flag);
	}
	if (d->exit_flag == 1)
		write(1, "exit\n", ft_strlen("exit\n"));
}
