CC = cc

NAME = pipex

CFLAGS = -Wall -Wextra -Werror -fsanitize=address
# CFLAGS = -g

BONUS = pipex_bonus

OBJSFOLDER = objs/

FOLD_UTILS = utils/

FOLD_PIPE = pipe_processing/

FOLD_ERROR = error_checking/

FOLD_HELPERS = helpers/

SRCS_UTILS = ft_strjoin.c \
			 ft_memcpy.c \
			 ft_memcmp.c \
			 ft_strncmp.c \
			 ft_strlcpy.c \
			 ft_split.c \
			 ft_strlen.c \
			 ft_free_split.c \
			 ft_putstr_fd.c

SRCS_ERROR = error_check.c

SRCS_PIPE = pipe_process.c

SRCS_GNL = get_next_line.c \
		   get_next_line_utils.c

SRCS_HELPERS = helpers.c

OBJS_FILES = $(SRCS_UTILS:.c=.o) \
			 $(SRCS_ERROR:.c=.o) \
			 $(SRCS_PIPE:.c=.o) \
			 $(SRCS_GNL:.c=.o) \
			 $(SRCS_HELPERS:.c=.o)

OBJS_FILES_BONUS = $(OBJS_FILES) \
				   bonus_helpers.o

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

OBJS_BONUS = $(foreach obj, $(OBJS_FILES_BONUS), $(OBJSFOLDER)$(obj))

all: $(OBJSFOLDER) $(NAME)

bonus: $(OBJSFOLDER) $(BONUS)

$(NAME): $(OBJS)

$(BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $^ $(BONUS).c -o $(NAME)

$(OBJSFOLDER):
	@mkdir $@

$(OBJSFOLDER)%.o:$(FOLD_UTILS)%.c include/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o:$(FOLD_PIPE)%.c include/pipe_process.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o:$(FOLD_ERROR)%.c include/error_check.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o:gnl/%.c include/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o:$(FOLD_HELPERS)%.c include/helpers.h include/bonus_helpers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re bonus all
