/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute_solve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:44:54 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/02 12:13:51 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <stdlib.h>

#define RA_EX	(-1 - RB - RRA - RRR)
#define RB_EX	(-1 - RA - RRB - RRR)
#define RR_EX	(-1 - RRA - RRB - RRR)
#define RRA_EX	(-1 - RA - RRB - RR)
#define RRB_EX	(-1 - RB - RRA - RR)
#define RRR_EX	(-1 - RA - RB - RR)
#define PA_EX	(-1 - PB)
#define PB_EX	(-1 - PA)
#define S_EX	(-1 - SA - SB - SS)

#define A_IS_0_1	(-1 - SS - SA - PB - RRR - RR - RA - RRA)
#define B_IS_0		(-1 - SS - SB - PA - RRR - RR - RB - RRB)
#define B_IS_1		(-1 - SS - SB      - RRR - RR - RB - RRB)

// ra,		0
// rb,		1
// rr,		2
// rra,		3
// rrb,		4
// rrr,		5
// pa,		6
// pb,		7
// sa,		8
// sb,		9
// ss,		10
// none		11
	
/*
** if size <= 2 don"t allow rr rotations
*/

static void			fill_exclusions(PS_TYPE asz, PS_TYPE bsz, t_action pac,
						unsigned short *exclusions)
{
	if (pac == ra)
		*exclusions = RA_EX;
	else if (pac == rb)
		*exclusions = RB_EX;
	else if (pac == rr)
		*exclusions = RR_EX;
	else if (pac == rra)
		*exclusions = RRA_EX;
	else if (pac == rrb)
		*exclusions = RRB_EX;
	else if (pac == rrr)
		*exclusions = RRR_EX;
	else if (pac == pa)
		*exclusions = PA_EX;
	else if (pac == pb)
		*exclusions = PB_EX;
	else if (pac != none)
		*exclusions = S_EX;
	if (asz <= 1)
		*exclusions &= A_IS_0_1;
	if (bsz == 1)
		*exclusions &= B_IS_1;
	else if (bsz == 0)
		*exclusions &= B_IS_0;
	return ;
}

static t_bool		next_lvl(t_brute *datas, char lvl, t_action pac)
{
	t_action		ac;
	unsigned short	exclusions;

	exclusions = -1;
	fill_exclusions(datas->list->asz, datas->list->bsz, pac, &exclusions);
	ac = 0;
	while (ac <= ss)
	{
		// qprintf("while: %3s auth(%hd)\n", action_name(ac), (exclusions & 0x1));
		if ((exclusions & 0x1) && ps_brute_solve_lvl(datas, lvl, ac))
			return (true);
		ac++;
		exclusions >>= 1;
	}
	return (false);
}

t_bool				ps_brute_solve_lvl(t_brute *datas, char lvl, t_action ac)
{
	apply_actions(datas->list, ac);
	if (lvl == datas->maxl)
	{
/* 		qprintf("==>\n"); */
/* 		print_list(datas->list); */
/* 		qprintf("<==\n"); */
		if (is_solved(datas->list) == true)
			return (save_step(datas->sol, &ac));
		rev_actions(datas->list, ac);
		return (false);
	}
	else if (next_lvl(datas, lvl + 1, ac) == true)
		return (save_step(datas->sol, &ac));
	rev_actions(datas->list, ac);
	return (false);
}
#define MAX_BRUTE_LVL 11

int					ps_brute_solve(t_pslist *orig, t_list *solution[1])
{
	t_brute		datas;
	int			i;

	i = 0;
	while (i <= MAX_BRUTE_LVL)
	{
		ft_bzero(&datas, sizeof(t_brute));
		datas.list = (t_pslist*)ft_memdup(orig, sizeof(t_pslist));
		datas.maxl = i;
		qprintf("\nCalling for %d:\n", i);
		if (ps_brute_solve_lvl(&datas, 0, none) == true)
		{
			i = MAX_BRUTE_LVL;
			qprintf("true.\n");
		}
		else
		{
			qprintf("false.\n");
		}
		print_list(datas.list);
		free(datas.list);
		i++;
	}
	*solution = *datas.sol;
	return (1);
}
