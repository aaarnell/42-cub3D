/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrcpy_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:06:31 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/20 17:42:13 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrcpy_strdup(char **from, char **to)
{
	int	i;

	i = 0;
	while (from && from[i])
	{
		to[i] = ft_strdup(from[i]);
		if (!to[i])
		{
			ft_frmtrx(to);
			free(to);
			return (NULL);
		}
		i++;
	}
	return (to);
}
