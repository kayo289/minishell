/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 23:16:05 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/04/22 23:11:15 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ans;
	size_t	total;

	total = count * size;
	ans = malloc(total);
	if (!ans)
		return (NULL);
	ft_memset(ans, 0, total);
	return (ans);
}
