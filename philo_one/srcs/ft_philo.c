/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:13:32 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/09 20:07:35 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int		fill_options(t_options *options, int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isnumber(argv[i])) //CANNOT BE NEGATIVE, MODIFY FONCTION?
			return (0);
	}
	options->number_of_philosopher = ft_atoi(argv[1]);
	options->time_to_die = ft_atoi(argv[2]);
	options->time_to_eat = ft_atoi(argv[3]);
	options->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		options->number_of_time_each_philosophers_must_eat = ft_atoi(argv[5]);
	else
		options->number_of_time_each_philosophers_must_eat = -1;
	options->table.seat = 0;
	return (1);
}

int		print_line(struct timeval start, int philosopher, char *action) // RET ERROR
{
	struct timeval  now;
	char	*tmp;
	char	*tmp2;
	char	*str;

	tmp = ft_itoa(philosopher + 1);
	tmp2 = ft_strjoin(tmp, action);
	free(tmp);
	tmp = ft_strjoin(" ", tmp2);
	free(tmp2);
	if (gettimeofday(&now, NULL) < 0)
		return (0);
	tmp2 = ft_itoa((now.tv_sec - start.tv_sec) * 1000
	+ (now.tv_usec - start.tv_usec) / 1000);
	str = ft_strjoin(tmp2, tmp);
	ft_putstr_fd(str, 1);
	free(tmp);
	free(tmp2);
	free(str);
	return (1);
}

void	*create_life(void *tmp)
{
	t_options		*options;
	t_perso			perso;
	struct timeval	now;
	void			*ret;

	options = tmp;
	perso.id = options->table.seat++;
	perso.forks[0] = perso.id == 0 ? options->number_of_philosopher - 1 : perso.id - 1;
	perso.forks[1] = perso.id;
	perso.last_meal = options->start;
	perso.meals_left = options->number_of_time_each_philosophers_must_eat;
	if (perso.id != options->number_of_philosopher - 1)
		pthread_join(options->philos[perso.id + 1], &ret);
	while (perso.meals_left < 0 ? 1 : perso.meals_left--)
	{
		while (options->table.fork[perso.forks[0]] || options->table.fork[perso.forks[1]])
		{
			if (gettimeofday(&now, NULL) < 0)
				return (0);
			if ((now.tv_sec - perso.last_meal.tv_sec) * 1000
+ (now.tv_usec - perso.last_meal.tv_usec) / 1000 >= options->time_to_die)
			{
				print_line(options->start, perso.id, AC_DIE);
				return (0);
			}
		}
		options->table.fork[perso.forks[0]] = 1;
		print_line(options->start, perso.id, AC_FORK);
		options->table.fork[perso.forks[1]] = 1;
		print_line(options->start, perso.id, AC_FORK);
		print_line(options->start, perso.id, AC_EAT);
		if (gettimeofday(&perso.last_meal, NULL) < 0)
			return (0);
		if (options->time_to_eat <= options->time_to_die)
			usleep(1000 * options->time_to_eat);
		else
		{
			usleep(1000 * options->time_to_die);
			print_line(options->start, perso.id, AC_DIE);
			return (0);
		}
		options->table.fork[perso.forks[0]] = 0;
		options->table.fork[perso.forks[1]] = 0;
		print_line(options->start, perso.id, AC_SLEEP);
		if (options->time_to_eat + options->time_to_sleep <= options->time_to_die)
			usleep(1000 * options->time_to_sleep);
		else
		{
			usleep(1000 * (options->time_to_die - options->time_to_eat));
			print_line(options->start, perso.id, AC_DIE);
			return (0);
		}
		print_line(options->start, perso.id, AC_THINK);
	}
	return (0);
}

int		run_threads(pthread_t *philos, t_options *options)
{
	int		i;
	void	*ret;

	i = -1;
	while (++i < options->number_of_philosopher)
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
	if (gettimeofday(&options.start, NULL) < 0) // CHECK IF WORK
		return (0);
	if (!(options.philos = ft_calloc(options.number_of_philosopher, sizeof(pthread_t)))
		|| !(options.table.fork = ft_calloc(options.number_of_philosopher, sizeof(int))))
		return (0);
	if (!run_threads(options.philos, &options))
		return (0);
}
