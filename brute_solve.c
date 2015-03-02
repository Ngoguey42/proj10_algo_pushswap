/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute_solve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 10:44:54 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/17 11:57:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

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

static void		a_limit_exclusions(DBUFF_T asz, t_action pact,
					t_dbyte *exclusions)
{
	if (asz <= 1)
		*exclusions &= A_IS_0_1;
	else if (asz == 2)
	{
		if (pact == rr || pact == rrr || pact == ss || pact == sa)
			*exclusions &= A_IS_2_PREV_SWAP;
		else
			*exclusions &= A_IS_2;
	}
	else if (asz == 3)
	{
		if (pact == ra || pact == rr)
			*exclusions &= A_IS_3_PREV_R;
		else if (pact == rra || pact == rrr)
			*exclusions &= A_IS_3_PREV_RR;
	}
	return ;
}

static void		b_limit_exclusions(DBUFF_T bsz, t_action pact,
					t_dbyte *exclusions)
{
	if (bsz == 1)
		*exclusions &= B_IS_1;
	else if (bsz == 0)
		*exclusions &= B_IS_0;
	else if (bsz == 2)
	{
		if (pact == rr || pact == rrr || pact == ss || pact == sb)
			*exclusions &= B_IS_2_PREV_SWAP;
		else
			*exclusions &= B_IS_2;
	}
	else if (bsz == 3)
	{
		if (pact == rb || pact == rr)
			*exclusions &= B_IS_3_PREV_R;
		else if (pact == rrb || pact == rrr)
			*exclusions &= B_IS_3_PREV_RR;
	}
	return ;
}

static t_bool	next_lvl(t_psl *l, t_action pact, t_byte lvl, t_byte maxl)
{
	t_action		act;
	t_dbyte			exclusions;
	const t_dbyte	exc1[] = {RA_EX, RB_EX, RR_EX, RRA_EX, RRB_EX,

	RRR_EX, PA_EX, PB_EX, S_EX, S_EX, S_EX, -1};
	if (BZS == (size_t)(maxl - lvl + 1))
		exclusions = PA;
	else if (BZS > (size_t)(maxl - lvl + 1))
		exclusions = 0;
	else
	{
		exclusions = exc1[pact];
		a_limit_exclusions(AZS, pact, &exclusions);
		b_limit_exclusions(BZS, pact, &exclusions);
	}
	act = 0;
	while (act <= ss)
	{
		if ((exclusions & 0x1) && ps_brute_solve_lvl(l, act, lvl, maxl))
			return (true);
		act++;
		exclusions >>= 1;
	}
	return (false);
}

inline t_bool	ps_brute_solve_lvl(t_psl *l, t_action act, t_byte lvl,
					t_byte maxl)
{
	if (act != none)
		apply_action(l, act);
	if (lvl == maxl)
	{
		if (ps_is_solved(l))
			return (true);
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

t_bool			ps_brute_solve(t_psl *l)
{
	int			i;

	i = 0;
	while (i <= MAX_BRUTE_LVL)
	{
		if (ps_brute_solve_lvl(l, none, 0, i) == true)
			return (true);
		i++;
	}
	return (false);
}
