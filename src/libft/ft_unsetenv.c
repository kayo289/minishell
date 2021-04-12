/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 04:59:17 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/04/06 20:32:22 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>
static int get_env_index(char *name)
{
	extern char **environ;
	int i;
	char **str;

	i = 0;
	while(environ[i] != NULL)
	{
		str = ft_split(environ[i], '=');
		if (ft_strcmp(str[0], name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_unsetenv(char *name)
{
	extern char **environ;
	int i;
	int status;

	status = 0;
	if ((i = get_env_index(name)) != -1)
	{
		printf("unsetenv,i:%d\n",i);
		while (environ[i])
		{
			environ[i] = environ[i + 1];
			i++;
		}
	}
	return (status);
}
