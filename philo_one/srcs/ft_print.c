/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:06:40 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/16 16:49:37 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

char	*msg_action(int action)
{
	if (action == MSG_FORK)
		return (AC_FORK);
	if (action == MSG_DIE)
		return (AC_DIE);
	if (action == MSG_EAT)
		return (AC_EAT);
	if (action == MSG_SLEEP)
		return (AC_SLEEP);
	if (action == MSG_THINK)
		return (AC_THINK);
	return (NULL);
}

void	print_philo(char *s1, char *s2, char *s3, t_print *print)
{
	char			*str;
	unsigned int	len;
	char			*tmp1;
	char			*tmp2;
	char			*tmp3;

	tmp1 = s1;
	tmp2 = s2;
	tmp3 = s3;
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 2;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return ;
	while (*s1)
		*str++ = *s1++;
	*str++ = ' ';
	while (*s2)
		*str++ = *s2++;
	*str++ = ' ';
	while (*s3)
		*str++ = *s3++;
	*str = 0;
	pthread_mutex_lock(&print->options->mutex);
	while (print->options->msg_nb < print->msg_nb)
	{
		pthread_mutex_unlock(&print->options->mutex);
		if (print->options->table.death)
		{
			free(str - len);
			free(tmp1);
			free(tmp2);
			return ;
		}
		pthread_mutex_lock(&print->options->mutex);
	}
	ft_putstr_fd(str - len, 1);
	if (ft_strncmp(tmp3, AC_DIE, 2))
		(print->options->msg_nb)++;
	else
		print->options->table.death = 1;
	pthread_mutex_unlock(&print->options->mutex);
	free(str - len);
	free(tmp1);
	free(tmp2);
	return ;
}

void	*print_thread(void *tmp)
{
	t_print			*print;

	print = tmp;
	print_philo(
	ft_itoa(print->time),
	ft_itoa(print->id + 1),
	msg_action(print->action), print);
	return (NULL);
}

int		print_line(t_options *options, int id, int action)
{
	t_print			*print;
	pthread_t		printer;
	long			time;

	print = malloc(sizeof(t_print));
	pthread_mutex_lock(&options->mutex);
	print->msg_nb = (options->msg_list)++;
	pthread_mutex_unlock(&options->mutex);
	if (!(time = get_time()))
		return (0);
	print->time = time - options->start;
	print->action = action;
	print->options = options;
	print->id = id;
	if (pthread_create(&printer, NULL, &print_thread, print))
			return (0);
	if (action == MSG_DIE)
		pthread_join(printer, NULL);
	return (1);
}
