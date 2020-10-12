/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:07:46 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/12 17:31:08 by mchardin         ###   ########.fr       */
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
# define AC_SLEEP " is sleeping\n"
# define AC_THINK " is thinking\n"
# define AC_DIE " died\n"

typedef enum	e_msg
{
	MSG_FORK,
	MSG_EAT,
	MSG_SLEEP,
	MSG_THINK,
	MSG_DIE
}				t_msg;

typedef struct	s_print
{
	int				action;
	long			start;
	int				id;
}				t_print;

typedef struct	s_table
{
	int				seat;
	int				*fork;
	int				death;
}				t_table;

typedef struct	s_perso
{
	int				id;
	int				forks[2];
	long			last_meal;
	int				meals_left;
}				t_perso;

typedef struct  s_options
{
	int		 		number_of_philosophers;
	int		 		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				time_to_eat_sleep;
	int				time_to_sleep_think;
	int				time_two_meals;
	int				number_of_meals;
	long		  start;
	pthread_t		*philos;
	t_table			table;
	pthread_mutex_t	mutex;
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