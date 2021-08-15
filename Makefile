NAME=philo
SRC=	src/action.c src/init.c src/main.c src/ft_atoi.c src/ft_strncmp.c
OBJ= $(SRC:.c=.o)
CC= gcc
INC = inc
CFLAGS= -Wall -Wextra -Werror
RM= rm -f

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INC) $< -c -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


clean:
	@$(RM) $(OBJ)

fclean: clean
	@echo "Removing binary file"
	@$(RM) $(NAME)

re: fclean all