CXX          := clang++ -std=c++11

CXXFLAGS     := -Iinclude

LDFLAGS      := -lncurses -lpthread

SRCS         := src/*.cpp

RM           := -@rm -rf

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
	$(CXX) $(CXXFLAGS) -c src/solver.cpp $(TESTS_DIR)/test$(1).cpp
	@mv *.o tests_build
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test$(1) tests_build/test$(1).o tests_build/solver.o
endef

define test
	$(call build_test,$(1))
	@./test$(1) && echo "\033[0;32m---> Passed <---\033[0m" || echo "\033[0;32mXXX Failed XXX\033[0m"
endef

all: $(EXECUTABLE)

$(EXECUTABLE): compile replace
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/$(EXECUTABLE) $(OBJECTS)

replace:
	@mv *.o build

compile: clean
	$(CXX) $(CXXFLAGS) -c $(SRCS) src/main.cpp

clean:
	$(RM) $(OBJECTS) $(BUILD_DIR)/$(EXECUTABLE)

cleantest: clean
	$(RM) test[1-6]

$(NAME_TEST1): cleantest
	$(call test,1)

$(NAME_TEST2): cleantest
	$(call test,2)

$(NAME_TEST3): cleantest
	$(call test,3)

$(NAME_TEST4): cleantest
	$(call test,4)

# $(NAME_TEST5): cleantest
	# $(call test,5)

# $(NAME_TEST6): cleantest
	# $(call test,6)

# test: $(NAME_TEST1) $(NAME_TEST2) $(NAME_TEST3) $(NAME_TEST4) $(NAME_TEST5) $(NAME_TEST6)
test: $(NAME_TEST1) $(NAME_TEST2) $(NAME_TEST3) $(NAME_TEST4)
