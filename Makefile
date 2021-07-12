SRC_C	=	./client.c
SRC_S	=	./server.c

OBJ_C	=	${SRC_C:.c=.o}
OBJ_S	=	${SRC_S:.c=.o}
#--------------------------------------//---------------------------------------
SRC_BC	=	./client_bonus.c
SRC_BS	=	./server_bonus.c

OBJ_BC	=	${SRC_BC:.c=.o}
OBJ_BS	=	${SRC_BS:.c=.o}
#--------------------------------------//---------------------------------------
NAME	=	client
NAME2	=	server

BONUS	=	client_b
BONUS2	=	server_b

FLAGS	=	-Wall -Wextra -Werror

INCLUDE	=	minitalk.h

CC		=	clang
#--------------------------------------//---------------------------------------
.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}
	@echo "  Criando .o de "$<
#--------------------------------------//---------------------------------------
all:		$(NAME) $(NAME2) $(INCLUDE)

$(NAME):	$(OBJ_C)
	@$(CC) $(FLAGS) $(OBJ_C) -o $(NAME)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|            Cliente Criado            |"
	@echo "\\ ************************************ /"
	@echo ""

$(NAME2):	$(OBJ_S)
	@$(CC) $(FLAGS) $(OBJ_S) -o $(NAME2)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|            Servidor Criado           |"
	@echo "\\ ************************************ /"
	@echo ""

bonus: $(BONUS) $(BONUS2)

$(BONUS): $(OBJ_BC)
	@$(CC) $(CFLAGS) $(OBJ_BC) -o $(BONUS)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|         Cliente Bonus Criado          |"
	@echo "\\ ************************************ /"
	@echo ""

$(BONUS2): $(OBJ_BS)
	@$(CC) $(CFLAGS) $(OBJ_BS) -o $(BONUS2)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|         Servidor Bonus Criado         |"
	@echo "\\ ************************************ /"
	@echo ""

#--------------------------------------//---------------------------------------
clean:
	@rm -rf $(OBJ_C) $(OBJ_S) $(OBJ_BC) $(OBJ_BS)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|         Arquivos .o Deletados        |"
	@echo "\\ ************************************ /"
	@echo ""

fclean:		clean
	@rm -rf $(NAME) $(NAME2) $(BONUS) $(BONUS2)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|       Client e Server Deletados      |"
	@echo "\\ ************************************ /"
	@echo ""
#--------------------------------------//---------------------------------------

re:			fclean all

reb:		fclean bonus

.PHONY:		all bonus clean fclean re reb