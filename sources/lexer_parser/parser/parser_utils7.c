/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:40:29 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:40:31 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parser_utils8.c  //
char		**t_inputs_type_to_arr(t_inputs *inp);
void		t_inputs_types_reset(t_inputs *inp, char **arr);

static char	*ft_hd_limiter_parse(char *str)
{
	char	**arr;
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	if (!str[0])
		return (str);
	arr = quotedstrtoarr(str);
	i = -1;
	while (arr[++i])
	{		
		if (arr[i][0] == '\'')
			arr[i] = ft_strtrim_free(arr[i], "\'");
		else if (arr[i][0] == '\"')
			arr[i] = ft_strtrim_free(arr[i], "\"");
	}
	new_str = join_arr_to_str(arr);
	return (new_str);
}

static int	ft_check_if_quotes_exist(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
	return (0);
}

void	t_inputs_hd_limiter_parse(t_inputs *inp)
{
	t_inputs	*tmp;
	char		*str;
	char		**tmp_types;

	tmp_types = t_inputs_type_to_arr(inp);
	tmp = inp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, HEREDOC))
		{
			if (!ft_check_if_quotes_exist(tmp->args[1]))
				tmp->quote_in_hd_limiter = 1;
			str = ft_hd_limiter_parse(tmp->args[1]);
			tmp->args[1] = ft_strreplace(tmp->args[1], str);
			free(str);
		}
		tmp = tmp->next;
	}
	t_inputs_types_reset(inp, tmp_types);
}
