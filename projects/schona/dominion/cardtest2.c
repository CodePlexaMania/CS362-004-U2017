/*
	Andy Schon
	CS362
	cardtest2.c
	- Testing SmityEffect
		Tests
			- P1 should get 3 cards
			- Smithy card discarded
			- SmityEffect returns 0
			- P2 completely unaffected
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

// function to check array of player 2 consistency tests
void Player2Comparisons(struct gameState *preState, struct gameState *postState)
{
	//make sure no functions affected p2;
	//check p2 hand
	AssertTrue(memcmp(preState->hand[1], postState->hand[1], MAX_HAND * sizeof(int)) == 0,  "player 2 hand remains same from start");
	//check p2 hand count
	AssertTrue(preState->handCount[1] == postState->handCount[1],  "player 2 hand count remains same from start");
	//check discard
	AssertTrue(memcmp(preState->discard[1], postState->discard[1], MAX_HAND * sizeof(int)) == 0,  "player 2 discard remains same from start");
	//check discard count
	AssertTrue(preState->discardCount[1] == postState->discardCount[1],  "player 2 discard count remains same from start");
	//check p2 deck
	AssertTrue(memcmp(preState->deck[1], postState->deck[1], MAX_HAND * sizeof(int)) == 0,  "player 2 deck remains same from start");
	//check deck count
	AssertTrue(preState->deckCount[1] == postState->deckCount[1],  "player 2 deck count remains same from start");
}

int isSmithyCardPresent(struct gameState *state)
{
	int i;
	for(i = 0; i < state->handCount[0]; i++)	
	{
		if(state->hand[0][i] == smithy) return 1;
	}
	return 0;
}

int main (int argc, char** argv)
{
	printf("\n----------------------------------------\n");
	printf("cardtest2: Test SmityEffect function");
	printf("\n----------------------------------------\n");

	//create 
	struct gameState preState, postState;

	//init
	memset(&preState,0,sizeof(struct gameState));

	//cards for game
	int k[10] = {adventurer, gardens, embargo, village, minion, 
				 mine, cutpurse, sea_hag, tribute, smithy};

	//"fill" state with intial supplyCount(s)
	initializeGame(2, k, 765, &preState);
		
	//put smithy in hand
	preState.hand[0][2] = smithy;
	
	memcpy(&postState, &preState, sizeof(struct gameState));
	
	//check SmityEffect returns 0
	AssertTrue(SmithyEffect(0, 2, &postState) == 0, "SmithyEffect returns 0");
	
	//check card count now +3
	AssertTrue((preState.handCount[0] == postState.handCount[0]+3) == 0, "P1 card count increased by 3");
	
	//check smithy card is now gone from hand
	AssertTrue(isSmithyCardPresent(&postState) == 0, "Smithy card removed");
	
	//check is player 2 unchanged
	Player2Comparisons(&preState, &postState);
	
	return 0;
}