/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:47 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/02 11:17:13 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

void		ps_print_sol(const t_list *solutions)
{
	while (solutions != NULL)
	{
		ft_dprintf(2, "%s ", action_name(*(unsigned char*)solutions->content));
		solutions = solutions->next;
	}
	ft_putendl_fd("", 2);
	return ;
}

void		print_list(const t_pslist *list)
{
	const PS_TYPE	*a = list->a;
	const PS_TYPE	*b = list->b;

	qprintf("A:(%hu)", list->asz);
	while (a && *a)
		qprintf("%hu ", *a++);
	qprintf("\n");
	qprintf("B:(%hu)", list->bsz);
	while (b &&*b)
		qprintf("%hu ", *b++);
	qprintf("\n");
	return ;
}

const char	*action_name(t_action action)
{
	static const char	names[][5] = {

	"ra",
	"rb",
	"rr",
	"rra",
	"rrb",
	"rrr",
	"pa",
	"pb",
	"sa",
	"sb",
	"ss",
	"none"};
	return (names[action]);
}
