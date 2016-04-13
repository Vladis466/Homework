CFLAGS = -Wall -fpic -coverage -lm

all: testdominion rngs.o dominion.o playdom unittestresults randall badTestDrawCard testBuyCard testDrawCard player 

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testdominion: dominion.o testdominion.c
	gcc -o testdominion testdominion.c -g dominion.o rngs.o $(CFLAGS)
	
	
 unittest1: unittest1.c dominion.o
	 gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

 unittest2: unittest2.c dominion.o
	 gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

 unittest3: unittest3.c dominion.o 
	 gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

 unittest4: unittest4.c dominion.o 
	 gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

randadv: randomtestadventurer.c dominion.o
	gcc -o randadv randomtestadventurer.c -g  dominion.o rngs.o $(CFLAGS)
	
randcard: randomtestcard.c dominion.o
	gcc -o randcard randomtestcard.c -g  dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
randall: randcard randadv
	./randadv >>  randomtestadventurer.out
	./randcard >> randomtestcard.out
	gcov -bf randomtestcard.c >> randomtestcard.out
	gcov -bf randomtestadventurer.c >> randomtestadventurer.out

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 >>  unittestresults.out
	./unittest2 >>  unittestresults.out
	./unittest3 >>  unittestresults.out
	./unittest4 >>  unittestresults.out
	./cardtest1 >>  unittestresults.out
	./cardtest2 >>  unittestresults.out
	./cardtest3 >>  unittestresults.out
	./cardtest4 >>  unittestresults.out
	gcov -bf unittest1 >> unittestresults.out
	gcov -bf unittest2 >> unittestresults.out
	gcov -bf unittest3 >> unittestresults.out
	gcov -bf unittest4 >> unittestresults.out
	gcov -bf cardtest1 >> unittestresults.out
	gcov -bf cardtest2 >> unittestresults.out
	gcov -bf cardtest3 >> unittestresults.out
	gcov -bf cardtest4 >> unittestresults.out

clean:
	rm -f *.o gameResults.out testdominion randomtestcard.out randomtestadventurer.out unittestresults.out randomtestcard randcard randadv badTestDrawCard testDrawCard unittest4 playdom.exe playdom unittest1.exe unittest1 unittest2.exe unittest2 unittest3.exe unittest3 unittest4.exe cardtest1.exe cardtest1 cardtest2.exe cardtest2 cardtest3.exe cardtest3 cardtest4.exe cardtest4 test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
