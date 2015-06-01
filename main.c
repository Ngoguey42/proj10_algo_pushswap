/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/01 18:03:12 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <stdlib.h>

static void	fill_al(t_dbuff *al, PS_TYPE *list, size_t len)
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

	(void)ft_dbuff_init(&ref->al, len, 0);
	i = 0;
	while (i < len)
	{
		ref->al.buf_rear[i] = len - i;
		i++;
	}
	ref->al.zone_rear = ref->al.buf_rear;
	ref->al.zone_size = len;
	ps_print_dbuff(&ref->al);
	ps_is_solved(ref);
	return ;
}

int			main(int ac, char **av)
{
	t_corresp	corresp;
	t_psl		ref;
	t_psl		psl;
	t_psl		*brute;

	put_struct_ps(&ac, av, &corresp); //read ac av
	create_ref(&ref, ac); //initialize reference
	(void)ps_get_nb_grad(0, ac, (char[16]){});//initialize debug's gradient
	
	(void)ft_dbuff_init(&psl.al, ac + (ac * 5), ac * 2);//init main struct
	(void)ft_dbuff_init(&psl.bl, ac + (ac * 5), ac * 2);//init main struct
	(void)ft_dstor_init(&psl.act, 0x20);//init main struct
	fill_al(&psl.al, corresp.corresp, ac); //remplit la liste initiale
	ft_dbuff_recenter(&psl.al); //recentre la liste initiale

	ps_dup_l(&psl, &brute); //cree la liste pour brute solve
	ps_brute_solve(brute); //fait le brute solve
	ps_print_psl(brute); //print le brute solve

	/* ps_set_solve(&psl); */
	/* qprintf("%d movements\n", ps_total_movements(NULL)); */
	ps_printbest_solution();
	return (0);
}
