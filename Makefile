SRC_C	=	./client.c
SRC_S	=	./server.c

OBJ_C	=	${SRC_C:.c=.o}
OBJ_S	=	${SRC_S:.c=.o}
#--------------------------------------//---------------------------------------
NAME	=	client
NAME2	=	server

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
#--------------------------------------//---------------------------------------
clean:
	@rm -rf $(OBJ_C) $(OBJ_S)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|         Arquivos .o Deletados        |"
	@echo "\\ ************************************ /"
	@echo ""

fclean:		clean
	@rm -rf $(NAME) $(NAME2)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|       Client e Server Deletados      |"
	@echo "\\ ************************************ /"
	@echo ""
#--------------------------------------//---------------------------------------

re:			fclean all

.PHONY:		all clean fclean re