/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:35:23 by mchardin          #+#    #+#             */
/*   Updated: 2020/10/27 11:43:04 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

long 	get_time()
{
	struct timeval  now;

	if (gettimeofday(&now, NULL) < 0)
		return (0);
	return (now.tv_sec * 1000000 + now.tv_usec);
}

void	*time_thread(void *tmp)
{
	t_options		*options;

	options = tmp;
	while (1)
	{
		if (options->table.end || !(options->time = get_time()))
			return (NULL);
	}
	return (NULL);
}

// void		usleep_opti(int time)
// {
// 	int		time2;

// 	time2 = 500 * time;
// 	usleep(time2);
// 	usleep(time2);
// 	return ;
// }
