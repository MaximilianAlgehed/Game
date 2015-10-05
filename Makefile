SRC = src
INC = inc
BUILD = build
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS = -c -std=c++11
HEADERS = $(shell echo $(INC)/*.h)
SOURCES = $(shell echo $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SOURCES))

all : $(OBJECTS) $(HEADERS)
	g++ $(OBJECTS) -o application $(LIBS)

$(BUILD)/%.o: $(SRC)/%.cpp
	g++ -I $(INC) $(FLAGS) $< -o $@

clean:
	-rm application $(OBJECTS)
