/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:13:32 by mchardin          #+#    #+#             */
/*   Updated: 2020/07/07 15:24:53 by mchardin         ###   ########.fr       */
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
		options->number_of_time_each_philosophers_must_eat = __INT32_MAX__; //ou -1?
	return (1);
}

void	*print_timestamp(void *tmp)
{
	t_options		*options;
	struct timeval  now;

	ft_putstr_fd("COUCOU2\n", 1);
	options = tmp;
	if (gettimeofday(&now, NULL) < 0)
		return ((void *)1); //WHICH VALUE??
	ft_putstr_fd("TIMESTAMP TEST :", 1);
	ft_putnbr_fd(now.tv_sec - options->start.tv_sec, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

int		run_threads(pthread_t *philos, t_options *options)
{
	int		i;

	i = -1;
	ft_putstr_fd("COUCOU\n", 1);
	while (++i < options->number_of_philosopher)
		if (pthread_create(&philos[i], NULL, &print_timestamp, options))
			return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_options		options;
	pthread_t		*philos;

	if (argc < 5 || argc > 6 || !fill_options(&options, argc, argv))
		return (0);
	if (gettimeofday(&options.start, NULL) < 0) // CHECK IF WORK
		return (0);
	if (!(philos = malloc(sizeof(pthread_t) * options.number_of_philosopher)))
		return (0);
	if (!run_threads(philos, &options))
		return (0);
}
