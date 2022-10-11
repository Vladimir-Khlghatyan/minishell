/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:44:33 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:44:35 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putstr_fd(char *str1, char *str2, char *str3, int fd)
{
	if (str1)
		write(fd, str1, ft_strlen(str1));
	if (str2)
		write(fd, str2, ft_strlen(str2));
	if (str3)
		write(fd, str3, ft_strlen(str3));
	return (1);
}

int	error_message(t_env *env, char *err, char *str, int exit_status)
{
	ft_putstr_fd(err, str, "\n", 2);
	t_env_exit_status_reset(env, exit_status);
	return (exit_status);
}

void	error_message_and_exit(char *str, int exit_status)
{
	char	*err;

	err = strerror(errno);
	ft_putstr_fd("minishell: ", err, ": ", 2);
	ft_putstr_fd(str, "\n", NULL, 2);
	exit(exit_status);
}

void	exit_message_on_ctrl_d(char *str, int exit_status)
{
	ft_putstr_fd(str, NULL, NULL, 2);
	exit(exit_status);
}

void	ft_history(char *buffer)
{
	if (!buffer)
		exit_message_on_ctrl_d("exit\n", 0);
	if (buffer[0] != '\0')
		add_history(buffer);
}
