/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:42:11 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:42:12 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_signals(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		printf("  \n");
		rl_on_new_line();
		rl_redisplay();
	}
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_signals2(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint_flag = 1;
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  ", NULL, NULL, 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_signals3(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint_flag = 1;
		printf("\n");
		rl_replace_line("", 0);
	}
	else if (sig == SIGQUIT)
	{
		g_sigint_flag = 131;
		ft_putstr_fd("Quit: 3\n", NULL, NULL, 2);
	}
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, SIG_IGN);
}
