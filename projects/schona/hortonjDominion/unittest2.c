/*
	Andy Schon
	CS362
	unittest2.c
	- Testing supplyCount function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <stdio.h>
#include <string.h>

//Print pseudo bool result with test name
void AssertTrue(int result, char* test)
{
	if(result == 1)
		printf("PASSED: %s.\n", test);
	else
		printf("FAILED: %s.\n", test);
}

int main (int argc, char** argv)
{
	printf("\n----------------------------------------\n");
	printf("unittest2: Test supplyCount function");
	printf("\n----------------------------------------\n");
	
	//create 
	struct gameState state;

	//init
	memset(&state,0,sizeof(struct gameState));

	//cards for game
	int k[10] = {adventurer, gardens, embargo, village, minion, 
				 mine, cutpurse, sea_hag, tribute, smithy};

	//"fill" state with intial supplyCount(s)
	initializeGame(2, k, 7, &state);
		
	//evaluate if supplyCount returns correct supply for each supplied card;
	// constraints - for 2 players
	//curse = 10
	//estate = 8
	//duchy = 8
	//province = 8
	//copper = (60 - 14) = 46
	//silver = 40
	//gold = 30
	AssertTrue(supplyCount(curse, &state) == 10, "supplyCount for curse = 10");
	AssertTrue(supplyCount(estate, &state) == 8, "supplyCount for estate = 8");
	AssertTrue(supplyCount(duchy, &state) == 8, "supplyCount for duchy = 8");
	AssertTrue(supplyCount(province, &state) == 8, "supplyCount for province = 8");
	AssertTrue(supplyCount(copper, &state) == 46, "supplyCount for copper = 46");
	AssertTrue(supplyCount(silver, &state) == 40, "supplyCount for silver = 40");
	AssertTrue(supplyCount(gold, &state) == 30, "supplyCount for gold = 30");
	
	return 0;
}