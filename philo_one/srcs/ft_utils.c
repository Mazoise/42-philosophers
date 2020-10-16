/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:35:23 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/16 15:33:45 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

long		get_time()
{
	struct timeval  now;

	if (gettimeofday(&now, NULL) < 0)
		return (0);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void		usleep_opti(int time)
{
	int		time2;

	time2 = time * 250;
	usleep(time2);
	usleep(time2);
	usleep(time2);
	usleep(time2);
}

int		take_forks(t_options *options, t_perso *perso)
{
	int		i;

	i = -1;
	while (++i < 2)
	{
		pthread_mutex_lock(&options->mutex);
		if (!options->table.fork[perso->fork_id[i]])
		{
			options->table.fork[perso->fork_id[i]] = 1;
			pthread_mutex_unlock(&options->mutex);
			perso->fork[i] = 1;
			print_line(options, perso->id, MSG_FORK);
		}
		else
			pthread_mutex_unlock(&options->mutex);
	}
	return (!options->table.death);
}
