/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:33:27 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:33:29 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_val(t_data *d, char *key);
char	*get_home_path(t_data *d);
int		free_two_strs(char *s1, char *s2);
int		ft_home_check(t_data *d, char **args);
int		chdir_fail(t_data *d, char *home, char *go_to);

static int	cd_change_dir(t_data *d, char **args)
{
	char	*home;
	char	*go_to;

	if (ft_home_check(d, args))
		return (1);
	home = get_home_path(d);
	if (!home)
		return (error_message(d->env, ERR_PERMIS, NULL, 1));
	if (args[1] == NULL)
		go_to = ft_strdup(home);
	else if (args[1][0] == '~')
		go_to = ft_strjoin(home, args[1] + 1);
	else if (!ft_strcmp(args[1], "-"))
		go_to = ft_strdup_for_builtin_cd(env_val(d, "OLDPWD"));
	else
		go_to = ft_strdup(args[1]);
	if (!go_to || !go_to[0])
		free_two_strs(home, go_to);
	if (!go_to || !go_to[0])
		return (error_message(d->env, ERR_OLDPWD, NULL, 1));
	if (!go_to[0])
		return (free_two_strs(go_to, NULL));
	if (chdir(go_to) == -1)
		return (chdir_fail(d, home, go_to));
	return (free_two_strs(home, go_to));
}

static t_env	*env_node(t_data *d, char *key)
{
	t_env	*tmp;

	tmp = d->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	cd_change_env(t_data *d, char *oldpwd, char *pwd)
{
	t_env	*oldpwd_key;
	t_env	*pwd_key;

	oldpwd_key = env_node(d, "OLDPWD");
	pwd_key = env_node(d, "PWD");
	if (!pwd_key)
	{
		if (!oldpwd_key || oldpwd_key->print_flag == 0)
			return ;
		else
			t_env_change_val_and_flag(d->env, "OLDPWD", "", 1);
	}
	else
	{
		t_env_change_val_and_flag(d->env, "PWD", pwd, 1);
		if (oldpwd_key)
			t_env_change_val_and_flag(d->env, "OLDPWD", oldpwd, 1);
	}
}

static void	ft_get_pwd_and_oldpwd(t_env *env, char **pwd, char **oldpwd)
{
	t_env	*tmp;

	if (*pwd || *oldpwd)
		return ;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			*pwd = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			*oldpwd = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

int	builtin_cd(t_data *d, char **args)
{
	int		ex_status;
	char	*oldpwd;
	char	*pwd;

	if (ft_strcmp(args[0], "cd"))
		return (0);
	oldpwd = getcwd(NULL, 0);
	ex_status = cd_change_dir(d, args);
	if (ex_status == 0)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			ft_putstr_fd("cd: error retrieving current directory: getcwd: ", \
				"cannot access parent directories: ", \
				"No such file or directory\n", 2);
			ft_get_pwd_and_oldpwd(d->env, &pwd, &oldpwd);
		}
		cd_change_env(d, oldpwd, pwd);
		free(pwd);
	}
	free(oldpwd);
	t_env_exit_status_reset(d->env, ex_status);
	return (ex_status);
}
