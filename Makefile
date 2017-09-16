CXX          := clang++

CPPVER       := -std=c++11

FLAGS        := -Iinclude

SOURCES      := src/*.cpp

BUILD_DIR    := build

OBJECTS      := $(BUILD_DIR)/*.o

TESTS_DIR    := tests

EXECUTABLE 	 := solver

NAME_TEST1   := test1

NAME_TEST2   := test2

NAME_TEST3   := test3

NAME_TEST4   := test4

NAME_TEST5   := test5

NAME_TEST6   := test6

define build_test
	$(CXX) $(CPPVER) $(FLAGS) -c src/solver.cpp $(TESTS_DIR)/test$(1).cpp
	@mv *.o tests_build
	$(CXX) $(CPPVER) $(FLAGS) -o test$(1) tests_build/test$(1).o tests_build/solver.o
endef

define test
	$(call build_test,$(1))
	@./test$(1) && echo "Passed" || echo "Failed"
endef

all: $(EXECUTABLE)

$(EXECUTABLE): compile moveobj
	$(CXX) $(CPPVER) $(FLAGS) -o $(BUILD_DIR)/$(EXECUTABLE) $(OBJECTS)

moveobj:
	@mv *.o build

compile: clean
	$(CXX) $(CPPVER) $(FLAGS) -c $(SOURCES) src/main.cpp

clean:
	-@rm -rf $(OBJECTS) $(BUILD_DIR)/$(EXECUTABLE)

cleantest: clean
	-@rm test[1-6]

$(NAME_TEST1): cleantest
	$(call test,1)

$(NAME_TEST2): cleantest
	$(call test,2)

$(NAME_TEST3): cleantest
	$(call test,3)

$(NAME_TEST4): cleantest
	$(call test,4)

$(NAME_TEST5): cleantest
	$(call test,5)

$(NAME_TEST6): cleantest
	$(call test,6)
