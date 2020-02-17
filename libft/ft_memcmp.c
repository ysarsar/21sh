/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:18:29 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:25:32 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ps1;
	const unsigned char	*ps2;

	ps1 = s1;
	ps2 = s2;
	while (n--)
	{
		if (*ps1 != *ps2)
		{
			return (*ps1 - *ps2);
		}
		ps1++;
		ps2++;
	}
	return (0);
}
