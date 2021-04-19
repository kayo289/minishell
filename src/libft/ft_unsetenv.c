/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 04:59:17 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/04/20 02:01:34 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char **get_env_adress(char *name)
{
	extern char **environ;
	int i;
	char **str;

	i = 0;
	while(environ[i] != NULL)
	{
		str = ft_split(environ[i], '=');
		if (ft_strcmp(str[0], name) == 0)
			return (&environ[i]);
		i++;
	}
	return (NULL);
}

static int judge_err(char *name)
{
	if ((name == NULL) | (ft_strlen(name) == 0) | (ft_strchr(name, '=') != NULL))
		return (-1);
	else
		return (0);
}

int		ft_unsetenv(char *name)
{
	extern char **environ;
	char **adress;
	int status;

	status = 0;
	adress = get_env_adress(name);
	status = judge_err(name);
	if (adress != NULL)
	{
		while (*adress)
		{
			*adress = *(adress + 1);
			adress++;
		}
		adress ++;
	}
	return (status);
}
