SRC = src
INC = inc
BUILD = build
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SOURCES = $(shell echo $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SOURCES))

all : $(OBJECTS)
	g++ $(OBJECTS) -o application $(LIBS)

$(BUILD)/%.o: $(SRC)/%.cpp
	g++ -I $(INC) -c $< -o $@

clean:
	-rm application $(OBJECTS)
