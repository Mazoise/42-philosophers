/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:13:32 by mchardin          #+#    #+#             */
/*   Updated: 2021/02/03 12:15:11 by mchardin         ###   ########.fr       */
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
	return (1);
}

int
	define_philos(t_perso *perso, t_shared *shared)
{
	int		i;

	i = -1;
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_MSG);
	sem_unlink(SEM_STOP);
	if ((shared->sem.forks = sem_open(SEM_FORKS, O_CREAT, 00600,
		shared->nb_philos / 2)) == SEM_FAILED)
		return (0);
	shared->sem.msg = sem_open(SEM_MSG, O_CREAT, 00600, 1);
	if (shared->sem.msg == SEM_FAILED)
	{
		sem_close(shared->sem.forks);
		return (0);
	}
	shared->sem.stop = sem_open(SEM_STOP, O_CREAT, 00600, 0);
	if (shared->sem.stop == SEM_FAILED)
	{
		sem_close(shared->sem.forks);
		sem_close(shared->sem.msg);
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
	while (1)
		if (get_time() > perso->t_death)
		{
			print_death(shared, perso->id);
			return ;
		}
	return ;
}

int
	run_processes(t_shared *shared, t_perso *perso)
{
	int				i;
	pthread_t		philo[shared->nb_philos];

	i = -1;
	shared->start = get_time();
	while (++i < shared->nb_philos)
	{
		shared->philos[i] = fork();
		if (shared->philos[i] == -1)
			return (i);
		else if (shared->philos[i] == 0)
		{
			if (pthread_create(&philo[i], NULL, &life_thread, &perso[i]))
				return (i);
			death_check(shared, &perso[i]);
			exit (0);
		}
	}
	i = -1;
	while (++i < shared->nb_philos)
		sem_wait(shared->sem.stop);
	return (-1);
}

int
	main(int argc, char **argv)
{
	t_shared		shared;
	t_perso			*perso;
	int				processes;

	memset(&shared, 0, sizeof(shared));
	if (argc < 5 || argc > 6 || !fill_shared(&shared, argc, argv))
		return (1);
	shared.philos = ft_calloc(shared.nb_philos, sizeof(pid_t));
	perso = ft_calloc(shared.nb_philos, sizeof(t_perso));
	if (!shared.philos || !perso)
		return (1);
	if (!define_philos(perso, &shared))
		return (1);
	if ((processes = run_processes(&shared, perso)) >= 0)
	{
		clean_all(&shared, perso, processes - 1);
		return (1);
	}
	clean_all(&shared, perso, shared.nb_philos);
	return (0);
}
