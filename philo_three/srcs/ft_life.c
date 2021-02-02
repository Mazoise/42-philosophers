/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:32:58 by mchardin          #+#    #+#             */
/*   Updated: 2021/02/02 18:58:52 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void
	eat_sleep_think(t_shared *shared, t_perso *perso)
{
	sem_wait(shared->sem.forks);
	print_line(shared, perso->id, MSG_FORK);
	print_line(shared, perso->id, MSG_FORK);
	perso->t_death = get_time() + shared->t_die;
	print_line(shared, perso->id, MSG_EAT);
	usleep_opti(get_time() + shared->t_eat);
	if (!perso->meals_left)
		shared->still_eating--;
	sem_post(shared->sem.forks);
	print_line(shared, perso->id, MSG_SLEEP);
	usleep_opti(get_time() + shared->t_sleep);
	print_line(shared, perso->id, MSG_THINK);
}

void
	life_thread(void *tmp)
{
	t_perso			*perso;
	t_shared		*shared;

	perso = tmp;
	shared = perso->shared;
	perso->t_death = shared->start + shared->t_die;
	if (shared->nb_philos == 1)
	{
		print_line(shared, perso->id, MSG_FORK);
		while (!shared->stop)
			;
		exit(0);
	}
	if (perso->id % 2)
		usleep(shared->t_eat / 2);
	else if (perso->id == shared->nb_philos - 1)
		usleep((3 * shared->t_eat) / 2);
	while (!shared->stop && perso->meals_left--)
		eat_sleep_think(shared, perso);
	while (!shared->stop)
		;
	exit(0);
}
