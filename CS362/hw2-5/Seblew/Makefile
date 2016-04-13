CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o -w $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o -w $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o -w $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o -w $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o -w $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

unittest1: clean all unittest1.c
	gcc unittest1.c -o unittest1 -g  dominion.o rngs.o $(CFLAGS)

unittest2: clean all unittest1.c
	gcc unittest2.c -o unittest2 -g  dominion.o rngs.o $(CFLAGS)

unittest3: clean all unittest1.c
	gcc unittest3.c -o unittest3 -g  dominion.o rngs.o $(CFLAGS)

unittest4: clean all unittest1.c
	gcc unittest4.c -o unittest4 -g  dominion.o rngs.o $(CFLAGS)

cardtest1: clean all cardtest1.c
	gcc cardtest1.c -o cardtest1 -g  dominion.o rngs.o $(CFLAGS)

cardtest2: clean all cardtest2.c
	gcc cardtest2.c -o cardtest2 -g  dominion.o rngs.o $(CFLAGS)

cardtest3: clean all cardtest3.c
	gcc cardtest3.c -o cardtest3 -g  dominion.o rngs.o $(CFLAGS)

cardtest4: clean all cardtest4.c
	gcc cardtest4.c -o cardtest4 -g  dominion.o rngs.o $(CFLAGS)

testcov: clean all unittest1
	gcov dominion.c
	unittest1
	echo "Unit Test 1" > unittestresults.out
	gcov dominion.c | grep Lines >> unittestresults.out
	make unittest2
	echo "Unit Test 2" >> unittestresults.out
	unittest2
	gcov dominion.c | grep Lines >> unittestresults.out
	make unittest3
	echo "Unit Test 3" >> unittestresults.out
	unittest3
	gcov dominion.c | grep Lines >> unittestresults.out
	make unittest4
	echo "Unit Test 4" >> unittestresults.out
	unittest4
	gcov dominion.c | grep Lines >> unittestresults.out
	make cardtest1
	echo "Card Test 1" >> unittestresults.out
	cardtest1
	gcov dominion.c | grep Lines >> unittestresults.out
	make cardtest2
	echo "Card Test 2" >> unittestresults.out
	cardtest2
	gcov dominion.c | grep Lines >> unittestresults.out
	make cardtest3
	echo "Card Test 3" >> unittestresults.out
	cardtest3
	gcov dominion.c | grep Lines >> unittestresults.out
	make cardtest4
	echo "Card Test 4" >> unittestresults.out
	cardtest4
	gcov dominion.c | grep Lines >> unittestresults.out

randomtestcard: clean all randomtestcard.c
	gcc randomtestcard.c -o randomtestcard -g dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer: clean all randomtestadventurer.c
	gcc randomtestadventurer.c -o randomtestadventurer -g dominion.o rngs.o $(CFLAGS)
	
randcov: clean all 
	gcov dominion.c
	randomtestcard
	echo "Card Test" > randomtestcard.out
	gcov dominion.c | grep Lines >> randomtestcard.out
	make randomtestadventurer
	echo "Adventurer Test" > randomtestadventurer.out
	gcov dominion.c | grep Lines >> randomtestadventurer.out
	
	
clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
