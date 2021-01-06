/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:06:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/01/06 16:59:00 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

char
	*msg_action(int action)
{
	if (action == MSG_FORK)
		return (AC_FORK);
	else if (action == MSG_SLEEP)
		return (AC_SLEEP);
	else if (action == MSG_THINK)
		return (AC_THINK);
	else if (action == MSG_EAT)
		return (AC_EAT);
	else if (action == MSG_DIE)
		return (AC_DIE);
	return (NULL);
}

int
	msg_len(int action)
{
	if (action == MSG_FORK)
		return (17);
	else if (action == MSG_SLEEP || action == MSG_THINK)
		return (12);
	else if (action == MSG_EAT)
		return (10);
	else if (action == MSG_DIE)
		return (5);
	return (0);
}

int
	print_line(t_shared *shared, int id, int action)
{
	int		timestamp;

	timestamp = (get_time() - shared->start) / 1000;
	pthread_mutex_lock(&shared->mutex.msg);
	if (!shared->still_eating && action != MSG_DIE)
		while (1)
			;
	ft_putnbrphilo(timestamp);
	ft_putnbrphilo(id + 1);
	write(1, msg_action(action), msg_len(action));
	if (action != MSG_DIE)
		pthread_mutex_unlock(&shared->mutex.msg);
	return (1);
}
