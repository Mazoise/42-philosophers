/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:06:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/02/02 15:22:45 by mchardin         ###   ########.fr       */
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
	return (0);
}

void
	print_line(t_shared *shared, int id, int action)
{
	int		timestamp;
	// int		sem_value1;
	// int		sem_value2;

	timestamp = (get_time() - shared->start) / 1000;
	// sem_getvalue(shared->sem.forks, &sem_value1);
	// sem_getvalue(shared->sem.msg, &sem_value2);
	// printf("FORKS : %d, MSG: %d", sem_value1, sem_value2); //W
	sem_wait(shared->sem.msg);
	if (!shared->stop && shared->still_eating)
	{
		ft_putnbrphilo(timestamp);
		ft_putnbrphilo(id + 1);
		write(1, msg_action(action), msg_len(action));
	}
	sem_post(shared->sem.msg);
	return ;
}

void
	print_death(t_shared *shared, int id)
{
	int		timestamp;

	timestamp = (get_time() - shared->start) / 1000;
	sem_wait(shared->sem.msg);
	shared->stop = 1;
	ft_putnbrphilo(timestamp);
	ft_putnbrphilo(id + 1);
	write(1, AC_DIE, 5);
	sem_post(shared->sem.msg);
	return ;
}
