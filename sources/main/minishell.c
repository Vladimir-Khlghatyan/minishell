/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:40:53 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:40:54 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_inputs_print(inp); //
// print_header(); //

void	display_prompt(t_env *env)
{
	char		*buffer;
	t_data		*d;
	t_inputs	*inp;

	d = (t_data *)malloc(sizeof(t_data));
	while (1)
	{
		handler_signals(0);
		buffer = readline("\33[1;32m🇦🇲  minishell> \33[0;m");
		signal(SIGINT, handler_signals3);
		signal(SIGQUIT, handler_signals3);
		if (!ft_history(buffer))
			continue ;
		inp = lexer_parser(env, buffer);
		t_data_update(d, env, inp);
		if (d->unexp_token)
			unexp_token_check(d);
		else if (d->single_builin)
			single_builtins(d, &env);
		else
			exec_processes(d, -1);
		ft_inputsfree(d->inp);
		wait_for_children(d);
		ft_exit_check(d);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	if (ac != 1)
	{
		ft_putstr_fd(ERR_MINISHELL, av[1], "\n", 2);
		exit(127);
	}
	print_header();
	env = copy_environment(envp, av[0]);
	display_prompt(env);
	return (0);
}
