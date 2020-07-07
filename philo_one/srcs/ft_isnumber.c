/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:33:33 by mchardin          #+#    #+#             */
/*   Updated: 2020/07/07 14:31:59 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int ft_isnumber(const char *str) //DOESN'T CHECK NEG NUMBERS
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
