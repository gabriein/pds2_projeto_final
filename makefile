CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 `pkg-config --cflags allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5`
LDFLAGS = `pkg-config --libs allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5`

SRC = projeto.cpp fundo.cpp tubo.cpp jogador.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = flappy

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
