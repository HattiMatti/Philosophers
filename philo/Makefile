# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msiitone <msiitone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 13:51:55 by msiitone          #+#    #+#              #
#    Updated: 2024/06/11 13:54:09 by msiitone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/main.c srcs/philo_utils.c srcs/erfre.c srcs/philosophers.c srcs/actions.c \
	srcs/monitor_utils.c srcs/arg_check.c

CFLAGS = -Wall -Wextra -Werror

COMPILE = cc

INCLUDES = includes/philo.h

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(COMPILE) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean flcean re
