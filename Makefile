NAME			=	ircserv

HEADERS			=	-Iincludes

CXX				=	c++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98
# DEBUG_FLAGS		+=	-g3 -fsanitize=address

OBJS_DIR		=	objs

SRCS_DIR		=	./srcs/

#############################################################################
##########  Directories and their files within the SRCS directory  ##########

SERVER_DIR		=	./server/
SERVER_SRC		=	Server.cpp\
					Server_Util.cpp\

CLIENT_DIR		=	./client/
CLIENT_SRC		=	Client.cpp\

CHANNEL_DIR		=	./channel/
CHANNEL_SRC		=	Channel.cpp\

MESSAGE_DIR		=	./message/
MESSAGE_SRC		=	Message.cpp\

COMMAND_DIR		=	./command/
COMMAND_SRC		=	cap.cpp\
					join.cpp\
					invite.cpp\
					kick.cpp\
					mode.cpp\
					nick.cpp\
					part.cpp\
					pass.cpp\
					ping.cpp\
					privmsg.cpp\
					quit.cpp\
					topic.cpp\
					user.cpp\

RPL_DIR		=		./RPL/
RPL_SRC		=		RPL.cpp\
					BOT.cpp\
					INVITE.cpp\
					JOIN.cpp\
					KICK.cpp\
					MODE.cpp\
					NICK.cpp\
					PART.cpp\
					PASS.cpp\
					PING.cpp\
					PRIVMSG.cpp\
					QUIT.cpp\
					TOPIC.cpp\
					USER.cpp\
					WELCOME.cpp\

UTIL_DIR		=	./util/
UTIL_SRC		=	$(addprefix $(RPL_DIR), $(RPL_SRC))\
					Parsing.cpp\
					Check.cpp\
					print.cpp\


SRC				=	main.cpp\
					$(addprefix $(SERVER_DIR), $(SERVER_SRC))\
					$(addprefix $(CLIENT_DIR), $(CLIENT_SRC))\
					$(addprefix $(CHANNEL_DIR), $(CHANNEL_SRC))\
					$(addprefix $(MESSAGE_DIR), $(MESSAGE_SRC))\
					$(addprefix $(COMMAND_DIR), $(COMMAND_SRC))\
					$(addprefix $(UTIL_DIR), $(UTIL_SRC))\


####################				 END	  		     ####################
#############################################################################

SRCS			=	$(addprefix $(SRCS_DIR), $(SRC))

OBJS			=	$(SRCS:%.cpp=$(OBJS_DIR)/%.o)

all		:	$(NAME)

$(NAME) :	$(OBJS)
			@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
			@echo "${GREEN}ircserv has been compiled!${DEF_COLOR}"

$(OBJS_DIR)/%.o	: 	%.cpp
			@mkdir -p $(@D)
			@$(CXX) $(CXXFLAGS) -c $^ $(HEADERS) -o $@
			@echo "${YELLOW}Compiling $<${DEF_COLOR}"

debug	:	$(OBJS)
			@$(CXX) $(DEBUG_FLAGS) -o $(NAME) $(OBJS)
			@echo "${GREEN}ircserv has been compiled!${DEF_COLOR}"

clean	:
			@rm -rf $(OBJS_DIR)
			@echo "$(WHITE)Object files have been removed successfully.$(DEF_COLOR)"


fclean	:	
			@make clean
			@rm -f $(NAME)
			@echo "${RED}> Cleaning of the ircserv has been done.❌${DEF_COLOR}"

re	:		
			@make fclean
			@make all
			@echo "$(MAGENTA)Cleaned and rebuilt everything for ircserv!$(DEF_COLOR)"

#color
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

.PHONY	:	all clean fclean re
