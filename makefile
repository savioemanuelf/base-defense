CXX = g++
CXXFLAGS = -std=c++11
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = meuJogo

SRCS = main.cpp heroi.cpp projectile.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)