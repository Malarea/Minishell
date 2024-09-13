# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wben-far <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 18:54:18 by wben-far          #+#    #+#              #
#    Updated: 2022/04/13 12:34:52 by wben-far         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#####                              FILES VARS                              #####
################################################################################

NAME		=	libft.a

D_INCLUDES	=	includes/

D_OBJS		=	objs/

D_SRCS		=	srcs/

_SRC_		=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
				ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c \
				ft_atoi.c ft_isalpha.c ft_is_ws.c ft_isdigit.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
				ft_strtrim.c ft_split.c ft_free_arr.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_malloc.c

SRCS		=	$(addprefix $(D_SRCS), $(_SRC_))

OBJS		=	$(addprefix $(D_OBJS), $(_SRC_:.c=.o))

################################################################################
#####                           COMPILER OPTIONS                           #####
################################################################################

CC			=	clang

FLAGS		=	-Wall -Wextra -Werror

AR			=	ar -rcs

################################################################################
#####                            MAKEFILE RULES                            #####
################################################################################

.PHONY : all bonus clean fclean re

all : $(D_OBJS) $(NAME)

compiling_start:
	@python3 -c 'print("\033[0;33m\u2192 " + "\033[0;36mCompiling \033[1;33m$(NAME)\033[0;36m sources... \033[0m")'

compiling_end :
	@python3 -c 'print("\033[0;32mCompiling successful \u2713 \033[0m")'

$(D_OBJS) :
	@mkdir -p $@

$(D_OBJS)%.o : $(D_SRCS)%.c
	@$(CC) $(FLAGS) -c $< -o $@ -Iincludes

$(NAME) : compiling_start $(OBJS) compiling_end
	@python3 -c 'print("\033[0;33m\u2192 " + "\033[0;36mLinking objects for \033[1;33m$(NAME)\033[0;33m... \033[0m")'
	@$(AR) $(NAME) $(OBJS)
	@python3 -c 'print("\033[0;32mLinking successful \u2713 \033[0m")'

clean :
	@rm -rf $(D_OBJS)
	@python3 -c 'print("\033[0;36mObjects deleted \u2713 \033[0m")'

fclean : clean
	@rm -rf $(NAME)
	@python3 -c 'print("\033[1;33m$(NAME) \033[0;36mdeleted \u2713 \033[0m")'

re : fclean all