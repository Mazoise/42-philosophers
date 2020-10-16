/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:32:58 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/16 15:37:18 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int		dead_philo(t_options *options, t_perso *perso, int t_death)
{
	if (t_death)
		usleep_opti(t_death);
	print_line(options, perso->id, MSG_DIE);
	return (0);
}

int		wait_for_fork(t_options *options, t_perso *perso)
{
	long	now;

	while (!perso->fork[0] || !perso->fork[1])
	{
		if (!(now = get_time()))
			return (0);
		if (now - perso->last_meal >= options->t_die)
			return (dead_philo(options, perso, 0));
		if (!take_forks(options, perso))
			return (0);
	}
	return (!options->table.death);
}

int		meal_time(t_options *options, t_perso *perso)
{
	print_line(options, perso->id, MSG_EAT);
	if (!(perso->last_meal = get_time()))
		return (0);
	if (options->t_eat <= options->t_die)
		usleep_opti(options->t_eat);
	else
		return (dead_philo(options, perso, options->t_die));
	pthread_mutex_lock(&options->mutex);
	options->table.fork[perso->fork_id[0]] = 0;
	options->table.fork[perso->fork_id[1]] = 0;
	pthread_mutex_unlock(&options->mutex);
	perso->fork[0] = 0;
	perso->fork[1] = 0;
	return (!options->table.death);
}

int		sleeping_time(t_options *options, t_perso *perso)
{
	print_line(options, perso->id, MSG_SLEEP);
	if (options->t_eat_sleep <= options->t_die)
		usleep_opti(options->t_sleep);
	else
		return (dead_philo(options, perso, options->t_sleep_think));
	return (!options->table.death);
}

int		thinking_time(t_options *options, t_perso *perso)
{
	print_line(options, perso->id, MSG_THINK);
	return (!options->table.death);
}
