/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:16:17 by mchardin          #+#    #+#             */
/*   Updated: 2021/01/06 18:14:17 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int
	ft_amalloc(void **dest, size_t size)
{
	*dest = malloc(size);
	if (!(*dest))
		return (0);
	return (1);
}

void
	ft_char_nbr(char *str, long n, int lg_n)
{
	str[lg_n] = 0;
	while (n > 9)
	{
		str[--lg_n] = n % 10 + '0';
		n = n / 10;
	}
	str[0] = n % 10 + '0';
}

int
	ft_length_n(int n)
{
	int	i;

	i = 0;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char
	*ft_itoa(int n)
{
	int			i;
	long		long_n;
	char		*str;
	int			sign;
	int			length_n;

	i = 0;
	sign = 0;
	length_n = ft_length_n(n);
	long_n = n;
	if (n < 0)
	{
		sign = 1;
		long_n = -1 * long_n;
	}
	if (!ft_amalloc((void *)&str, sizeof(char) * (length_n + sign + 1)))
		return (0);
	if (sign == 1)
	{
		str[i] = '-';
		i++;
	}
	ft_char_nbr(&str[i], long_n, length_n);
	return (str);
}
