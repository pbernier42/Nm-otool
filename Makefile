PROJECT_NM		=	FT_NM
PROJECT_OTOOL	=	FT_OTOOL

NAME_NM			=	ft_nm
NAME_OTOOL		=	ft_otool

NO_TO_BE		=	ON

DIR_OBJ			=	objs/
DIR_SRC			=	srcs/
DIR_INC			=	includes/

CC				=	gcc
FLAGS			=	-Wall -Werror -Wextra
INCLUDES		=	-I $(DIR_INC)

DIR_NM			=	ft_nm/
DIR_OTOOL		=	ft_otool/

SRC_INCLUDE		=	ft_nm_otool.h match_o.h

SRC_NM			=	ft_nm.c
SRC_OTOOL		=	ft_otool.c print_otool.c read_otool.c

INC				=	$(addprefix $(DIR_INC),$(SRC_INCLUDE))

SRCS_NM			=	$(addprefix $(DIR_SRC)$(DIR_NM),$(SRC_NM))
SRCS_OTOOL		=	$(addprefix $(DIR_SRC)$(DIR_OTOOL),$(SRC_OTOOL))

PATH_OBJ_NM		=	$(DIR_OBJ)$(DIR_NM)
PATH_OBJ_OTOOL	=	$(DIR_OBJ)$(DIR_OTOOL)

OBJS_NM			=	$(addprefix $(PATH_OBJ_NM),$(SRC_NM:.c=.o))
OBJS_OTOOL		=	$(addprefix $(PATH_OBJ_OTOOL),$(SRC_OTOOL:.c=.o))

UND				= \033[4m
RES				= \033[0m

all: $(NAME_NM) $(NAME_OTOOL)
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
	@$(CC) -o $(NAME_NM) $(FLAGS) $(OBJS_NM)
	@printf "[$(PROJECT_NM)] $(NAME_NM) compiled.\n"

$(NAME_OTOOL): $(PATH_OBJ_OTOOL) $(OBJS_OTOOL)
	@printf "[$(PROJECT_OTOOL)] Objs compilation done.                    \n"
	@$(CC) -o $(NAME_OTOOL) $(FLAGS) $(OBJS_OTOOL)
	@printf "[$(PROJECT_OTOOL)] $(NAME_OTOOL) compiled.\n"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(INC) Makefile
	@printf "[???] Compiling $(notdir $<) to $(notdir $@)              \r"
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(DIR_OBJ)%:
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $@

clean:
	@rm -rf $(DIR_OBJ)
#@printf "[ALL] Obj removed.\n"

clean_nm:
	@rm -rf $(PATH_OBJ_NM)
#@printf "[$(PROJECT_NM)] Obj removed.\n"

clean_otool:
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
