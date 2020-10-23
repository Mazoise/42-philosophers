/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:06:40 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/23 19:12:12 by mchardin         ###   ########.fr       */
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

void	*print_thread(void *tmp)
{
	t_print			*print;

	print = tmp;
	pthread_mutex_lock(&print->options->mutex.msg);
	if (print->options->table.death)
	{
		pthread_mutex_unlock(&print->options->mutex.msg);
		free (print);
		return (0);
	}
	ft_putnbrpos_fd((print->time - print->options->start) / 1000, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbrpos_fd(print->id + 1, 1);
	ft_putstr_fd(msg_action(print->action), 1);
	if (print->action == MSG_DIE)
		print->options->table.death = 1;
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
	if (action == MSG_DIE)
		pthread_join(printer, NULL);
	return (1);
}
