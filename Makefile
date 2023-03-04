CC = cc

NAME = pipex

CFLAGS = -Wall -Wextra -Werror

OBJSFOLDER = objs/

FOLD_UTILS = utils/

UTILS_SRCS = ft_strjoin.c \
			 ft_memcpy.c \
			 ft_memcmp.c \
			 ft_strncmp.c \
			 ft_strlcpy.c \
			 ft_split.c \
			 ft_strlen.c

OBJS_FILES = $(UTILS_SRCS:.c=.o)

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

$(OBJSFOLDER)%.o:$(FOLD_UTILS)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re bonus all
