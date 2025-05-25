## Commands ##
CC = cc
INCLUDES = -I ./include -I $(LIBMLX)/include
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -MMD -MP -g $(INCLUDES) #-g -fsanitize=address
#CFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -framework OpenGL $(INCLUDES)
LIBMLX = ./MLX42
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LDFLAGS = -L./libft -lft
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p

## Files ##
SRCS = src/so_long.c \
		src/so_long_clean.c \
		src/so_long_map.c \
		src/so_long_map2.c \
		src/so_long_graph.c \
		src/so_long_handlers.c \
		
OBJS = $(SRCS:src/%.c=obj/%.o)
DEPS = $(OBJS:.o=.d)

## Configuration ##
NAME = so_long

## Targets ##
.PHONY: all clean fclean re libmlx

all: submodules libmlx $(NAME)

# Target to initialize and update submodules
submodules:
	git submodule update --init --recursive

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): obj $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

obj:
	@$(MKDIR) obj

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS) $(DEPS)
	$(RMDIR) $(LIBMLX)/build
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

libft/libft.a:
	$(MAKE) -C libft all
