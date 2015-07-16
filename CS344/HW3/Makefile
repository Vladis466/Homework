CC = icc
CXX = icpc
CFLAGS = -Wall -std=c99 -openmp -O3 -g -I.
CXXFLAGS = -Wall -openmp -O3 -g
#overkill on the flags, but that doesn't hurt anything
LDFLAGS = -lrt -lpthread 
#replace this if you want to change the output name
TARGET = signal

#any headers go here
INCLUDES = 

#any .c or .cpp files go here
SOURCE = sigSample.c



	

#default is to compile
default: compile


fork: Forksample.c Forksample
#	$(CC) -o fork -g Forksample.c $(CFLAGS)

shell: Shell.c Shell
	$(CC) $(CFLAGS) Shell.c -o myShell $(LDFLAGS)
	
	
#depends on all of you source and header files
compile: ${SOURCE} ${INCLUDES}
#this assumes you actually are linking all of the source files together
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS}

debug: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS} -DDEBUG
	
	
clean:
	rm -f *.o Forksample signal