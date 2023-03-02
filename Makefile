CC = cc

NAME = pipex

CFLAGS = -Wall -Wextra -Werror

OBJSFOLDER = objs/

# FOLD_ALGO = algo/

# SRCS = main.c

OBJS_FILES = $(SRCS:.c=.o)

# OBJS_FILES_BONUS = $(SRCS_RULES:.c=.o) \

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

# OBJS_BONUS = $(foreach obj, $(OBJS_FILES_BONUS), $(OBJSFOLDER)$(obj))

all: $(OBJSFOLDER) $(NAME)

bonus: $(OBJSFOLDER) $(BONUS)

$(NAME): $(OBJS)

# $(BONUS): $(OBJS_BONUS) bonus/checker.c
# 	$(CC) $(CFLAGS) $^ -o $@

$(OBJSFOLDER):
	@mkdir $@

$(OBJSFOLDER)%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
