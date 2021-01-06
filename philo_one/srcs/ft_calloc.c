/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:49:11 by mchardin          #+#    #+#             */
/*   Updated: 2021/01/06 18:19:55 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void
	*ft_calloc(size_t count, size_t size)
{
	unsigned char		*str;
	size_t				i;

	i = 0;
	str = malloc(count * size);
	if (!str)
		return (0);
	while (i < size * count)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
