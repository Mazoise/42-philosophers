/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:06:40 by mchardin          #+#    #+#             */
/*   Updated: 2020/11/04 14:38:44 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

char	*msg_action(int action)
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

int		msg_len(int action)
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

// void	*print_thread(void *tmp)
// {
// 	t_print			*print;

// 	print = tmp;
// 	pthread_mutex_lock(&print->options->mutex.msg);
// 	if (print->options->table.end)
// 	{
// 		pthread_mutex_unlock(&print->options->mutex.msg);
// 		free (print);
// 		return (NULL);
// 	}
// 	ft_putnbrphilo((print->time - print->options->start) / 1000);
// 	ft_putnbrphilo(print->id + 1);
// 	write(1, msg_action(print->action), msg_len(print->action));
// 	if (print->action == MSG_DIE)
// 		print->options->table.end = 1;
// 	pthread_mutex_unlock(&print->options->mutex.msg);
// 	free (print);
// 	return (NULL);
// }

// int		print_line(t_options *options, int id, int action)
// {
// 	t_print			*print;
// 	pthread_t		printer;

// 	if (!(print = malloc(sizeof(t_print))))
// 		return (0);
// 	print->time = get_time();
// 	print->action = action;
// 	print->options = options;
// 	print->id = id;
// 	if (pthread_create(&printer, NULL, &print_thread, print))
// 		return (0);
// 	if (action == MSG_DIE)
// 		pthread_join(printer, NULL);
// 	return (1);
// }

int		print_line(t_options *options, int id, int action)
{
	int		timestamp;

	timestamp = (get_time() - options->start) / 1000;
	pthread_mutex_lock(&options->mutex.msg);
	if (options->table.end)
	{
		pthread_mutex_unlock(&options->mutex.msg);
		return (1); //useless now 
	}
	ft_putnbrphilo(timestamp);
	ft_putnbrphilo(id + 1);
	write(1, msg_action(action), msg_len(action));
	if (action == MSG_DIE)
		options->table.end = 1;
	pthread_mutex_unlock(&options->mutex.msg);
	return (1);
}
