XX = g++
CXXFLAGS = -std=c++0x
OBJS = Dice.o Main.o
SRCS = Dice.cpp Main.cpp
HEADERS = Dice.hpp

dice: ${SRCS} ${HEADERS}
		${CXX} ${CXXFLAGS} ${SRCS} -o dice

clean:
		rm -f *.o dice
