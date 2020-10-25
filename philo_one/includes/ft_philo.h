/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:07:46 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/25 19:03:47 by mchardin         ###   ########.fr       */
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
	int				seat;
	int				end;
	int				finished_eating;
}				t_table;

typedef struct  s_mutex
{
	pthread_mutex_t		end;
	pthread_mutex_t		msg;
	pthread_mutex_t		seat;
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
	long 			time;
	pthread_t		*philos;
	t_table			table;
	t_mutex			mutex;
}				t_options;

typedef struct	s_perso
{
	int				id;
	int				fork_id[2];
	long 			last_meal;
	int				meals_left;
	t_options		*options;
}				t_perso;

typedef struct	s_print
{
	int				action;
	int				id;
	long 	time;
	t_options		*options;
}				t_print;

int		ft_isnumber(const char *str);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbrphilo_fd(unsigned int n, int fd);
int		ft_strlen(const char *s);
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		print_line(t_options *options, int id, int action);
void	*print_thread(void *tmp);
void	print_philo(char *s1, char *s2, char *s3, t_print *print);
char	*msg_action(int action);
void	eat_sleep_think(t_options *options, t_perso *perso);
int		dead_philo(t_options *options, t_perso *perso, int t_death);
void	usleep_opti(int time);
long 	get_time();
void	*time_thread(void *tmp);

#endif