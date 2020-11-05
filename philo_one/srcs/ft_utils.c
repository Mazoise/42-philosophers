/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:35:23 by mchardin          #+#    #+#             */
/*   Updated: 2020/11/05 18:04:18 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

long		get_time(void)
{
	struct timeval		now;

	if (gettimeofday(&now, NULL) < 0)
		return (0);
	return (now.tv_sec * 1000000 + now.tv_usec);
}

void		clean_all(t_shared *shared, t_perso *perso)
{
	int		i;

	i = -1;
	free(shared->philos);
	pthread_mutex_destroy(&shared->mutex.end);
	pthread_mutex_destroy(&shared->mutex.msg);
	while (++i < shared->nb_philos)
		pthread_mutex_destroy(&shared->mutex.fork[i]);
	free(shared->mutex.fork);
	free(perso);
	return ;
}

void		usleep_opti(long t_end)
{
	while (get_time() < t_end)
		usleep(50);
}
