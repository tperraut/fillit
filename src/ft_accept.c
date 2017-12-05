/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_accept.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperraut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 09:25:11 by tperraut          #+#    #+#             */
/*   Updated: 2016/03/22 09:33:58 by tperraut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	add_pt(t_pt *p_pt, t_pt p1, t_pt p2)
{
	p_pt->x = p1.x + p2.x;
	p_pt->y = p1.y + p2.y;
}

static int	gtoe(t_pt a_pt[3], int size, int mod)
{
	int	i;

	i = 0;
	if (!mod)
	{
		while (i < 3)
		{
			if (a_pt[i].x >= size)
				return (1);
			++i;
		}
	}
	else
	{
		while (i < 3)
		{
			if (a_pt[i].y >= size)
				return (1);
			++i;
		}
	}
	return (0);
}

static int	lt(t_pt a_pt[3], int size, int mod)
{
	int	i;

	i = 0;
	if (!mod)
	{
		while (i < 3)
		{
			if (a_pt[i].x < size)
				return (1);
			++i;
		}
	}
	return (0);
}

t_tr		ft_accept(t_trio t, char **a_sq, t_pt pt, int sq_size)
{
	t_pt	a_pt[3];
	int		i;

	i = 0;
	add_pt(&a_pt[0], t.a_tab[0], pt);
	add_pt(&a_pt[1], t.a_tab[1], pt);
	add_pt(&a_pt[2], t.a_tab[2], pt);
	if (pt.y >= sq_size || gtoe(a_pt, sq_size, 1))
		return (UP_Y);
	if (pt.x >= sq_size || gtoe(a_pt, sq_size, 0))
		return (UP_X);
	if (pt.x < 0 || lt(a_pt, 0, 0))
		return (DOWN_X);
	if (a_sq[pt.y][pt.x] != '.')
		return (CONFLICT);
	while (i < 3)
	{
		if (a_sq[a_pt[i].y][a_pt[i].x] != '.')
			return (CONFLICT);
		++i;
	}
	return (ACCEPT);
}
