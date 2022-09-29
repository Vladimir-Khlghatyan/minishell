/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:31:57 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:31:58 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define RED       		"\33[1;31m"
# define GREEN      	"\33[1;32m"
# define PINK	    	"\33[1;35m"
# define YELLOW			"\33[1;33m"
# define BLUE     		"\33[1;36m"
# define CYAN       	"\33[1;37m"
# define WHITE			"\033[1;37m"
# define RESET			"\33[0;m"

# define MC 			" |<>"
# define PIPE			"pipe"
# define REDIR			"redirection"
# define CMD			"command"
# define HEREDOC		"heredoc"
# define UNEXP			"unexpected token"
# define BUILTIN		"builtin"

# define ERR_TOKEN   	"minishell 💔: syntax error near unexpected token` "
# define ERR_HEREDOC	"minishell 💔: here documnet error!"
# define ERR_NOFILE		"minishell 💔: no such file or directory: "
# define ERR_ENV		"minishell 💔: env: Args and options are not required: "
# define ERR_MINISHELL	"minishell 💔: Arguments are not required: "
# define ERR_EXPORT		"minishell 💔: export: Not a valid identifier: "
# define ERR_UNSET		"minishell 💔: unset: Not a valid identifier: "
# define ERR_PERMIS		"minishell 💔: permission denied: "
# define ERR_OLDPWD		"minishell 💔: cd: OLDPWD not set"
# define ERR_HOME		"minishell 💔: cd: HOME not set"
# define ERR_EXIT1		"minishell 💔: exit: numeric argument required: "
# define ERR_EXIT2		"minishell 💔: exit: too many arguments"
# define ERR_HDMAX		"minishell 💔: maximum here-document count exceeded"
# define ERR_CMD		"minishell 💔: command not found: "
# define ERR_FORK		"minishell 💔: fork: Resource temporarily unavailable"
# define ERR_PIPE		"minishell 💔: pipe: no buffer space available"

#endif
