/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:19:08 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:25:38 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_numlen(int num)
{
	int res;
	int n;

	res = 0;
	if (num == 0)
		return (1);
	else if (num < 0)
	{
		res++;
		n = -num;
	}
	else
		n = num;
	while (n > 0)
	{
		res++;
		n /= 10;
	}
	return (res);
}
