/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:07:46 by mchardin          #+#    #+#             */
/*   Updated: 2020/07/07 14:56:40 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct  s_options
{
	int		 		number_of_philosopher;
	int		 		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_each_philosophers_must_eat;
	struct timeval  start;
}				t_options;

int		ft_isnumber(const char *str);
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(const char *s);

#endif