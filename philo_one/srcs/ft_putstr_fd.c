/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:14:41 by mchardin          #+#    #+#             */
/*   Updated: 2020/07/07 15:01:38 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

	int		ft_strlen(const char *s)
{
	int len;

	len = -1;
	while (s[++len])
		;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
