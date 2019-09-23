PROJECT_NM		=	FT_NM
PROJECT_OTOOL	=	FT_OTOOL

NAME_NM_		=	ft_nm
NAME_OTO		=	ft_otool

NO_TO_BE		=	ON

DIR_OBJ			=	objs/
DIR_SRC			=	srcs/

DIR_INC			=	includes/
DIR_NM_			=	ft_nm/
DIR_OTO			=	ft_otool/
DIR_UTI			=	utils/

#wicard
SRC_INC			=	error.h			ft_nm.h			ft_otool.h		\
					struct.h 		utils.h

SRC_NM_			=	main_nm.c

SRC_OTO			=	f_fat_otool.c	f_match_otool.c	main_otool.c	\
					print_otool.c	open_otool.c	read_otool.c

SRC_UTI			=	count.c			print.c			error.c

CC				=	gcc
FLAGS			=	-Wall -Werror -Wextra -Wpadded
INCLUDES		=	-I $(DIR_INC)

SRC_INC			:=	$(addprefix $(DIR_INC),$(SRC_INC))
SRC_NM_			:=	$(addprefix $(DIR_SRC)$(DIR_NM_), $(SRC_NM_))
SRC_OTO			:=	$(addprefix $(DIR_SRC)$(DIR_OTO), $(SRC_OTO))
SRC_UTI			:=	$(addprefix $(DIR_SRC)$(DIR_UTI), $(SRC_UTI))

DIR_OBJ_NM_		=	$(DIR_OBJ)$(DIR_NM_)
DIR_OBJ_OTO		=	$(DIR_OBJ)$(DIR_OTO)
DIR_OBJ_UTI		=	$(DIR_OBJ)$(DIR_UTI)

DIR_OBJ_ALL		=	$(DIR_OBJ_NM_)	$(DIR_OBJ_UTI)	$(DIR_OBJ_OTO)

OBJ_NM_			=	$(subst $(DIR_SRC),$(DIR_OBJ),$(SRC_NM_:.c=.o))
OBJ_OTO			=	$(subst $(DIR_SRC),$(DIR_OBJ),$(SRC_OTO:.c=.o))
OBJ_UTI			=	$(subst $(DIR_SRC),$(DIR_OBJ),$(SRC_UTI:.c=.o))

DEP_NM_			=	$(DIR_OBJ_NM_)	$(OBJ_NM_)
DEP_OTO			=	$(DIR_OBJ_OTO)	$(OBJ_OTO)
DEP_UTI			=	$(DIR_OBJ_UTI)	$(OBJ_UTI)

all: $(NAME_NM_)
ifeq ($(NO_TO_BE),OFF)
	@echo > /dev/null
endif

$(NAME_NM_): $(DEP_NM_) $(DEP_UTI)
	printf "??"
NAME 			=	$(NAME_NM_)
OBJS			= 	$(OBJ_NM_)		$(OBJ_UTI)
DIRS			=	$(DIR_OBJ_NM_)	$(DIR_OBJ_UTI)
PROJECT			=	$(PROJECT_NM)

$(NAME_OTO): $(DEP_OTO) $(DEP_UTI)
NAME 			=	$(NAME_OTO)
OBJS			= 	$(OBJ_OTO)		$(OBJ_UTI)
DIRS			=	$(DIR_OBJ_OTO)	$(DIR_OBJ_UTI)
PROJECT			=	$(PROJECT_OTOOL)

$(NAME): $(DIRS) $(OBJS)
	@printf "[$(PROJECT)] Objs compilation done.                    \n"
	@$(CC) -o $(NAME) $(INCLUDES) $(FLAGS) $(OBJS)
	@printf "[$(PROJECT)] $(NAME) compiled.\n"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(SRC_INC) Makefile
	@printf "[$(PROJECT)] Compiling $(notdir $<) to $(notdir $@)            \n"
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(DIR_OBJ_ALL):
	@mkdir -p $@


# else
# 	@printf "2.$(MAKECMDGOALS)\n"
#endif



#
# $(NAME_NM): $(PATH_OBJ_NM) $(OBJS_NM)
# 	@printf "[$(PROJECT_NM)] Objs compilation done.                    \n"
# 	@$(CC) -o $(NAME_NM) $(INCLUDES) $(FLAGS) $(OBJS_NM)
# 	@printf "[$(PROJECT_NM)] $(NAME_NM) compiled.\n"
#
#
#
#
#
#
#
#
#
# clean:
# 	@rm -rf $(DIR_OBJ)
# #@printf "[ALL] Obj removed.\n"
#
# clean_utils:
# 	@rm -rf $(PATH_OBJ_UTILS)
#
# clean_nm: clean_utils
# 	@rm -rf $(PATH_OBJ_NM)
# #@printf "[$(PROJECT_NM)] Obj removed.\n"
#
# clean_otool: clean_utils
# 	@rm -rf $(PATH_OBJ_OTOOL)
# #@printf "[$(PROJECT_OTOOL)] Obj removed.\n"
#
# fclean: clean fclean_nm fclean_otool
#
# fclean_nm : clean_nm
# 	@rm -f $(NAME_NM)
# #@printf "[$(PROJECT_NM)] \"$(NAME_NM)\" removed.\n"
#
# fclean_otool : clean_otool
# 	@rm -f $(NAME_OTOOL)
# #@printf "[$(PROJECT_NM)] \"$(NAME_NM)\" removed.\n"
#
# re: fclean $(NAME)

.PHONY: all help flag clean fclean re


# help:
# 	@printf "[$(PROJECT)] make \n"
# 	@printf "    		-- compile the project '$(NAME)'\n"
# 	@printf "  $(NAME)	-- compile the project '$(NAME)'\n"
# 	@printf "  clean	-- remove \'$(DIR_OBJ)\' and all \'.o\' files from it\n"
# 	@printf "  fclean	-- $(UND)clean$(RES) and remove '$(NAME)' and '$(LINK)'\n"
# 	@printf "  re		-- $(UND)fclean$(RES) then $(UND)make$(RES)\n"
