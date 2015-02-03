/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:49 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/03 11:47:27 by ngoguey          ###   ########.fr       */
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

int			main(void)
{
	PS_TYPE	list[] = {
		7, 2, 4, 3, 5, 6, 1
	};
	size_t	len = sizeof(list) / sizeof(PS_TYPE);


	t_psl	psl;

	ft_dbuff_init(&psl.al, len * 3);
	ft_dbuff_init(&psl.bl, len * 3);
	ft_dstor_init(&psl.act, 0x20);
/* 	ps_print_dstor(&psl.act); */
/* 	ps_print_dbuff(&psl.al); */
	ps_print_psl(&psl);
	fill_al(&psl.al, list, len);
	ps_print_psl(&psl);
	ft_dbuff_recenter(&psl.al);
	ps_print_psl(&psl);
/* 	ps_print_dbuff(&psl.al); */
	
	apply_action(&psl, sa);
	ps_print_psl(&psl);
	return (0);
}
