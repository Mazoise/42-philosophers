/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:13:32 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/25 19:07:29 by mchardin         ###   ########.fr       */
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
	options->t_die = ft_atoi(argv[2]) * 1000;
	options->t_eat = ft_atoi(argv[3]) * 1000;
	options->t_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		options->nb_meals = ft_atoi(argv[5]);
	else
		options->nb_meals = -1;
	options->table.finished_eating = options->nb_philos;
	pthread_mutex_init(&options->mutex.end, NULL);
	pthread_mutex_init(&options->mutex.msg, NULL);
	pthread_mutex_init(&options->mutex.seat, NULL);
	return (1);
}

int		define_philo(t_options *options, t_perso *perso)
{
	pthread_mutex_lock(&options->mutex.seat);
	perso->id = options->table.seat++;
	pthread_mutex_unlock(&options->mutex.seat);
	if (options->nb_philos == 1)
		return (dead_philo(options, perso, options->t_die));
	perso->fork_id[0] = perso->id;
	perso->fork_id[1] = (perso->id + 1) % options->nb_philos;
	perso->last_meal = options->start;
	perso->meals_left = options->nb_meals;
	perso->options = options;
	return (1);
}

void	*action_thread(void *tmp)
{
	t_perso			*perso;
	t_options		*options;

	perso = tmp;
	options = perso->options;
	if (perso->id % 2)
		usleep(1000);
	else if (perso->id  == options->nb_philos - 1)
		usleep(2000);
	while (perso->meals_left < 0 ? 1 : perso->meals_left--)
		eat_sleep_think(options, perso);
	while (1)
		;
	return (NULL);
}

void	*life_thread(void *tmp)
{
	t_options		*options;
	t_perso			perso;
	pthread_t		ac_thread;

	options = tmp;
	memset(&perso, 0, sizeof(perso));
	if (!define_philo(options, &perso))
		return (NULL);
	if (pthread_create(&ac_thread, NULL, &action_thread, &perso))
			return (NULL);
	while (1)
	{
		if (options->table.end)
		{
			usleep(100000);	
			return (NULL);
		}
		else if (options->time - perso.last_meal > options->t_die)
		{
			print_line(options, perso.id, MSG_DIE);
			usleep(100000);
			return (NULL);
		}
	}
	return (NULL);
}

int		run_threads(pthread_t *philos, t_options *options)
{
	int		i;

	i = -1;
	while (++i < options->nb_philos)
		pthread_mutex_init(&options->mutex.fork[i], NULL);
	i = 0;
	if (pthread_create(&philos[0], NULL, &time_thread, options))
		return (0);
	if (!(options->start = get_time()))
		return (0);
	options->time = options->start;
	while (++i <= options->nb_philos)
		if (pthread_create(&philos[i], NULL, &life_thread, options))
			return (0);
	i = 0;
	while (++i <= options->nb_philos)
		pthread_join(philos[i], NULL);
	return (1);
}

void	clean_all(t_options *options)
{
	int		i;

	i = -1;
	free(options->philos);
	pthread_mutex_destroy(&options->mutex.seat);
	pthread_mutex_destroy(&options->mutex.end);
	pthread_mutex_destroy(&options->mutex.msg);
	while (++i < options->nb_philos)
		pthread_mutex_destroy(&options->mutex.fork[i]);
	free(options->mutex.fork);
	return ;
}

int		main(int argc, char **argv)
{
	t_options		options;

	memset(&options, 0, sizeof(options));
	if (argc < 5 || argc > 6 || !fill_options(&options, argc, argv))
		return (0);
	if (!(options.philos = ft_calloc(options.nb_philos + 1, sizeof(pthread_t)))
		|| !(options.mutex.fork = ft_calloc(options.nb_philos, sizeof(pthread_mutex_t))))
		return (0);
	if (!run_threads(options.philos, &options))
		return (0);
	usleep(10000);
	clean_all(&options);
	return (0);
}
