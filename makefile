HEAD_DIR = Headers
IMPL_DIR = Implementations
OBJ_DIR = Objects

EXEC = programa
SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS = main.cpp $(IMPL_DIR)/heroi.cpp $(IMPL_DIR)/Enemy.cpp $(IMPL_DIR)/projectile.cpp $(IMPL_DIR)/Base.cpp $(IMPL_DIR)/Bar.cpp $(IMPL_DIR)/Menu.cpp
OBJS = $(SRCS:$(IMPL_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJS)
	g++ -o $(EXEC) $(OBJS) $(SFML)

$(OBJ_DIR)/%.o: $(IMPL_DIR)/%.cpp
	g++ -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)

.PHONY: all clean