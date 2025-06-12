NAME = humangl
CPP = c++ -std=c++11 -fsanitize=address -g3
# CPP = c++ -std=c++11
INCS_ROOT = inc
INCS_READLINE = /usr/local/opt/readline/include
BUILDDIR=build/
SRCS = ${wildcard src/*.cpp}
OBJS= ${SRCS:.cpp=.o}
OBJS_TARGET=${addprefix ${BUILDDIR},${subst /,_,${OBJS}}}
UNAME := $(shell uname)

# Install gl headers and glfw on ubuntu using package manager. GLM can be linked with default libm.
ifeq ($(UNAME), Linux)
	CPP_FLAGS = lib/glad/libglad-linux.a -lglfw -lm
	CPP_INCS= -I${INCS_ROOT} -Ilib/glad/include -Ilib/glm -Ilib/glfw
else ifeq ($(UNAME), Darwin)
	CPP_FLAGS = lib/glad/libglad-mac.a lib/glfw/libglfw3.a -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo 
	CPP_INCS= -I${INCS_ROOT} -Ilib/glad/include -Ilib/glm -Ilib/glfw
endif

# Style constants
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
NC=\033[0m # No Color

all : ${NAME}
	@echo "${GREEN}✔️  Done building..${NC}"

bonus : ${NAME}

${NAME}: ${OBJS_TARGET}
	@echo "${GREEN}😏  Linking..${NC}"
	@${CPP} ${BUILDDIR}*.o ${CPP_FLAGS} -o ${NAME}

build/%.o : ${OBJS}
	@echo "${GREEN}📇  Compile finish..${NC}"

.cpp.o :
	@echo "${GREEN}📇  Compiling $<..${NC}"
	@${CPP} -c ${CPP_INCS} $< -o ${BUILDDIR}${subst /,_,$@}

clean : 
	@echo "${YELLOW}🗑️  Removing Objects..${NC}"
	@rm -rf ${BUILDDIR}*.o

fclean : clean
	@echo "${YELLOW}🗑️  Removing ${NAME}..${NC}"
	@rm -rf ${NAME}

re : fclean all

.PHONY : re clean fclean all