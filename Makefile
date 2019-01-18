# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cababou <cababou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/13 22:39:07 by cababou           #+#    #+#              #
#    Updated: 2019/01/18 00:02:54 by cababou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLEAR_LINE	:= \033[2K
BEGIN_LINE	:= \033[A
COL_END		:= \033[0m
COL_RED		:= \033[1;31m
COL_GREEN	:= \033[1;32m
COL_YELLOW	:= \033[1;33m
COL_BLUE	:= \033[1;34m
COL_VIOLET	:= \033[1;35m
COL_CYAN	:= \033[1;36m
COL_WHITE	:= \033[1;37m

NAME :=	wolf3d

SRC :=	wolf3d.c events.c game_logic/main_loop.c

OBJ := $(SRC:.c=.o)

PWD :=		$(shell pwd)
FRAMEWORKSDIR = /Library/Frameworks
SDL2_FRAMEWORKS =	-framework SDL2 -framework SDL2_image \
					-framework SDL2_mixer -framework SDL2_ttf\
					-framework SDL2_net

SRCDIR := src
OBJDIR := obj

SRCP :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJP :=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR :=	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

LIB := ./libft

FLAG := -g
SDL := -I/Library/Frameworks/SDL2.framework/Headers/ -framework SDL2 -framework Cocoa

MLX := -lmlx -framework OpenGL -framework AppKit

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell ls $(PWD)/obj/ 2> /dev/null | wc -l | sed -e 's/ //g')

all : libft_comp $(NAME)

$(NAME) : $(OBJP)
			@gcc $(FLAG) $(SDL) $(MLX) $(OBJP) ./libft/libft.a -o $(NAME)
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_END)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p $(ONLYDIR)
			@gcc -c $(FLAG) $< -o $@
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Compiling file [$(COL_VIOLET)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

libft_comp:
			@make -C $(LIB)

clean :
			@rm -rf $(OBJDIR)
			@make clean -C $(LIB)
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)compiled objects.$(COL_END)"

fclean :	clean
			@rm -rf $(NAME)
			@make fclean -C $(LIB)
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)$(NAME)$(COL_END)"

re :		fclean all
