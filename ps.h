/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:44 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/01 18:00:27 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include <ft_debug.h>
# include <libft.h>

# define MAX_BRUTE_LVL 12
# define SOFT_CAP 10
# define HARD_CAP 10
# define MAX_SET_MOVEMENTS (1000 * 1000 * 1)

# define PS_TYPE DBUFF_T

# define BZF (l->bl.zone_front)
# define BZR (l->bl.zone_rear)
# define BZS (l->bl.zone_size)

# define AZF (l->al.zone_front)
# define AZR (l->al.zone_rear)
# define AZS (l->al.zone_size)

/*
** ************************************************************************** **
** Game handling.
*/

typedef struct	s_corresp
{
	int			*ref;
	PS_TYPE		*corresp;
}				t_corresp;

/*
**	'struct s_psl' represents the game at a given time.
**			'act'	previous actions.
**			'al'	a list state
**			'bl'	b list state
*/
typedef struct	s_psl
{
	t_dstor		act;
	t_dbuff		al;
	t_dbuff		bl;
}				t_psl;

/*
**	'enum e_action' available actions.
*/
typedef enum	e_action
{
	ra,
	rb,
	rr,
	rra,
	rrb,
	rrr,
	pa,
	pb,
	sa,
	sb,
	ss,
	none
}				t_action;
# define RA  0b00000000001
# define RB  0b00000000010
# define RR  0b00000000100
# define RRA 0b00000001000
# define RRB 0b00000010000
# define RRR 0b00000100000
# define PA  0b00001000000
# define PB  0b00010000000
# define SA  0b00100000000
# define SB  0b01000000000
# define SS  0b10000000000

void			rev_action(t_psl *l);
void			apply_action(t_psl *l, t_action act);
void			apply_actions_s(t_psl *l, t_action act);
void			apply_actions_p(t_psl *l, t_action act);
void			apply_actions_rr(t_psl *l, t_action act);
void			apply_actions_r(t_psl *l, t_action act);
/*
** ************************************************************************** **
** 'Set' solving.
** Part 1:	for the initial list	build multiple sets.
** Part 2:	for each sets			build multiple ways to send to b-list.
** Part 3:	for each ways			build multiple ways to send back to a-list.
** Part 4:	Keep the shortest result.
*/

/*
**	'struct s_set' represents a single set found in list a, before any action.
**			'first'		first value of the set
**			'last'		last value of the set
**			'len'		length of the set
**			'ptr'		pointer to the first value in the main 'struct s_psl'.
**			'to_b'		list of the ways to send numbers to b-list.
*/
typedef struct	s_set
{
	PS_TYPE		first;
	PS_TYPE		*ptr;
	PS_TYPE		len;
	PS_TYPE		last;
	t_list		*to_b[1];
}				t_set;

/*
**	'struct s_tob' represents a single way to send numbers to b.
**			'l'			state of the game, after this part.
**			'to_a'		list of the ways to send numbers to a-list.
*/
typedef struct	s_tob
{
	t_psl		*l;
	t_list		*to_a[1];
}				t_tob;

void			ps_set_solve(t_psl *l);
void			ps_build_sets(const t_psl *l, t_list *lst[1]);
void			build_alternatives_to_b(const t_psl *l, t_set *s);
void			build_alternatives_to_a(t_tob *tob);
t_psl			*ps_solution_storing(t_psl *l);
void			ps_printbest_solution(void);
int				ps_total_movements(const t_psl *l);
/*
** ************************************************************************** **
** 'Brute' solving.
** Try each meaningful combinations, up to MAX_BRUTE_LVL(~13) actions.
*/
t_bool			ps_brute_solve(t_psl *l);
t_bool			ps_brute_solve_lvl(t_psl *l, t_action,
					t_byte lvl, t_byte maxl);
/*
** ************************************************************************** **
*/

/*
** Tools
*/
t_bool			ps_is_solved(const t_psl *l);
void			ps_dup_l(const t_psl *lref, t_psl **ldst);
void			ft_exit(char *str);
void			put_a_b_solved(t_corresp *corresp, int ac);
void			put_struct_ps(int *ac, char **av, t_corresp *corresp);
void			ps_free_l(t_psl **l, t_bool free_struct);

/*
** Debug
*/
const char	*ps_action_name(t_action action);
void		ps_print_dstor(const t_dstor *dstor);
void		ps_print_dbuff(const t_dbuff *dbuff);
void		ps_print_psl(const t_psl *psl);
void		ps_get_nb_grad(DBUFF_T nb, DBUFF_T init, char buf[16]);
void		ps_print_dbuff_content(const t_dbuff *dbuff);

#endif
