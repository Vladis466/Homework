#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>




//This function will test the getCost() function to make sure all values are in the range limits.
int main(){
	int i = 0;
	int x = 0;
	int cardss [27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, 
			feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward,
			tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
			
	const char *names[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", 
			"feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
			"tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

	for (i = 0; i < 27; i++)     	//27 cards
	{		
		if (getCost(cardss[i]) > 8)
		printf("card %s in the list has a cost greater than 8, breaking standard dominion rules", names[i]);
		x++;
	}
	
	if(x > 0){ printf("Test was a success, no card failed");}
	

	return (0);
	
}

