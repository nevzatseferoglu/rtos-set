.PHONY : ctest test clean all

CC=clang++
CFLAGS= -c -Wall -Wextra
OBJECTS = main.o

#-----
PROG_EXECUTABLE=prog

all: program run clean-objects

program: $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(PROG_EXECUTABLE)

run: $(PROG_EXECUTABLE) 
	@./$(PROG_EXECUTABLE)

%.o: %.cpp
	@$(CC) $(CFLAGS) $<

#-----
TESTDIR=test/

test: testenv run-test clean-objects

testenv: driver.o
	@$(CC) driver.o -o dout

driver.o: $(TESTDIR)driver.cpp
	@$(CC) $(CFLAGS) $(TESTDIR)driver.cpp

ctest: test clean

run-test: dout
	@./dout

#-----
IGNORE_ERROR=2>/dev/null || true

clean: clean-objects clean-test-output

clean-objects:
	-@rm -rf *.o $(IGNORE_ERROR)

clean-test-output:
	-@rm -rf dout $(IGNORE_ERROR)