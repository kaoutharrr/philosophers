# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkouaz <kkouaz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/18 12:21:16 by kkouaz            #+#    #+#              #
#    Updated: 2023/06/24 18:28:46 by kkouaz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror   -pthread 
RM  = rm -rf
SRC = main.c parse.c tools.c  ft_split.c philo.c tools2.c 
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean : 
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
#-fsanitize=thread