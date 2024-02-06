# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 09:14:10 by btan              #+#    #+#              #
#    Updated: 2024/02/06 15:12:43 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDES = .

SRCS = philo_utils.c \
	   main.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -I$(INCLUDES)

clean:
	rm -rf $(OBJECTS) $(NAME).a

fclean: clean
	rm -rf $(NAME)


re: fclean all

debug: CFLAGS += -g -fsanitize=thread
debug: re

.PHONY: all clean fclean re
