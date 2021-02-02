/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:07:46 by mchardin          #+#    #+#             */
/*   Updated: 2021/02/02 19:52:46 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/stat.h> 
# include <sys/types.h>
# include <sys/wait.h>

# define AC_FORK "has taken a fork\n"
# define AC_EAT "is eating\n"
# define AC_SLEEP "is sleeping\n"
# define AC_THINK "is thinking\n"
# define AC_DIE "died\n"

# define SEM_FORKS "forks_sem_philo_two_mchardin"
# define SEM_MSG "msg_sem_philo_two_mchardin"
# define SEM_STOP "stop_sem_philo_two_mchardin"

typedef enum			e_msg
{
	MSG_FORK,
	MSG_EAT,
	MSG_SLEEP,
	MSG_THINK,
	MSG_DIE
}						t_msg;

typedef struct			s_sem
{
	sem_t				*msg;
	sem_t				*forks;
	sem_t				*stop;
}						t_sem;

typedef struct			s_shared
{
	int					nb_philos;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					t_think;
	int					nb_meals;
	long				start;
	pid_t				*philos;
	t_sem				sem;
}						t_shared;

typedef struct			s_perso
{
	int					id;
	int					meals_left;
	long				t_death;
	t_shared			*shared;
}						t_perso;

int						ft_isposnumber(const char *str);
int						ft_atoi(const char *str);
void					ft_putnbrphilo(int n);
char					*ft_itoa_pos(int n);
void					*ft_calloc(size_t count, size_t size);
int						ft_acalloc(void **dest, size_t count, size_t size);
int						ft_amalloc(void **dest, size_t size);
long					get_time(void);
void					usleep_opti(long t_end);
int						end_of_philo(t_perso *perso, t_shared *shared);
void					print_line(t_shared *shared, int id, int action);
void					print_death(t_shared *shared, int id);
void					life_thread(void *tmp);
void					clean_all(t_shared *shared, t_perso *perso, int thr);

#endif
