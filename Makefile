CC = cc

NAME = pipex

CFLAGS = -Wall -Wextra -Werror

OBJSFOLDER = objs/

FOLD_UTILS = utils/

SRCS_UTILS = ft_strjoin.c \
			 ft_memcpy.c \
			 ft_memcmp.c \
			 ft_strncmp.c \
			 ft_strlcpy.c \
			 ft_split.c \
			 ft_strlen.c

SRCS_GNL = get_next_line.c \
		   get_next_line_utils.c

OBJS_FILES = $(SRCS_UTILS:.c=.o) \
			 $(SRCS_GNL:.c=.o)

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

$(OBJSFOLDER)%.o:$(FOLD_UTILS)%.c include/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o:gnl/%.c include/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re bonus all
