/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:13:32 by mchardin          #+#    #+#             */
/*   Updated: 2021/02/03 12:57:44 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int
	fill_shared(t_shared *shared, int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isposnumber(argv[i]))
			return (0);
	}
	shared->nb_philos = ft_atoi(argv[1]);
	if (!shared->nb_philos)
		return (0);
	i = -1;
	while (argv[1][++i])
		shared->len_nb_philos++;
	shared->t_die = ft_atoi(argv[2]) * 1000;
	shared->t_eat = ft_atoi(argv[3]) * 1000;
	shared->t_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		shared->nb_meals = ft_atoi(argv[5]);
	else
		shared->nb_meals = -1;
	shared->still_eating = shared->nb_philos;
	return (1);
}

int
	define_philos(t_perso *perso, t_shared *shared)
{
	int		i;

	i = -1;
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_MSG);
	if ((shared->sem.forks = sem_open(SEM_FORKS, O_CREAT, 00600,
		shared->nb_philos / 2)) == SEM_FAILED)
		return (0);
	shared->sem.msg = sem_open(SEM_MSG, O_CREAT, 00600, 1);
	if (shared->sem.msg == SEM_FAILED)
	{
		sem_close(shared->sem.forks);
		return (0);
	}
	while (++i < shared->nb_philos)
	{
		perso[i].shared = shared;
		perso[i].id = i;
		perso[i].meals_left = shared->nb_meals;
	}
	return (1);
}

void
	death_check(t_shared *shared, t_perso *perso)
{
	usleep(shared->t_die / 2);
	while (!end_of_philo(perso, shared))
		;
	return ;
}

int
	run_threads(t_shared *shared, t_perso *perso)
{
	int		i;

	i = -1;
	shared->start = get_time();
	while (++i < shared->nb_philos)
		if (pthread_create(&shared->philos[i], NULL, &life_thread, &perso[i]))
			return (i);
	death_check(shared, perso);
	return (-1);
}

int
	main(int argc, char **argv)
{
	t_shared		shared;
	t_perso			*perso;
	int				threads;

	memset(&shared, 0, sizeof(shared));
	if (argc < 5 || argc > 6 || !fill_shared(&shared, argc, argv))
		return (1);
	shared.philos = ft_calloc(shared.nb_philos, sizeof(pthread_t));
	perso = ft_calloc(shared.nb_philos, sizeof(t_perso));
	if (!shared.philos || !perso)
		return (1);
	if (!define_philos(perso, &shared))
		return (1);
	if ((threads = run_threads(&shared, perso)) >= 0)
	{
		clean_all(&shared, perso, threads - 1);
		return (1);
	}
	clean_all(&shared, perso, shared.nb_philos);
	return (0);
}
