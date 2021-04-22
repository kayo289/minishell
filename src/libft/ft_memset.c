/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 07:47:51 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/04/22 23:40:57 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memset(void *buf, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)buf)[i] = (char)c;
		i++;
	}
	return (buf);
}
