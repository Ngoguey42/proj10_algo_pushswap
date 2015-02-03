/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute_solve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:44:54 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/03 14:42:22 by ngoguey          ###   ########.fr       */
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

static t_bool		next_lvl(t_psl *l, t_action pact, char lvl, char maxl)
{
	t_action		act;
	unsigned short	exclusions;

	exclusions = -1;
	fill_exclusions(AZS, BZS, pact, &exclusions);
	act = 0;
	while (act <= ss)
	{
		// qprintf("while: %3s auth(%hd)\n", action_name(ac), (exclusions & 0x1));
		if ((exclusions & 0x1) && ps_brute_solve_lvl(l, act, lvl, maxl))
			return (true);
		act++;
		exclusions >>= 1;
	}
	return (false);
}

t_bool				ps_brute_solve_lvl(t_psl *l, t_action act, char lvl, char maxl)
{
	if (act != none)
		apply_action(l, act);
	if (lvl == maxl)
	{
		if (ps_is_solved(l))
		{
/* 			ps_print_psl(l); */
			return (true);
		}
		if (act != none)
			rev_action(l);
		return (false);
	}
	else if (next_lvl(l, act, lvl + 1, maxl))
		return (true);
	if (act != none)
		rev_action(l);
	return (false);
}
#define MAX_BRUTE_LVL 10

int					ps_brute_solve(t_psl *l)
{
	int			i;

	i = 0;
	while (i <= MAX_BRUTE_LVL)
	{
		qprintf("\nCalling for %d:\n", i);
		if (ps_brute_solve_lvl(l, none, 0, i) == true)
		{
/* 			qprintf("true.\n"); */
			break ;
		}
		else
		{
/* 			qprintf("false.\n"); */
		}
		i++;
	}
	return (1);
}
