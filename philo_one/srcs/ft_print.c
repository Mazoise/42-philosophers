/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:06:40 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/25 19:15:16 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

char	*msg_action(int action)
{
	if (action == MSG_FORK)
		return (AC_FORK);
	if (action == MSG_DIE)
		return (AC_DIE);
	if (action == MSG_EAT)
		return (AC_EAT);
	if (action == MSG_SLEEP)
		return (AC_SLEEP);
	if (action == MSG_THINK)
		return (AC_THINK);
	return (NULL);
}

int		msg_len(int action)
{
	if (action == MSG_FORK)
		return (17);
	if (action == MSG_DIE)
		return (6);
	if (action == MSG_EAT)
		return (10);
	if (action == MSG_SLEEP)
		return (12);
	if (action == MSG_THINK)
		return (12);
	return (0);
}

void	*print_thread(void *tmp)
{
	t_print			*print;

	print = tmp;
	pthread_mutex_lock(&print->options->mutex.msg);
	if (print->options->table.end)
	{
		pthread_mutex_unlock(&print->options->mutex.msg);
		free (print);
		return (NULL);
	}
	pthread_mutex_unlock(&print->options->mutex.seat);
	ft_putnbrphilo_fd((print->time - print->options->start) / 1000, 1);
	ft_putnbrphilo_fd(print->id + 1, 1);
	write(1, msg_action(print->action), msg_len(print->action));
	if (print->action == MSG_DIE || (print->action == MSG_EAT && !print->options->table.finished_eating))
		print->options->table.end = 1;
	pthread_mutex_unlock(&print->options->mutex.msg);
	free (print);
	return (NULL);
}

int		print_line(t_options *options, int id, int action)
{
	t_print			*print;
	pthread_t		printer;

	if (!(print = malloc(sizeof(t_print))))
		return (0);
	print->time = options->time;
	print->action = action;
	print->options = options;
	print->id = id;
	if (pthread_create(&printer, NULL, &print_thread, print))
		return (0);
	if (action == MSG_DIE || (!options->table.finished_eating && action == MSG_EAT))
		pthread_join(printer, NULL);
	return (1);
}
