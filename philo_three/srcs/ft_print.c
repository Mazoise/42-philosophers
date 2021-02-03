/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:06:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/02/03 14:09:35 by mchardin         ###   ########.fr       */
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

void
	print_line(int timestamp, int id, int action, int philo_len)
{
	char		line[39];
	int			end;
	int			i;

	i = 12 + philo_len;
	end = i;
	line[i] = ' ';
	while (--i >= 12)
	{
		line[i] = '0' + id % 10;
		id = id / 10;
	}
	line[i] = ' ';
	while (--i >= 0)
	{
		line[i] = '0' + timestamp % 10;
		timestamp = timestamp / 10;
	}
	end += ft_strcpyphilo(&line[end + 1], msg_action(action));
	write(1, line, end + 1);
}

void
	print_event(t_shared *shared, int id, int action)
{
	int		timestamp;

	if (sem_wait(shared->sem.msg) < 0)
		return ;
	timestamp = (get_time() - shared->start) / 1000;
	print_line(timestamp, id + 1, action, shared->len_nb_philos);
	sem_post(shared->sem.msg);
	return ;
}

void
	print_death(t_shared *shared, int id)
{
	int		timestamp;
	int		i;

	i = -1;
	if (sem_wait(shared->sem.msg) < 0)
		return ;
	timestamp = (get_time() - shared->start) / 1000;
	print_line(timestamp, id + 1, MSG_DIE, shared->len_nb_philos);
	while (++i < shared->nb_philos)
		sem_post(shared->sem.stop);
	return ;
}
