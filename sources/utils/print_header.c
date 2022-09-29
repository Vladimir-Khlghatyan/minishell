/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:44:25 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:44:26 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_header(void)
{
	printf("%s%s", BLUE,
		"                      ____  ___               ___ ___ \n");
	printf("                     6MMMMb|`MM               `MM `MM \n");
	printf("                    6M'    ` MM                MM  MM \n");
	printf("%s%s%s%s", RED,
		"             ____", BLUE, "   MM       MM  __     ____   MM  MM \n");
	printf("%s%s%s%s", RED,
		"       ,M   6MMMMb", BLUE, "  YM.      MM 6MMb   6MMMMb  MM  MM \n");
	printf("%s%s%s%s", RED,
		"      ,dM  MM'  `Mb", BLUE, "  YMMMMb  MMM9 `Mb 6M'  `Mb MM  MM \n");
	printf("%s%s%s%s", RED,
		"     ,dMM       ,MM", BLUE, "      `Mb MM'   MM MM    MM MM  MM \n");
	printf("%s%s%s%s", RED,
		"    ,d MM      ,MM'", BLUE, "       MM MM    MM MMMMMMMM MM  MM \n");
	printf("%s%s%s%s", RED,
		"   ,d  MM    ,M'", BLUE, "          MM MM    MM MM       MM  MM \n");
	printf("%s%s%s%s", RED,
		"  ,d   MM  ,M'", BLUE, "      L    ,M9 MM    MM YM    d9 MM  MM \n");
	printf("%s%s%s%s", RED,
		"  MMMMMMMM MMMMMMMM", BLUE, " MYMMMM9 _MM_  _MM_ YMMMM9 _MM__MM_\n");
	printf("%s%s", RED, "       MM\n");
	printf("%s%s%s", "       MM", YELLOW,
		"              created by  Vladimir Khlghatyan\n");
	printf("%s%s%s%s", RED, "       MM", YELLOW,
		"                      and    Levon Malkhasyan\n\n");
}
