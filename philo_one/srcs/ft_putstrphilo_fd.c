/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrphilo_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:14:41 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/25 16:50:29 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_philo.h"

void	ft_putstrphilo_fd(char *s, int fd, int len)
{
	if (!s)
		return ;
	write(fd, s, len);
}
