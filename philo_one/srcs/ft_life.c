/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:32:58 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/30 17:24:55 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int			dead_philo(t_options *options, t_perso *perso, int t_death)
{
	if (t_death)
		usleep(t_death);
	print_line(options, perso->id, MSG_DIE);
	return (0);
}

void		eat_sleep_think(t_options *options, t_perso *perso)
{
	pthread_mutex_lock(&options->mutex.fork[perso->fork_id[0]]);
	print_line(options, perso->id, MSG_FORK);
	pthread_mutex_lock(&options->mutex.fork[perso->fork_id[1]]);
	print_line(options, perso->id, MSG_FORK);
	perso->t_last_meal = options->time;
	print_line(options, perso->id, MSG_EAT);
	perso->t_end_usleep = perso->t_last_meal + options->t_eat;
	while (options->time < perso->t_end_usleep)
		usleep(100);
	if (!perso->meals_left)
	{
		pthread_mutex_lock(&options->mutex.msg);
		options->table.still_eating--;
		if (!options->table.still_eating)
			options->table.end = 1;
		pthread_mutex_unlock(&options->mutex.msg);
	}
	pthread_mutex_unlock(&options->mutex.fork[perso->fork_id[0]]);
	pthread_mutex_unlock(&options->mutex.fork[perso->fork_id[1]]);
	print_line(options, perso->id, MSG_SLEEP);
	perso->t_end_usleep = options->time + options->t_sleep;
	while (options->time < perso->t_end_usleep)
		usleep(100);
	print_line(options, perso->id, MSG_THINK);
	usleep(20);
}
