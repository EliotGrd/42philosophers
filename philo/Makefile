NAME = philo

SRC_PATH = srcs/
OBJ_PATH = build/

SRC = main.c parsing.c utils.c 

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
DPD = $(addprefix $(OBJ_PATH), $(SRC:.c=.d))

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -g #-fsanitize=address,leak,undefined
INCS = includes/philo.h
INC = -Iincludes

PURPLE = \033[0;35m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(INCS)
	@echo "\n$(PURPLE)  Compiling Philosophers...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME)
	@echo "\n$(PURPLE)  Ready ✓$(NC)\n"

-include $(DPD)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@echo "\n$(PURPLE)  Cleaning object files... $(NC)"
	@rm -rf $(OBJ_PATH)
	@rm -rf $(OBJ) $(OBJ_BON)
	@rm -rf $(DPD) $(OBJ_DPD)
	@echo "\n$(PURPLE)  Done ✓$(NC)"

fclean: clean
	@echo "\n$(PURPLE)  Cleaning Philosophers...$(NC)"
	@$(RM) $(NAME)
	@$(RM) $(NAME_BON)
	@echo "\n$(PURPLE)  Done ✓$(NC)"

dev: all clean
 
re: fclean all

.PHONY: all clean fclean re dev
