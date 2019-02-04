/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rejocic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:52:48 by rejocic           #+#    #+#             */
/*   Updated: 2018/10/11 13:55:20 by rejocic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	buff;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		buff = str[i];
		str[i] = str[len];
		str[len] = buff;
		len--;
		i++;
	}
	return (str);
}
