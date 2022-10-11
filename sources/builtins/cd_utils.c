/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:33:39 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:33:40 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_val(t_data *d, char *key)
{
	t_env	*tmp;

	tmp = d->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_home_path(t_data *d)
{
	char	*dir_path;
	char	**dirs;
	char	*home;

	home = env_val(d, "HOME");
	if (home)
		return (ft_strdup(home));
	dir_path = getcwd(NULL, 0);
	if (!dir_path)
		return (NULL);
	dirs = ft_split(dir_path, '/');
	home = ft_strjoin("/", dirs[0]);
	home = ft_strjoin_free(home, "/");
	home = ft_strjoin_free(home, dirs[1]);
	free(dir_path);
	ft_arrfree(dirs);
	return (home);
}

int	free_two_strs(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (0);
}

int	ft_home_check(t_data *d, char **args)
{
	char	*home;

	home = env_val(d, "HOME");
	if (!home && !args[1])
		return (error_message(d->env, ERR_HOME, NULL, 1));
	return (0);
}

int	chdir_fail(t_data *d, char *home, char *go_to)
{
	char	*err;

	err = strerror(errno);
	free_two_strs(home, go_to);
	return (error_message(d->env, "minishell: ", err, 1));
}
