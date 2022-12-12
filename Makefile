.PHONY : test ctest clean all

CC=clang++
CFLAGS=  -c -Wall -Wextra -std=c++2a -pthread 

#-----
TESTDIR=test/

ctest: testenv run-test clean-objects

testenv: driver.o
	@$(CC) driver.o -o dout

driver.o: $(TESTDIR)driver.cpp
	@$(CC) $(CFLAGS) $(TESTDIR)driver.cpp
 
test: ctest clean

run-test: dout
	@./dout

#-----
IGNORE_ERROR=2>/dev/null || true

clean: clean-objects clean-test-output

clean-objects:
	-@rm -rf *.o $(IGNORE_ERROR)

clean-test-output:
	-@rm -rf dout $(IGNORE_ERROR)
