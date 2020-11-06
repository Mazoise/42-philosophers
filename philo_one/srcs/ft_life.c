/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:32:58 by mchardin          #+#    #+#             */
/*   Updated: 2020/11/06 16:40:28 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int			dead_philo(t_shared *shared, t_perso *perso, int t_death)
{
	usleep_opti(get_time() + t_death);
	print_line(shared, perso->id, MSG_DIE);
	return (0);
}

void		eat_sleep_think(t_shared *shared, t_perso *perso)
{
	pthread_mutex_lock(&shared->mutex.fork[perso->fork_id[1]]);
	print_line(shared, perso->id, MSG_FORK);
	pthread_mutex_lock(&shared->mutex.fork[perso->fork_id[0]]);
	print_line(shared, perso->id, MSG_FORK);
	perso->t_death = get_time() + shared->t_die;
	print_line(shared, perso->id, MSG_EAT);
	usleep_opti(get_time() + shared->t_eat);
	if (!perso->meals_left)
	{
		pthread_mutex_lock(&shared->mutex.msg);
		shared->still_eating--;
		pthread_mutex_unlock(&shared->mutex.msg);
	}
	pthread_mutex_unlock(&shared->mutex.fork[perso->fork_id[0]]);
	pthread_mutex_unlock(&shared->mutex.fork[perso->fork_id[1]]);
	print_line(shared, perso->id, MSG_SLEEP);
	usleep_opti(get_time() + shared->t_sleep);
	print_line(shared, perso->id, MSG_THINK);
}

void		*life_thread(void *tmp)
{
	t_perso			*perso;
	t_shared		*shared;

	perso = tmp;
	shared = perso->shared;
	if (!shared->start && !(shared->start = get_time()))
		return (NULL);
	perso->t_death = shared->start + shared->t_die;
	if (shared->nb_philos == 1)
	{
		print_line(shared, perso->id, MSG_FORK);
		while (1)
			;
	}
	if (perso->id % 2)
		usleep(shared->t_eat / 2);
	else if (perso->id == shared->nb_philos - 1)
		usleep((3 * shared->t_eat) / 2);
	while (perso->meals_left < 0 ? 1 : perso->meals_left--)
		eat_sleep_think(shared, perso);
	while (1)
		;
	return (NULL);
}
