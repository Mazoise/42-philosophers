/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:35:23 by mchardin          #+#    #+#             */
/*   Updated: 2021/02/03 14:08:58 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

long
	get_time(void)
{
	struct timeval		now;

	if (gettimeofday(&now, NULL) < 0)
		return (0);
	return (now.tv_sec * 1000000 + now.tv_usec);
}

int
	end_of_philo(t_perso *perso, t_shared *shared)
{
	int		i;

	i = -1;
	while (++i < shared->nb_philos)
	{
		if (get_time() > perso[i].t_death)
		{
			print_death(shared, perso[i].id);
			return (1);
		}
	}
	if (!shared->still_eating)
	{
		shared->stop = 1;
		return (1);
	}
	return (0);
}

void
	clean_all(t_shared *shared, t_perso *perso, int threads)
{
	int		i;

	i = -1;
	if (threads > 0)
		while (++i < threads)
			pthread_join(shared->philos[i], NULL);
	free(shared->philos);
	pthread_mutex_destroy(&shared->mutex.msg);
	while (++i < shared->nb_philos)
		pthread_mutex_destroy(&shared->mutex.fork[i]);
	free(shared->mutex.fork);
	free(perso);
	return ;
}

void
	usleep_opti(long t_end)
{
	while (get_time() < t_end)
		usleep(50);
}
