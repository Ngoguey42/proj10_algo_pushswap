/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute_solve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:44:54 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/04 10:27:09 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>
#include <stdlib.h>

#define RA_EX	(-1 - RB - RRA - RRR		- SB - RRB)
#define RB_EX	(-1 - RA - RRB - RRR		- SA - RRA)
#define RR_EX	(-1 - RRA - RRB - RRR)
#define RRA_EX	(-1 - RA - RRB - RR			- SB)
#define RRB_EX	(-1 - RB - RRA - RR			- SA)
#define RRR_EX	(-1 - RA - RB - RR)
#define PA_EX	(-1 - PB)
#define PB_EX	(-1 - PA)
#define S_EX	(-1 - SA - SB - SS)

#define A_IS_0_1	(-1 - SS - SA - PB - RRR - RR - RA - RRA)
#define B_IS_0		(-1 - SS - SB - PA - RRR - RR - RB - RRB)
#define B_IS_1		(-1 - SS - SB      - RRR - RR - RB - RRB)

#define A_IS_2				(-1 - RRA - RA)
#define B_IS_2				(-1 - RRB - RB)
#define A_IS_2_PREV_SWAP	(-1 - RRA - RA - RRR - RR - SA - SS)
#define B_IS_2_PREV_SWAP	(-1 - RRB - RB - RRR - RR - SB - SS)

#define A_IS_3_PREV_R		(-1 - RA - RR)
#define A_IS_3_PREV_RR		(-1 - RRA - RRR)
#define B_IS_3_PREV_R		(-1 - RB - RR)
#define B_IS_3_PREV_RR		(-1 - RRB - RRR)

#define MAX_BRUTE_LVL 14

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

static void			fill_exclusions(const t_psl *l, t_action pac,
						unsigned short *exclusions, t_byte lvl_left)
{
	const unsigned short	exc1[] = {RA_EX, RB_EX, RR_EX, RRA_EX, RRB_EX,

		RRR_EX, PA_EX, PB_EX, S_EX, S_EX, S_EX, -1};

	*exclusions = exc1[pac];
	if (AZS <= 1)
		*exclusions &= A_IS_0_1;
	else if (AZS == 2)
	{
		if (pac == rr || pac == rrr || pac == ss || pac == sa)
			*exclusions &= A_IS_2_PREV_SWAP;
		else
			*exclusions &= A_IS_2;
	}
	else if (AZS == 3)
	{
		if (pac == ra || pac == rr)
			*exclusions &= A_IS_3_PREV_R;
		else if (pac == rra || pac == rrr)
			*exclusions &= A_IS_3_PREV_RR;
	}
	if (BZS == 1)
		*exclusions &= B_IS_1;
	else if (BZS == 0)
		*exclusions &= B_IS_0;
	else if (BZS == 2)
	{
		if (pac == rr || pac == rrr || pac == ss || pac == sb)
			*exclusions &= B_IS_2_PREV_SWAP;
		else
			*exclusions &= B_IS_2;
	}
	else if (BZS == 3)
	{
		if (pac == rb || pac == rr)
			*exclusions &= B_IS_3_PREV_R;
		else if (pac == rrb || pac == rrr)
			*exclusions &= B_IS_3_PREV_RR;
	}
	(void)lvl_left;
	if (BZS == (size_t)lvl_left)
		*exclusions = PA;
	else if (BZS > (size_t)lvl_left)
		*exclusions = 0;
	return ;
}

static t_bool		next_lvl(t_psl *l, t_action pact, t_byte lvl, t_byte maxl)
{
	t_action		act;
	unsigned short	exclusions;

/* 	exclusions = -1; */
	fill_exclusions(l, pact, &exclusions, maxl - lvl + 1);
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

inline t_bool				ps_brute_solve_lvl(t_psl *l, t_action act, t_byte lvl, t_byte maxl)
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
