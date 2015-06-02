/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/02 14:11:49 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <stdlib.h>

/*
** 'fill_al'		Fills the main 't_psl' from 'corresp'.
** *
** 'create_ref'		Creates a 't_psl' reference in order to memcmp in
** 						'ps_is_solved'.
** *
** 'main'
** 		'put_struct_ps'		Reads ac, av. Might exit
** 		'create_ref'		Initialize a ref 't_psl' containing numbers
** 								in the wished order in the a-list.
** 		'ps_get_nb_grad'	Debug.
** 		'ft_dbuff_init'x2	Initializes both lists in 'psl'
** 		'ft_dstor_init'		Initializes actions buffer in 'psl'
** 		'fill_al'			Fills 'psl' with the arguments received.
** 		'ft_dbuff_recenter'	Recenters a-list's arguments in 'psl'
** 		'ps_dup_l'			Duplicates 'psl' before trying to solve.
** 		'ps_brute_solve'	Tries 'brute solving' solution.
** 		'ps_set_solve'		Tries 'set solving' solution.
**		'ps_printbest_solution'		Print best solution from 'set solving'
*/

static void	fill_al(t_dbuff *al, PS_TYPE const *list, size_t len)
{
	DBUFF_T	*ptr;

	al->zone_size = len;
	al->zone_rear = al->buf_rear;
	al->zone_front = al->buf_rear + len - 1;
	ptr = al->zone_rear;
	while (len--)
		*ptr++ = *list++;
	return ;
}

static void	create_ref(t_psl *ref, size_t len)
{
	DBUFF_T	i;

	if (ft_dbuff_init(&ref->al, len, 0))
		ft_exit("ENOMEM");
	i = 0;
	while (i < len)
	{
		ref->al.buf_rear[i] = len - i;
		i++;
	}
	ref->al.zone_rear = ref->al.buf_rear;
	ref->al.zone_size = len;
	ps_is_solved(ref);
	return ;
}

#include <unistd.h>
#include <stdio.h>

void		checkLeaks()
{
	char	buf[512];

	snprintf(buf, 512, "/usr/bin/leaks %d | tail -n 1 >&2 ", getpid());
	system(buf);
	exit(0);
	return ;
}

int			main(int ac, char **av)
{
	t_corresp	corresp;
	t_psl		ref;
	t_psl		psl;
	t_psl		*brute;

	put_struct_ps(&ac, av, &corresp);
	create_ref(&ref, ac);
	if (ft_dbuff_init(&psl.al, ac + (ac * 5), ac * 2) ||
		ft_dbuff_init(&psl.bl, ac + (ac * 5), ac * 2) ||
		ft_dstor_init(&psl.act, 0x20))
		ft_exit("ENOMEM");
	fill_al(&psl.al, corresp.corresp, ac);
	ft_dbuff_recenter(&psl.al);
	ps_dup_l(&psl, &brute);
	if (ps_brute_solve(brute))
	{
		ps_print_psl(brute);
		return (0);
	}
	ps_set_solve(&psl);
	ps_printbest_solution();
	return (0);
}
