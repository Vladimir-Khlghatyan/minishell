/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_and_quotes5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:39:31 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:39:32 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* from dollar_and_quotes2.c */
int		ft_to_be_split_cnt(char *s);
int		ft_arr_new_size(char **arr);
char	**ft_split_word(char *s1, char *s2);
char	**ft_check_for_to_be_split(char **arr);

void	t_inputs_dollar_sign_handler(t_env *env, t_inputs *inp)
{
	t_inputs	*tmp;
	int			i;

	tmp = inp;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, HEREDOC))
		{
			i = -1;
			while (tmp->args[++i])
				tmp->args[i] = str_dollar_sign_handler(env, tmp->args[i]);
		}
		tmp = tmp->next;
	}
	tmp = inp;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, HEREDOC))
			tmp->args = ft_check_for_to_be_split(tmp->args);
		tmp = tmp->next;
	}
}
