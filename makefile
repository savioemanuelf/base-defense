HEAD_DIR = Headers
IMPL_DIR = Implementations
OBJ_DIR = Objects

EXEC = programa
SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS = -Wall -fsanitize=address

SRCS = main.cpp $(IMPL_DIR)/AssetsManager.cpp $(IMPL_DIR)/StateManager.cpp $(IMPL_DIR)/Menu.cpp $(IMPL_DIR)/Settings.cpp $(IMPL_DIR)/Game.cpp $(IMPL_DIR)/Hero.cpp $(IMPL_DIR)/Projectile.cpp $(IMPL_DIR)/Enemy.cpp $(IMPL_DIR)/Base.cpp $(IMPL_DIR)/Pause.cpp
OBJS = $(SRCS:$(IMPL_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJS)
	g++ -o $(EXEC) $(OBJS) $(SFML) $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(IMPL_DIR)/%.cpp
	g++ -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)

.PHONY: all clean