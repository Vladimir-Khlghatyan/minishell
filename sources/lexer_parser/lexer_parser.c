/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:37:46 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:37:56 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_inputs	*lexer_parser(t_env *env, char *str)
{
	char		**tokens;
	t_inputs	*inp;

	tokens = lexer(str);
	inp = parser(env, tokens);
	if (str)
		free(str);
	str = NULL;
	return (inp);
}

void	t_inputs_print(t_inputs *inp)
{
	int			i;
	int			j;
	t_inputs	*tmp;

	j = 0;
	tmp = inp;
	while (tmp)
	{
		printf("%snode %2d: %16s-> %s", RED, ++j, tmp->type, RESET);
		i = -1;
		if (tmp->args == NULL)
			printf(" %s[%s%s%s]%s", RED, WHITE, "(null)", RED, RESET);
		else
			while (tmp->args[++i])
				printf(" %s[%s%s%s]%s", RED, WHITE, tmp->args[i], RED, RESET);
		printf("  rdflag=%d", tmp->redir_is_last);
		printf("\n");
		tmp = tmp->next;
	}
}
