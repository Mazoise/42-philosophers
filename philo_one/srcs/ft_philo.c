/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:13:32 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/05 18:57:38 by mchardin         ###   ########.fr       */
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
void	print_line(int timestamp, int philosopher, char *action)
{
	char	*str_time;
	char	*str_philo;
	char	*tmp;
	char	*tmp2;

	str_time = ft_itoa(timestamp);
	str_philo = ft_itoa(philosopher + 1);
	tmp = ft_strjoin(str_time, " ");
	tmp2 = ft_strjoin(tmp, str_philo);
	free(tmp);
	tmp = ft_strjoin(tmp2, action);
	ft_putstr_fd(tmp, 1);
	free(str_time);
	free(str_philo);
	free(tmp);
	free(tmp2);
}

int		id_cloud(t_cloud *cloud)
{
	int		i;

	i = -1;	
	while(cloud[++i].taken == 1)
		;
	cloud[i].taken = 1;
	return (i);
}

void	*print_timestamp(void *tmp)
{
	t_options		*options;
	struct timeval  now;
	int				perso_nb;

	options = tmp;
	perso_nb = id_cloud(options->cloud);
	if (gettimeofday(&now, NULL) < 0)
		return ((void *)1); //WHICH VALUE??
	// while (1)
	{
		print_line((now.tv_usec - options->start.tv_usec) / 10,
		perso_nb, AC_FORK);
	}
	return (0);
}

int		run_threads(pthread_t *philos, t_options *options)
{
	int		i;

	i = -1;
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
	if (!(philos = ft_calloc(sizeof(pthread_t), options.number_of_philosopher))
		|| !(options.cloud = ft_calloc(sizeof(t_cloud), options.number_of_philosopher)))
		return (0);
	if (!run_threads(philos, &options))
		return (0);
	while (1)
		;
}
