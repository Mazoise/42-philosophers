/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:13:32 by mchardin          #+#    #+#             */
/*   Updated: 2020/11/06 16:40:51 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int		fill_shared(t_shared *shared, int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isposnumber(argv[i]))
			return (0);
	}
	if (!(shared->nb_philos = ft_atoi(argv[1])))
		return (0);
	shared->t_die = ft_atoi(argv[2]) * 1000;
	shared->t_eat = ft_atoi(argv[3]) * 1000;
	shared->t_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		shared->nb_meals = ft_atoi(argv[5]);
	else
		shared->nb_meals = -1;
	shared->still_eating = shared->nb_philos;
	pthread_mutex_init(&shared->mutex.end, NULL);
	pthread_mutex_init(&shared->mutex.msg, NULL);
	return (1);
}

void	define_philos(t_perso *perso, t_shared *shared)
{
	int		i;

	i = -1;
	while (++i < shared->nb_philos)
	{
		perso[i].shared = shared;
		perso[i].id = i;
		perso[i].fork_id[0] = i;
		perso[i].fork_id[1] = (i + 1) % shared->nb_philos;
		perso[i].meals_left = shared->nb_meals;
	}
}
void		*death_thread(void *tmp)
{
	t_perso			*perso;
	t_shared		*shared;
	int				i;

	i = -1;
	perso = tmp;
	shared = perso->shared;
	while (++i < shared->nb_philos)
		if (pthread_create(&shared->philos[i], NULL, &life_thread, &perso[i]))
			return (NULL);
	usleep(shared->t_die / 2);
	while (1)
		if (end_of_philo(perso, shared))
			return (NULL);
	return (NULL);
}

int		run_threads(pthread_t *philos, t_shared *shared, t_perso *perso)
{
	int		i;

	i = -1;
	while (++i < shared->nb_philos)
		pthread_mutex_init(&shared->mutex.fork[i], NULL);
	if (pthread_create(&philos[shared->nb_philos], NULL, &death_thread, perso))
			return (0);
	pthread_join(philos[shared->nb_philos], NULL);
	return (1);
}

int		main(int argc, char **argv)
{
	t_shared		shared;
	t_perso			*perso;

	memset(&shared, 0, sizeof(shared));
	if (argc < 5 || argc > 6 || !fill_shared(&shared, argc, argv))
		return (0);
	if (!(shared.philos = ft_calloc(shared.nb_philos + 1, sizeof(pthread_t)))
		|| !(shared.mutex.fork =
			ft_calloc(shared.nb_philos, sizeof(pthread_mutex_t)))
		|| !(perso = ft_calloc(shared.nb_philos, sizeof(t_perso))))
		return (0);
	define_philos(perso, &shared);
	if (!run_threads(shared.philos, &shared, perso))
		return (0);
	usleep(10000);
	clean_all(&shared, perso);
	return (0);
}
