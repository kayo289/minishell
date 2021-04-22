/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 03:18:18 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/04/22 23:34:17 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*t;

	if (c == '\0')
		return ((char *)s);
	t = (char *)s;
	while (*t != '\0')
	{
		if (*t == (char)c)
			return (t);
		t++;
	}
	return (NULL);
}
