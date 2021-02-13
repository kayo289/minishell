/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:56:03 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/02/13 21:29:55 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	int i;
	int j;

	i = 0;
	if (to_find[i] == '\0')
		return ((char*)str);
	while (str[i] && n > 0)
	{
		j = 0;
		while (str[i + j] && str[i + j] == to_find[j] && j < (int)n)
		{
			if (to_find[j + 1] == '\0')
				return ((char*)&str[i]);
			j++;
		}
		i++;
		n--;
	}
	return (NULL);
}
