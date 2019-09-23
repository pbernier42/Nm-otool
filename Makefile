PROJECT_NM		=	FT_NM
PROJECT_OTOOL	=	FT_OTOOL

NAME_NM			=	ft_nm
NAME_OTOOL		=	ft_otool

NO_TO_BE		=	ON

DIR_OBJ			=	objs/
DIR_SRC			=	srcs/
DIR_INC			=	includes/

CC				=	gcc
FLAGS			=	-Wall -Werror -Wextra -Wpadded
INCLUDES		=	-I $(DIR_INC)

DIR_NM			=	ft_nm/
DIR_OTOOL		=	ft_otool/
DIR_UTILS		=	utils/

SRC_INCLUDE		=	error.h \
					ft_nm.h \
					ft_otool.h \
					struct.h \
					utils.h

SRC_NM			=	main_nm.c
SRC_OTOOL		=	f_fat_otool.c \
					f_match_otool.c \
					main_otool.c \
					print_otool.c \
					open_otool.c \
					read_otool.c \
SRC_UTILS		=	count.c \
					print.c \
					erroc.c

INC				=	$(addprefix $(DIR_INC),$(SRC_INCLUDE))

SRCS_NM			=	$(addprefix $(DIR_SRC)$(DIR_NM), $(SRC_NM))
SRCS_OTOOL		=	$(addprefix $(DIR_SRC)$(DIR_OTOOL), $(SRC_OTOOL))
SRCS_UTILS		=	$(addprefix $(DIR_SRC)$(DIR_UTILS), $(SRC_UTILS))

PATH_OBJ_NM		=	$(DIR_OBJ)$(DIR_NM)
PATH_OBJ_UTILS	=	$(DIR_OBJ)$(DIR_UTILS)
PATH_OBJ_OTOOL	=	$(DIR_OBJ)$(DIR_OTOOL)
PATH_OBJ_ALL	=	$(PATH_OBJ_NM) $(PATH_OBJ_UTILS) $(PATH_OBJ_OTOOL)

OBJS_NM			=	$(addprefix $(PATH_OBJ_NM),$(SRC_NM:.c=.o))
OBJS_UTILS		=	$(addprefix $(PATH_OBJ_UTILS),$(SRC_UTILS:.c=.o))
OBJS_OTOOL		=	$(addprefix $(PATH_OBJ_OTOOL),$(SRC_OTOOL:.c=.o))

UND				= \033[4m
RES				= \033[0m

all: $(NAME_NM)
ifeq ($(NO_TO_BE),OFF)
	@echo > /dev/null
endif

# help:
# 	@printf "[$(PROJECT)] make \n"
# 	@printf "    		-- compile the project '$(NAME)'\n"
# 	@printf "  $(NAME)	-- compile the project '$(NAME)'\n"
# 	@printf "  clean	-- remove \'$(DIR_OBJ)\' and all \'.o\' files from it\n"
# 	@printf "  fclean	-- $(UND)clean$(RES) and remove '$(NAME)' and '$(LINK)'\n"
# 	@printf "  re		-- $(UND)fclean$(RES) then $(UND)make$(RES)\n"

$(NAME_NM): $(PATH_OBJ_NM) $(OBJS_NM)

	@printf "[$(PROJECT_NM)] Objs compilation done.                    \n"
	@$(CC) -o $(NAME_NM) $(INCLUDES) $(FLAGS) $(OBJS_NM)
	@printf "[$(PROJECT_NM)] $(NAME_NM) compiled.\n"

# $(NAME_OTOOL): $(PATH_OBJ_OTOOL) $(OBJS_OTOOL)
# 	@printf "[$(PROJECT_OTOOL)] Objs compilation done.                    \n"
# 	@$(CC) -o $(NAME_OTOOL) $(FLAGS) $(OBJS_OTOOL)
# 	@printf "[$(PROJECT_OTOOL)] $(NAME_OTOOL) compiled.\n"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(INC) Makefile
	@printf "[???] Compiling $(notdir $<) to $(notdir $@)              \r"
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(PATH_OBJ_ALL):
	mkdir -p $@





clean:
	@rm -rf $(DIR_OBJ)
#@printf "[ALL] Obj removed.\n"

clean_utils:
	@rm -rf $(PATH_OBJ_UTILS)

clean_nm: clean_utils
	@rm -rf $(PATH_OBJ_NM)
#@printf "[$(PROJECT_NM)] Obj removed.\n"

clean_otool: clean_utils
	@rm -rf $(PATH_OBJ_OTOOL)
#@printf "[$(PROJECT_OTOOL)] Obj removed.\n"

fclean: clean fclean_nm fclean_otool

fclean_nm : clean_nm
	@rm -f $(NAME_NM)
#@printf "[$(PROJECT_NM)] \"$(NAME_NM)\" removed.\n"

fclean_otool : clean_otool
	@rm -f $(NAME_OTOOL)
#@printf "[$(PROJECT_NM)] \"$(NAME_NM)\" removed.\n"

re: fclean $(NAME)

.PHONY: all help flag clean fclean re
