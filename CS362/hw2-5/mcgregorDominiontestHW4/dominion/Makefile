CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS) -ftest-coverage -fprofile-arcs

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

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

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
all: playdom player testDrawCard testBuyCard badTestDrawCard

unitTests: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs
	./unittest1
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

randomTestCard: randomtestcard.c randomtestadventurer.c dominion.c rngs.o
	gcc -o randomtestcard randomtestcard.c dominion.c rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs
	./randomtestcard
	gcov dominion.c >> randomtestcard.out
	gcc -o randomtestadventurer randomtestadventurer.c dominion.c rngs.o $(CFLAGS) -ftest-coverage -fprofile-arcs
	./randomtestadventurer
	gcov dominion.c >> randomtestadventurer.out

testDominion: testdominion.c dominion.c rngs.o
	gcc -o testdominion testdominion.c dominion.c rngs.o $(CFLAGS)
	./testdominion > testdominion.out

testDominionRerun: testdominionrerun.c dominion.c rngs.o
	gcc -o testdominionrerun testdominionrerun.c dominion.c rngs.o $(CFLAGS)
	./testdominionrerun > testdominionrerun.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
