/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:09:20 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/02/13 21:29:55 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	ft_strlcat(str, s1, len + 1);
	ft_strlcat(str, s2, len + 1);
	return (str);
}
