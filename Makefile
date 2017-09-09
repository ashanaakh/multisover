CXX=clang++ -std=c++14
SOURCES=src/*.cpp
OBJECTS=build/*.o
EXECUTABLE=build/solver

all: $(EXECUTABLE)

$(EXECUTABLE): moveobj
	$(CXX) -o $(EXECUTABLE) $(OBJECTS)

$(OBJECTS): clean
	$(CXX) -c $(SOURCES)

moveobj:$(OBJECTS)
	mv *.o build

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
