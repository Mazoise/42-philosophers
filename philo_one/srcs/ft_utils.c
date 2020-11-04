/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:35:23 by mchardin          #+#    #+#             */
/*   Updated: 2020/11/04 14:16:03 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

long 	get_time()
{
	struct timeval  now;

	if (gettimeofday(&now, NULL) < 0)
		return (0);
	return (now.tv_sec * 1000000 + now.tv_usec);
}

void	clean_all(t_options *options, t_perso *perso)
{
	int		i;

	i = -1;
	free(options->philos);
	pthread_mutex_destroy(&options->mutex.end);
	pthread_mutex_destroy(&options->mutex.msg);
	while (++i < options->nb_philos)
		pthread_mutex_destroy(&options->mutex.fork[i]);
	free(options->mutex.fork);
	free(perso);
	return ;
}

void		usleep_opti(long t_end)
{
	while (get_time() < t_end)
		usleep(50);
}
