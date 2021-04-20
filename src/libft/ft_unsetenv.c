/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 04:59:17 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/04/19 21:19:23 by user42           ###   ########.fr       */
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
		if (ft_strcmp(str[0], name) == EQUAL)
			return (&environ[i]);
		i++;
	}
	return (NULL);
}

int		ft_unsetenv(char *name)
{
	extern char **environ;
	char **adress;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (FAIL);
	}
	adress = get_env_adress(name);
	if (adress != NULL)
	{
		while (*adress)
		{
			*adress = *(adress + 1);
			adress++;
		}
		adress++;
	}
	return (0);
}
