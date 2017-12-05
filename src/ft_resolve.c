/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperraut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 09:36:43 by tperraut          #+#    #+#             */
/*   Updated: 2016/03/22 09:40:15 by tperraut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#include <stdlib.h>

static void	upy_case1(int *p_i, char ***pa_sq, int *sq_size, t_pt *p_pt)
{
	*p_i = 0;
	++*sq_size;
	ft_free_mat(pa_sq, *sq_size);
	*pa_sq = ft_create_mat(*sq_size);
	ft_pset(p_pt, 0, 0);
}

static void	upy_case2(t_trio t, char ***pa_sq, t_pt *p_ref, t_pt *p_pt)
{
	ft_remove_trio(t, pa_sq, *p_ref);
	ft_pset(p_pt, p_ref->x + 1, p_ref->y);
}

static int	accept_split(t_trio t, char ***pa_sq, t_pt *p_ref, t_pt *p_pt)
{
	ft_add_trio(t, pa_sq, *p_pt);
	*p_ref = *p_pt;
	ft_pset(p_pt, 0, 0);
	return (1);
}

char		**ft_resolve(t_trio *a_t, int size, int *sq_size, int i)
{
	char	**a_sq;
	t_tr	test;
	t_pt	a_ref[size + 1];

	ft_pset(&a_ref[size], 0, 0);
	if ((a_sq = ft_create_mat(*sq_size)) == NULL)
		return (NULL);
	while (i < size)
	{
		if ((test = ft_accept(a_t[i], a_sq, a_ref[size], *sq_size)) == ACCEPT)
			i = i + accept_split(a_t[i], &a_sq, &a_ref[i], &a_ref[size]);
		else if (test == CONFLICT || test == DOWN_X)
			++a_ref[size].x;
		else if (test == UP_X)
			ft_pset(&a_ref[size], 0, a_ref[size].y + 1);
		else if (test == UP_Y)
		{
			if (--i < 0)
				upy_case1(&i, &a_sq, sq_size, &a_ref[size]);
			else
				upy_case2(a_t[i], &a_sq, &a_ref[i], &a_ref[size]);
		}
	}
	return (a_sq);
}
