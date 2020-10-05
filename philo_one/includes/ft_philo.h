/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:07:46 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/05 18:53:02 by mchardin         ###   ########.fr       */
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

# define AC_FORK " has taken a fork\n"
# define AC_EAT " is eating\n"
# define AC_SLEEP " is eating\n"
# define AC_THINK " is thinking\n"
# define AC_DIE " died\n"

typedef struct	s_cloud
{
	int				taken;
	
}				t_cloud;

typedef struct  s_options
{
	int		 		number_of_philosopher;
	int		 		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_each_philosophers_must_eat;
	struct timeval  start;
	t_cloud			*cloud;
}				t_options;

int		ft_isnumber(const char *str);
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);

#endif