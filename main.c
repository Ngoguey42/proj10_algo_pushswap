/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/02 12:05:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <stdlib.h>


static const t_pslist	*create_solved_ref(PS_TYPE len)
{
	t_pslist	ret;
	t_pslist	*retp;
	PS_TYPE		i;

	ret.asz = len;
	ret.a = (PS_TYPE*)malloc(len * sizeof(PS_TYPE));
	ret.b = NULL;
	ret.bsz = 0;
	i = 0;
	while (i++ < len)
		ret.a[i - 1] = i;
	retp = (t_pslist*)ft_memdup(&ret, sizeof(t_pslist));
	print_list(retp);
	return ((const t_pslist*)retp);
}

int			main(void)
{
	PS_TYPE		origin[] = {4, 2, 3, 1};
/* 	PS_TYPE		origin[] = {7, 2, 3, 6, 1, 4, 5}; */
	PS_TYPE		len;
	t_pslist	*origin_a;
	t_list		*sol[1];

	len = sizeof(origin) / sizeof(PS_TYPE);
	(void)is_solved(create_solved_ref(len));
	origin_a = (t_pslist*)ft_memalloc(sizeof(t_pslist));
	origin_a->a = (PS_TYPE*)ft_memdup(origin, len * sizeof(PS_TYPE));
	origin_a->b = (PS_TYPE*)ft_memalloc(len * sizeof(PS_TYPE));
	origin_a->asz = len;
	print_list(origin_a);
	*sol = NULL;
	(void)ps_brute_solve(origin_a, sol);
	ps_print_sol(*sol);
	return (0);
}
