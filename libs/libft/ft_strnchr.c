/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:28:29 by harndt            #+#    #+#             */
/*   Updated: 2022/05/26 21:55:43 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str++ == (char)c)
			return (i);
		i++;
	}
	return (-1);
}