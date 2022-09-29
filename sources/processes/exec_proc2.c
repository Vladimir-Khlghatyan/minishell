/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:41:27 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:41:28 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->pipefd_cnt)
		close(d->pipefds[i]);
	if (d->pipefds)
		free(d->pipefds);
	d->pipefds = NULL;
}

char	**get_path(t_data *d)
{
	t_env	*tmp;
	char	*path;
	char	**path_arr;
	int		i;

	tmp = d->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp->value, ":.");
	path_arr = ft_split(path, ':');
	free(path);
	i = -1;
	while (path_arr[++i])
		path_arr[i] = ft_strjoin_free(path_arr[i], "/");
	return (path_arr);
}

char	*check_cmd(char **path_arr, char *cmd)
{
	int		i;
	char	*cmd_full_path;

	if (access(cmd, 0) == 0)
	{
		ft_arrfree(path_arr);
		return (cmd);
	}
	if (!path_arr)
		return (NULL);
	i = -1;
	while (path_arr[++i])
	{
		cmd_full_path = ft_strjoin(path_arr[i], cmd);
		if (access(cmd_full_path, 0) == 0)
		{
			ft_arrfree(path_arr);
			return (cmd_full_path);
		}
		free(cmd_full_path);
	}
	ft_arrfree(path_arr);
	return (NULL);
}

char	**t_env_to_array(t_env *env)
{
	char	**env_arr;
	int		len;
	int		i;
	t_env	*tmp;

	len = t_env_len(env);
	env_arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env_arr)
		return (NULL);
	i = -1;
	tmp = env;
	while (tmp)
	{
		env_arr[++i] = ft_strjoin(tmp->key, "=");
		env_arr[i] = ft_strjoin_free(env_arr[i], tmp->value);
		tmp = tmp->next;
	}
	env_arr[++i] = NULL;
	return (env_arr);
}
