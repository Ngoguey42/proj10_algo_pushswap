/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:44 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/03 11:31:29 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include <ft_debug.h>
# include <libft.h>

# define RA 0b00000000001
# define RB 0b00000000010
# define RR 0b00000000100
# define RRA 0b00000001000
# define RRB 0b00000010000
# define RRR 0b00000100000
# define PA 0b00001000000
# define PB 0b00010000000
# define SA 0b00100000000
# define SB 0b01000000000
# define SS 0b10000000000

#define PS_TYPE unsigned short

typedef struct	s_pslist
{
	PS_TYPE		*a;
	PS_TYPE		asz;
	PS_TYPE		*b;
	PS_TYPE		bsz;
}				t_pslist;

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

typedef struct	s_brute
{
	t_pslist	*list;
	t_list		*sol[1];
	PS_TYPE		maxl;
}				t_brute;

typedef struct	s_psl
{
	t_dstor		act;
	t_dbuff		al;
	t_dbuff		bl;
}				t_psl;

/*
** Tools
*/
/* t_bool			save_step(t_list *sol[1], const t_action *ac); */
t_bool			is_solved(const t_psl *l);
/* t_bool			is_solved(const t_pslist *list); */

/*
** Apply action to list
*/
void			rev_action(t_psl *l);
void			apply_action(t_psl *l, t_action act);
/* void			rev_actions(t_pslist *list, t_action ac); */
/* void			apply_actions(t_pslist *list, t_action ac); */

void			apply_actions_s(t_psl *l, t_action act);
void			apply_actions_p(t_psl *l, t_action act);
void			apply_actions_rr(t_psl *l, t_action act);
void			apply_actions_r(t_psl *l, t_action act);

/*
** Brute solve
*/
/* t_bool			ps_brute_solve_lvl(t_pslist *list, t_list *sol[1], */
/* 					char lvl, t_action ac); */
int				ps_brute_solve(t_pslist *orig, t_list *solution[1]);
t_bool			ps_brute_solve_lvl(t_brute *datas, char lvl, t_action ac);


/*
** Debug
*/
const char		*ps_action_name(t_action action);
/* void			print_list(const t_pslist *list); */
/* void			ps_print_sol(const t_list *solutions); */
void        ps_print_dstor(const t_dstor *dstor);
void        ps_print_dbuff(const t_dbuff *dbuff);
void		ps_print_psl(const t_psl *psl);

#endif
