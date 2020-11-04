/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:13:32 by mchardin          #+#    #+#             */
/*   Updated: 2020/11/04 14:54:05 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int		fill_options(t_options *options, int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isposnumber(argv[i]))
			return (0);
	}
	if (!(options->nb_philos = ft_atoi(argv[1])))
		return (0);
	options->t_die = ft_atoi(argv[2]) * 1000;
	options->t_eat = ft_atoi(argv[3]) * 1000;
	options->t_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		options->nb_meals = ft_atoi(argv[5]);
	else
		options->nb_meals = -1;
	options->table.still_eating = options->nb_philos;
	pthread_mutex_init(&options->mutex.end, NULL);
	pthread_mutex_init(&options->mutex.msg, NULL);
	return (1);
}

void	define_philos(t_perso *perso, t_options *options)
{
	int		i;

	i = -1;
	while (++i < options->nb_philos)
	{
		perso[i].options = options;
		perso[i].id = i;
		perso[i].fork_id[0] = i;
		perso[i].fork_id[1] = (i + 1) % options->nb_philos;
		perso[i].meals_left = options->nb_meals;
	}
}

void	*action_thread(void *tmp)
{
	t_perso			*perso;
	t_options		*options;

	perso = tmp;
	options = perso->options;
	if (!options->start && !(options->start = get_time()))
		return (NULL);
	perso->t_death = options->start + options->t_die;
	if (options->nb_philos == 1)
	{
		print_line(options, perso->id, MSG_FORK);
		while (1)
			;
	}
	if (perso->id % 2)
		usleep(options->t_eat / 2);
	else if (perso->id == options->nb_philos - 1)
		usleep((3 * options->t_eat) / 2);
	while (perso->meals_left < 0 ? 1 : perso->meals_left--)
		eat_sleep_think(options, perso);
	while (1)
		;
	return (NULL);
}

void	*life_thread(void *tmp)
{
	t_options		*options;
	t_perso			*perso;

	perso = tmp;
	options = perso->options;
	if (pthread_create(&options->philos[perso->id + options->nb_philos], NULL, &action_thread, perso))
			return (NULL);
	usleep(options->t_die / 2);
	while (1)
	{
		if (options->table.end)
			return (NULL);
		else if (get_time() > perso->t_death)
		{
			print_line(options, perso->id, MSG_DIE);
			return (NULL);
		}
	}
	return (NULL);
}

int		run_threads(pthread_t *philos, t_options *options, t_perso *perso)
{
	int		i;

	i = -1;
	while (++i < options->nb_philos)
		pthread_mutex_init(&options->mutex.fork[i], NULL);
	i = -1;
	if (!(options->start = get_time()))
		return (0);
	while (++i < options->nb_philos)
		if (pthread_create(&philos[i], NULL, &life_thread, &perso[i]))
			return (0);
	i = -1;
	while (++i < options->nb_philos)
		pthread_join(philos[i], NULL);
	return (1);
}

int		main(int argc, char **argv)
{
	t_options		options;
	t_perso			*perso;

	memset(&options, 0, sizeof(options));
	if (argc < 5 || argc > 6 || !fill_options(&options, argc, argv))
		return (0);
	if (!(options.philos = ft_calloc(options.nb_philos * 2, sizeof(pthread_t)))
		|| !(options.mutex.fork = ft_calloc(options.nb_philos, sizeof(pthread_mutex_t)))
		|| !(perso = ft_calloc(options.nb_philos, sizeof(t_perso))))
		return (0);
	define_philos(perso, &options);
	if (!run_threads(options.philos, &options, perso))
		return (0);
	usleep(10000);
	clean_all(&options, perso);
	return (0);
}
