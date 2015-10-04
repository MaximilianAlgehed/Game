SRC = src
INC = inc
BUILD = build
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SOURCES = $(shell echo $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SOURCES))

all : $(OBJECTS)
	g++ $(OBJECTS) -o application $(LIBS)

$(OBJECTS) : $(SOURCES)
	g++ -c $(SOURCES) -I $(INC)
	mv *.o $(BUILD)

clean:
	-rm application $(OBJECTS)
