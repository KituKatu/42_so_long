files = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_exit_error.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_lstnew.c \
		ft_printf_utils.c \
		ft_printf_utils2.c \
		ft_printf.c \
		get_next_line.c

NAME = ../libft/libft.a
HEADERFILES = libft.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
CFILES = $(files:.c=.o)
OBJFILES = $(files:.c=.o)

$(NAME): $(OBJFILES)
	ar rcs $(NAME) $(OBJFILES)

%.o: %.c  
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

clean:
	rm -f $(OBJFILES)

fclean: clean 
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re