/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:41:09 by mariacos          #+#    #+#             */
/*   Updated: 2025/05/03 14:09:13 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	len_s;

	if (!s)
	{
		return ;
	}
	i = 0;
	len_s = ft_strlen(s);
	while (i < len_s)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
