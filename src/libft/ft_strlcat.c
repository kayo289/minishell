/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 02:08:37 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/02/13 21:29:55 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t dest_len;
	size_t src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	while (src[i] && i + dest_len + 1 < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	if (size < dest_len)
		return (size + src_len);
	else
		return (dest_len + src_len);
}
