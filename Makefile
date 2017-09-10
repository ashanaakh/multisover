CXX=clang++ -std=c++11 -Iinclude
SOURCES=src/*.cpp
OBJECTS=build/*.o
EXECUTABLE=build/solver

all: $(EXECUTABLE)

$(EXECUTABLE): compile moveobj
	$(CXX) -o $(EXECUTABLE) $(OBJECTS)

moveobj:
	mv *.o build

compile: clean
	$(CXX) -c $(SOURCES)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

