/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:13:32 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/11 21:59:04 by mchardin         ###   ########.fr       */
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
	if (!(options->number_of_philosophers = ft_atoi(argv[1])))
		return (0);
	options->time_to_die = 1000 * ft_atoi(argv[2]);
	options->time_to_eat = 1000 * ft_atoi(argv[3]);
	options->time_to_sleep = 1000 * ft_atoi(argv[4]);
	if (argc == 6)
		options->number_of_meals = ft_atoi(argv[5]);
	else
		options->number_of_meals = -1;
	options->time_to_eat_sleep = options->time_to_eat + options->time_to_sleep;
	options->time_to_think = options->time_to_die - options->time_to_eat_sleep;
	options->time_two_meals = 2 * options->time_to_eat;
	options->time_to_sleep_think = options->time_to_sleep + options->time_to_think;
	options->table.seat = 0;
	options->table.death = 0;
	pthread_mutex_init(&options->mutex, NULL);
	return (1);
}

void	*print_thread(void *tmp_print)
{
	t_print			*print;
	struct timeval  now;
	char			*tmp;
	char			*tmp2;
	char			*str;

	print = tmp_print;
	ft_putstr_fd(print->action, 1);
	tmp = ft_itoa(print->id + 1);
	tmp2 = ft_strjoin(tmp, print->action);
	free(tmp);
	tmp = ft_strjoin(" ", tmp2);
	free(tmp2);
	if (gettimeofday(&now, NULL) < 0)
		return (NULL);
	tmp2 = ft_itoa((now.tv_sec - print->start.tv_sec) * 1000
	+ (now.tv_usec - print->start.tv_usec) / 1000);
	str = ft_strjoin(tmp2, tmp);
	// ft_putstr_fd(str, 1);
	free(tmp);
	free(tmp2);
	free(str);
	return (NULL);
}

int		print_line(t_options *options, int id, char *action, int death)
{
	t_print			print;

	if (death == 1)
		return (0);
	print.action = action;
	print.start = options->start;
	print.id = id;
	if (pthread_create(&options->prints[id], NULL, &print_thread, &print))
			return (0);
	pthread_detach(options->prints[id]);
	return (1);
}

int		dead_philo(t_options *options, t_perso *perso, int time_death)
{
	if (time_death)
		usleep(time_death);
	pthread_mutex_lock(&options->mutex);
	print_line(options, perso->id, AC_DIE, options->table.death);
	options->table.death = 1;
	pthread_mutex_unlock(&options->mutex);
	return (0);
}

int		define_philosopher(t_options *options, t_perso *perso)
{
	pthread_mutex_lock(&options->mutex);
	perso->id = options->table.seat++;
	pthread_mutex_unlock(&options->mutex);
	if (options->number_of_philosophers == 1)
		return (dead_philo(options, perso, options->time_to_die));
	if (perso->id % 2)
		usleep(options->time_to_eat / 2);
	perso->forks[0] = perso->id == 0 ?
	options->number_of_philosophers - 1 : perso->id - 1;
	perso->forks[1] = perso->id;
	perso->last_meal = options->start;
	perso->meals_left = options->number_of_meals;
	return (1);
}

int		wait_for_fork(t_options *options, t_perso *perso)
{
	struct timeval	now;

	pthread_mutex_lock(&options->mutex);
	while (options->table.fork[perso->forks[0]]
	|| options->table.fork[perso->forks[1]])
	{
		pthread_mutex_unlock(&options->mutex);
		if (gettimeofday(&now, NULL) < 0)
			return (0);
		if ((now.tv_sec - perso->last_meal.tv_sec) * 1000000
+ (now.tv_usec - perso->last_meal.tv_usec) >= options->time_to_die)
			return (dead_philo(options, perso, 0));
		pthread_mutex_lock(&options->mutex);
	}
	return (1);
}

int		meal_time(t_options *options, t_perso *perso)
{
	options->table.fork[perso->forks[0]] = 1;
	options->table.fork[perso->forks[1]] = 1;
	if (!print_line(options, perso->id, AC_FORK, options->table.death)
	|| !print_line(options, perso->id, AC_FORK, options->table.death)
	|| !print_line(options, perso->id, AC_EAT, options->table.death))
	{
		pthread_mutex_unlock(&options->mutex);
		return (0);
	}
	pthread_mutex_unlock(&options->mutex);
	if (gettimeofday(&perso->last_meal, NULL) < 0)
		return (0);
	if (options->time_to_eat < options->time_to_die)
		usleep(options->time_to_eat);
	else
		return (dead_philo(options, perso, options->time_to_die));
	pthread_mutex_lock(&options->mutex);
	options->table.fork[perso->forks[0]] = 0;
	options->table.fork[perso->forks[1]] = 0;
	pthread_mutex_unlock(&options->mutex);
	return (1);
}

int		sleeping_time(t_options *options, t_perso *perso)
{
	pthread_mutex_lock(&options->mutex);
	if (!print_line(options, perso->id, AC_SLEEP, options->table.death))
		return (0);
	pthread_mutex_unlock(&options->mutex);
	if (options->time_to_eat_sleep < options->time_to_die)
		usleep(options->time_to_sleep);
	else
		return (dead_philo(options, perso, options->time_to_sleep_think));
	return (1);
}

int		thinking_time(t_options *options, t_perso *perso)
{
	pthread_mutex_lock(&options->mutex);
	if (!print_line(options, perso->id, AC_THINK, options->table.death))
		return (0);
	pthread_mutex_unlock(&options->mutex);
	usleep(options->time_to_think / 2);
	return (1);
}

void	*create_life(void *tmp)
{
	t_options		*options;
	t_perso			perso;

	options = tmp;
	if (!define_philosopher(options, &perso))
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
	void	*ret;

	i = -1;
	if (gettimeofday(&options->start, NULL) < 0)
		return (0);
	while (++i < options->number_of_philosophers)
	{
		if (pthread_create(&philos[i], NULL, &create_life, options))
			return (0);
	}
	pthread_join(philos[0], &ret);
	return (1);
}

int		main(int argc, char **argv)
{
	t_options		options;

	if (argc < 5 || argc > 6 || !fill_options(&options, argc, argv))
		return (0);
	if (!(options.philos = ft_calloc(options.number_of_philosophers, sizeof(pthread_t)))
		|| !(options.table.fork = ft_calloc(options.number_of_philosophers, sizeof(int)))
		|| !(options.prints = ft_calloc(options.number_of_philosophers, sizeof(pthread_t))))
		return (0);
	if (!run_threads(options.philos, &options))
		return (0);
	free(options.philos);
	free(options.prints);
	free(options.table.fork);
}
