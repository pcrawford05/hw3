CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: llrec-test

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------
llrec-test: llrec.h llrec.cpp llrec-test.cpp
	${CXX} ${CXXFLAGS} llrec.cpp llrec-test.cpp -o llrec-test

stack_test: stack_test.cpp stack.h
	${CXX} ${CXXFLAGS}	$< -o $@

heap_test: heap_test.cpp heap.h
	${CXX} ${CXXFLAGS}	$< -o $@
clean:
	rm -f *.o rh llrec-test *~

.PHONY: clean 