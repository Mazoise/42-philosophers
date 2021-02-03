/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:35:23 by mchardin          #+#    #+#             */
/*   Updated: 2021/02/03 11:27:03 by mchardin         ###   ########.fr       */
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

void
	clean_all(t_shared *shared, t_perso *perso, int processes)
{
	int		i;

	i = -1;
	if (processes > 0)
	while (++i < processes)
		kill(shared->philos[i], SIGKILL);
	free(shared->philos);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_MSG);
	sem_unlink(SEM_STOP);
	sem_close(shared->sem.msg);
	sem_close(shared->sem.forks);
	sem_close(shared->sem.stop);
	free(perso);
	return ;
}

void
	usleep_opti(long t_end)
{
	while (get_time() < t_end)
		usleep(100);
}
