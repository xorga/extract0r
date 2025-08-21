NAME = extract0r
CC = gcc
CFLAGS = -g
SRC_FOLDER = 0x_srcs
SRCS = $(wildcard $(SRC_FOLDER)/*.c)
OBJS = $(SRCS:.c=.o)
LDFLAGS = -lcurl

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
NC = \033[0m

all: show_art $(NAME) auto_clean
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(NC)"

show_art:
	@clear
	@echo "$(GREEN)"
	@cat art/low.tix 2>/dev/null || echo "ASCII art not found"
	@echo "$(NC)"
	@sleep 1

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	@echo "$(BLUE)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

auto_clean:
	@rm -f $(OBJS)
	@echo "$(GREEN)Object files cleaned automatically$(NC)"

clean:
	@rm -f $(OBJS)
	@echo "$(GREEN)Object files cleaned$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)Executable removed$(NC)"

re: fclean all

.PHONY: all clean fclean re show_art auto_clean
