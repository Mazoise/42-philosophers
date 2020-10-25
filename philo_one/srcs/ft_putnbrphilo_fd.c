/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrphilo_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:25:40 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/25 16:52:16 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_philo.h"

void	ft_putnbrphilo_fd(unsigned int n, int fd)
{
	char	nb[12];
	int		i;

	i = 9;
	nb[11] = 0;
	nb[10] = ' ';
	while (n > 9)
	{
		nb[i] = '0' + n % 10;
		n = n / 10;
		i--;
	}
	nb[i] = '0' + n % 10;
	write(fd, &nb[i], 11 - i);
}
