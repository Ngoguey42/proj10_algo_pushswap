/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/04 11:25:09 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <stdlib.h>

void		fill_al(t_dbuff *al, PS_TYPE *list, size_t len)
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

void		create_ref(t_psl *ref, size_t len)
{
	DBUFF_T	i;

	ft_dbuff_init(&ref->al, len, 0);
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


int			main(void)
{
//		2, 4, 3, 5, 7,  6, 1, 8
	PS_TYPE	list[] = {
		2, 4, 3, 5, 7,  6, 1



/* 		1, 2, 3, 4, 5, 1, */
/* 		1, 2, 3, 4, 5, 1, */
/* 		1, 2, 3, 4, 5, 1, */
/* 		1, 2, 3, 4, 5, 1 */

	};



	size_t	len = sizeof(list) / sizeof(PS_TYPE);
	t_psl	ref;
	t_psl	psl;

	ft_dbuff_init(&psl.al, len + 25, 10);
	ft_dbuff_init(&psl.bl, len + 25, 10);
	ft_dstor_init(&psl.act, 0x20);

	create_ref(&ref, len);
/* 	ps_print_dstor(&psl.act); */


	ps_print_psl(&psl);
	fill_al(&psl.al, list, len);
	ps_print_psl(&psl);
	ft_dbuff_recenter(&psl.al);
	ps_print_psl(&psl);


#define TEST(action)							\
	apply_action(&psl, action);					\
	ps_print_psl(&psl);							\
	if (ps_is_solved(&psl))						\
		qprintf("solved\n\n");					\
	else										\
		qprintf("not solved\n\n")

/* 	int i; */
/* 	for (i = 0; i < 3; i++) */
	ps_brute_solve(&psl);
/* 	ps_print_psl(&psl); */

	TEST(none);

/* 	(void)i; */
	return (0);
}
