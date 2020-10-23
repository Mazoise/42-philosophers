/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrpos_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:25:40 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/23 19:02:53 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_philo.h"

void	ft_putnbrpos_fd(long n, int fd)
{
	char	nb[11];
	int		i;

	i = 10;
	nb[10] = 0;
	while (n > 0)
	{
		nb[i] = '0' + n % 10;
		n = n / 10;
		i--;
	}
	ft_putstr_fd(&nb[++i], fd);
}
