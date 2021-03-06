#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/04 11:28:17 by ngoguey           #+#    #+#              #
#    Updated: 2015/06/01 17:56:43 by ngoguey          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = push_swap

# LIBFT
LFTPATH = libft/
LFTIPATH = -I $(LFTPATH)includes/
LFT = -L $(LFTPATH) -lft

OBJPATH = obj
SRCPATH = .
INCLUDE = -I ./

CC = clang

LIBS = $(LFT)
INCLUDES = $(INCLUDE) $(LFTIPATH)

BASEFLAGS = -Wall -Wextra
CFLAGS = $(BASEFLAGS) -Werror -O2
DEBUGFLAGS = $(BASEFLAGS) -g

LFTCALL = all
LFTRE = re
LFTG = g
LFTGRE = gre

SRCSFILES = main.c tools.c\
put_struct_ps2.c put_struct_ps.c\
apply_actions.c apply_actions_pertype.c\
brute_solve.c\
set_solve.c set_save.c set_to_b.c set_to_a.c set_solutions.c\
debug.c debug_dbuff.c


SRC = $(addprefix $(SRCPATH)/,$(SRCSFILES))
OBJECTS = $(SRC:$(SRCPATH)/%.c=$(OBJPATH)/%.o)

RM = rm -rf

Y = \033[0;33m
R = \033[0;31m
G = \033[0;32m
E = \033[39m

W = 0

all: l $(NAME)

$(NAME): $(OBJECTS)
	@echo -e "$(Y)[COMPILING PUSHSWAP] $(G) $(CC) -o $@ $(CFLAGS) objs.o $(LIBS) $(E)"
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBS)
	@echo -e "$(Y)[COMPILING PUSHSWAP]$(E)"

$(OBJECTS): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@if [ $(W) -eq 0 ] ; then printf "$(R)%-10s$(E): %s\n$(R)%-10s$(E): %s\n$(R)%-10s$(E): %s\n$(R)%-10s$(E): %s\n"\
		"=>COMPILER"\
		"$(CC)"\
		"=>CFLAGS"\
		"$(CFLAGS)"\
		"=>INCLUDES"\
		"$(INCLUDES)" ;\
	fi
	$(eval W = 1)
	@mkdir -p $(dir $@)
	@echo -e "$(R)COMPILER$(E) -o $@ $(R)CFLAGS INCLUDES$(E) -c [...].c"
	@$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

clean:
	$(RM) $(OBJPATH)

fclean: clean
	$(RM) $(NAME)

l:
	@echo -e "$(Y)[COMPILING LIBFT] $(G) make -C $(LFTPATH) $(LFTCALL) $(E)"
	@$(MAKE) -C $(LFTPATH) $(LFTCALL)
	@echo -e "$(Y)[COMPILING LIBFT DONE]$(E)"

g: _g _gft all

# re rules
re: fclean all
rel: _relft l
rea: _relft re

# gre rules
gre: _g re
grel: _greft l
grea: _g _greft re

# eval rules
_g:
	$(eval CFLAGS = $(DEBUGFLAGS))
_relft:
	$(eval LFTCALL = $(LFTRE))
_gft:
	$(eval LFTCALL = $(LFTG))
_greft:
	$(eval LFTCALL = $(LFTGRE))
