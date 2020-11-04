/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:07:46 by mchardin          #+#    #+#             */
/*   Updated: 2020/11/04 14:16:14 by mchardin         ###   ########.fr       */
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

# define AC_FORK "has taken a fork\n"
# define AC_EAT "is eating\n"
# define AC_SLEEP "is sleeping\n"
# define AC_THINK "is thinking\n"
# define AC_DIE "died\n"

typedef enum	e_msg
{
	MSG_FORK,
	MSG_EAT,
	MSG_SLEEP,
	MSG_THINK,
	MSG_DIE
}				t_msg;

typedef struct	s_table
{
	int				end;
	int				still_eating;
}				t_table;

typedef struct  s_mutex
{
	pthread_mutex_t		end;
	pthread_mutex_t		msg;
	pthread_mutex_t		*fork;
}				t_mutex;

typedef struct  s_options
{
	int		 		nb_philos;
	int		 		t_die;
	int				t_eat;
	int				t_sleep;
	int				t_think;
	int				nb_meals;
	long 			start;
	pthread_t		*philos;
	t_table			table;
	t_mutex			mutex;
}				t_options;

typedef struct	s_perso
{
	int				id;
	int				fork_id[2];
	int				meals_left;
	long 			t_death;
	t_options		*options;
}				t_perso;

int		ft_isposnumber(const char *str);
int		ft_atoi(const char *str);
void	ft_putnbrphilo(int n);
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);
long 	get_time();
void	usleep_opti(long t_end);
int		print_line(t_options *options, int id, int action);
void	eat_sleep_think(t_options *options, t_perso *perso);
int		dead_philo(t_options *options, t_perso *perso, int t_death);
void	clean_all(t_options *options, t_perso *perso);

#endif