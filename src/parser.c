/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperraut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 11:56:38 by tperraut          #+#    #+#             */
/*   Updated: 2016/05/23 11:36:14 by tperraut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

#include <unistd.h>
#include <stdlib.h>

static int	check(int sharp, int x, int y, char c)
{
	if (sharp > 4
			|| x > 4
			|| y > 4
			|| (x != 4 && c != '#' && c != '.')
			|| (x == 4 && c != '\n'))
		return (1);
	return (0);
}

static int	new_trio(char *buf, t_trio *t)
{
	t_pt	ogn;
	t_pt	curs;
	int		sharp;

	ft_pset(&curs, 0, 0);
	sharp = 0;
	while (*buf)
	{
		if (check(sharp, curs.x, curs.y, *buf))
			return (ER);
		if (*buf == '#')
		{
			if (sharp == 0)
				ft_pset(&ogn, curs.x, curs.y);
			else
				ft_pset(&(t->a_tab[sharp - 1]), curs.x - ogn.x, curs.y - ogn.y);
			++sharp;
		}
		if (curs.x == 4 && ++curs.y)
			curs.x = 0;
		else
			++curs.x;
		++buf;
	}
	return ((sharp == 4) ? 0 : ER);
}

static int	pt_link(t_pt p1, t_pt p2)
{
	if ((p1.x == p2.x && (p1.y - 1 == p2.y || p1.y + 1 == p2.y))
			|| (p1.y == p2.y && (p1.x - 1 == p2.x || p1.x + 1 == p2.x)))
		return (1);
	return (0);
}

/*
** a[4] is an independant variable
*/

static int	trio_check(t_trio t)
{
	t_pt	p;
	int		a[5];

	ft_pset(&p, 0, 0);
	a[1] = pt_link(p, t.a_tab[0]);
	a[2] = pt_link(p, t.a_tab[1]);
	a[3] = pt_link(p, t.a_tab[2]);
	a[0] = a[1] + a[2] + a[3];
	if (a[0] && a[0] < 3)
	{
		a[4] = pt_link(t.a_tab[0], t.a_tab[1]);
		a[2] += a[4];
		a[1] += a[4];
		a[4] = pt_link(t.a_tab[0], t.a_tab[2]);
		a[3] += a[4];
		a[1] += a[4];
	}
	if (a[1] && a[1] < 3)
	{
		a[4] = pt_link(t.a_tab[1], t.a_tab[2]);
		a[2] += a[4];
		a[3] += a[4];
	}
	return (!(a[0] && a[1] && a[2] && a[3]
				&& (a[0] > 1 || a[1] > 1 || a[2] > 1 || a[3] > 1)));
}

int			parser(int fd, t_trio **pa_trio)
{
	char	buf[BUF_SIZE + 1];
	ssize_t	rd;
	int		len;
	t_trio	*a_trio;
	int		tmp;

	len = 0;
	rd = 1;
	tmp = 0;
	IF_RETURN(!(a_trio = (t_trio *)malloc(sizeof(t_trio) * MAX_TRIO)), ER);
	while (rd && (rd = read(fd, buf, BUF_SIZE)))
	{
		IF_RETURN(rd != BUF_SIZE || len == MAX_TRIO, ER);
		buf[rd] = '\0';
		IF_RETURN((new_trio(buf, &(a_trio[len]))) < 0
				|| (rd = read(fd, buf, 1)) < 0
				|| (rd && buf[0] != '\n')
				|| trio_check(a_trio[len]), ER);
		a_trio[len].lt = 'A' + len;
		tmp = rd;
		++len;
	}
	IF_RETURN(tmp, ER);
	*pa_trio = a_trio;
	return (len);
}
