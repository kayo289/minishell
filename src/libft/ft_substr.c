/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 13:47:41 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/02/13 21:29:55 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t		ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

char				*ft_substr(char const *s, size_t start, size_t len)
{
	size_t		l;
	char		*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	l = ft_min(ft_strlen(s) - start, len);
	if (!(str = ft_calloc(l + 1, sizeof(char))))
		return (NULL);
	ft_strlcpy(str, &s[start], l + 1);
	return (str);
}
