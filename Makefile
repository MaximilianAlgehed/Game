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

$(BUILD)/%.o: $(SRC)/%.cpp $(INC)/%.h
	g++ -I $(INC) $(FLAGS) $< -o $@

$(INC)/main.h:

clean:
	-rm application $(OBJECTS)
