/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 01:27:09 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/04/22 23:41:05 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *buf1, const void *buf2, size_t n)
{
	size_t	i;

	if (!buf1 && !buf2)
		return (NULL);
	if (buf1 > buf2)
		ft_memcpy(buf1, buf2, n);
	else
	{
		i = 0;
		while (i < n)
		{
			((char *)buf1)[i] = ((char *)buf2)[i];
			i++;
		}
	}
	return (buf1);
}
