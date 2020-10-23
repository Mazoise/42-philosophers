/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:32:58 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/23 19:06:16 by mchardin         ###   ########.fr       */
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
	print_line(options, perso->id, MSG_EAT);
	perso->last_meal = options->time;
	usleep(options->t_eat);
	pthread_mutex_unlock(&options->mutex.fork[perso->fork_id[0]]);
	pthread_mutex_unlock(&options->mutex.fork[perso->fork_id[1]]);
	print_line(options, perso->id, MSG_SLEEP);
	usleep(options->t_sleep);
	print_line(options, perso->id, MSG_THINK);
}
