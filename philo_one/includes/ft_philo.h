/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:07:46 by mchardin          #+#    #+#             */
/*   Updated: 2020/11/05 18:05:54 by mchardin         ###   ########.fr       */
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

typedef enum			e_msg
{
	MSG_FORK,
	MSG_EAT,
	MSG_SLEEP,
	MSG_THINK,
	MSG_DIE
}						t_msg;

typedef struct			s_table
{
	int					end;
	int					still_eating;
}						t_table;

typedef struct			s_mutex
{
	pthread_mutex_t		end;
	pthread_mutex_t		msg;
	pthread_mutex_t		*fork;
}						t_mutex;

typedef struct			s_shared
{
	int					nb_philos;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					t_think;
	int					nb_meals;
	long				start;
	pthread_t			*philos;
	t_table				table;
	t_mutex				mutex;
}						t_shared;

typedef struct			s_perso
{
	int					id;
	int					fork_id[2];
	int					meals_left;
	long				t_death;
	t_shared			*shared;
}						t_perso;

int						ft_isposnumber(const char *str);
int						ft_atoi(const char *str);
void					ft_putnbrphilo(int n);
char					*ft_itoa(int n);
void					*ft_calloc(size_t count, size_t size);
long					get_time(void);
void					usleep_opti(long t_end);
int						print_line(t_shared *shared, int id, int action);
void					*life_thread(void *tmp);
void					clean_all(t_shared *shared, t_perso *perso);

#endif
