/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:13:32 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/16 15:47:08 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int		fill_options(t_options *options, int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isnumber(argv[i]) || argv[i][0] == '-')
			return (0);
	}
	if (!(options->nb_philos = ft_atoi(argv[1])))
		return (0);
	options->t_die = ft_atoi(argv[2]);
	options->t_eat = ft_atoi(argv[3]);
	options->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		options->nb_meals = ft_atoi(argv[5]);
	else
		options->nb_meals = -1;
	options->t_eat_sleep = options->t_eat + options->t_sleep;
	options->t_think = options->t_die - options->t_eat_sleep;
	options->t_two_meals = 2 * options->t_eat;
	options->t_sleep_think = options->t_sleep + options->t_think;
	pthread_mutex_init(&options->mutex, NULL);
	return (1);
}

int		define_philo(t_options *options, t_perso *perso)
{
	pthread_mutex_lock(&options->mutex);
	perso->id = options->table.seat++;
	pthread_mutex_unlock(&options->mutex);
	if (options->nb_philos == 1)
		return (dead_philo(options, perso, options->t_die));
	if (perso->id % 2)
		usleep(1000);
	else if (perso->id  == options->nb_philos - 1)
		usleep(2000);
	perso->fork_id[0] = perso->id == 0 ?
	options->nb_philos - 1 : perso->id - 1;
	perso->fork_id[1] = perso->id;
	perso->last_meal = options->start;
	perso->meals_left = options->nb_meals;
	return (1);
}

void	*create_life(void *tmp)
{
	t_options		*options;
	t_perso			perso;

	options = tmp;
	memset(&perso, 0, sizeof(perso));
	if (!define_philo(options, &perso))
		return (NULL);
	while (perso.meals_left < 0 ? 1 : perso.meals_left--)
	{
		if (!wait_for_fork(options, &perso))
			return (NULL);
		if (!meal_time(options, &perso))
			return (NULL);
		if (!sleeping_time(options, &perso))
			return (NULL);
		if (!thinking_time(options, &perso))
			return (NULL);
	}
	return (NULL);
}

int		run_threads(pthread_t *philos, t_options *options)
{
	int		i;

	i = -1;
		if (!(options->start = get_time()))
		return (0);
	while (++i < options->nb_philos)
		if (pthread_create(&philos[i], NULL, &create_life, options))
			return (0);
	pthread_join(philos[0], NULL);
	return (1);
}

int		main(int argc, char **argv)
{
	t_options		options;

	memset(&options, 0, sizeof(options));
	if (argc < 5 || argc > 6 || !fill_options(&options, argc, argv))
		return (0);
	if (!(options.philos = ft_calloc(options.nb_philos, sizeof(pthread_t)))
		|| !(options.table.fork = ft_calloc(options.nb_philos, sizeof(int))))
		return (0);
	if (!run_threads(options.philos, &options))
		return (0);
	free(options.philos);
	free(options.table.fork);
}
