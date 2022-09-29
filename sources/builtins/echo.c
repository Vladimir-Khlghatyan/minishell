/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:33:52 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:33:54 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-' || ft_strlen(str) == 1)
		return (0);
	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	builtin_echo(t_data *d, char **args)
{
	int		i;
	int		nl_flag;

	if (ft_strcmp(args[0], "echo"))
		return (0);
	t_env_underscore_key_reset(d->env, args);
	nl_flag = 1;
	i = 0;
	while (args[++i] && is_option(args[i]))
		nl_flag = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], NULL, NULL, 1);
		if (args[++i])
			ft_putstr_fd(" ", NULL, NULL, 1);
	}
	if (nl_flag)
		ft_putstr_fd("\n", NULL, NULL, 1);
	t_env_exit_status_reset(d->env, 0);
	return (0);
}
