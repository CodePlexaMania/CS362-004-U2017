/*
	Andy Schon
	CS362
	cardtest3.c
	- Testing MineEffect
		Tests
			- Ensure choice1 selected is a treasure card
			- Encsure valid card selected for choice1
			- Only trash Treasure card
			- Cost of new card must be 3 or less in value than the one being trashed 
			- MineEffect returns 0
			- Card discarded is Mine card
			- P2 unchanged after MineEffect called
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

int isMineCardPresent(struct gameState *state)
{
	int i;
	for(i = 0; i < state->handCount[0]; i++)	
	{
		if(state->hand[0][i] == mine) return 1;
	}
	return 0;
}

int main (int argc, char** argv)
{
	printf("\n----------------------------------------\n");
	printf("cardtest3: Test MineEffect function");
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
	
	//set eql
	memcpy (&postState, &preState, sizeof(struct gameState));
	
	//place sngle mine card in hand
	postState.hand[0][0] = curse;
	postState.hand[0][1] = treasure_map;
	postState.hand[0][2] = mine;
	postState.hand[0][3] = embargo;	
	
	//check for correct card chosen
	AssertTrue(MineEffect(0, 0, embargo, 2, &postState) == -1, "Not treasure card - Less than copper");
	AssertTrue(MineEffect(0, 1, embargo, 2, &postState) == -1, "Not treasure card - More than gold");
	
	//set above and below enum thresholds
	postState.hand[0][0] = curse-1;
	postState.hand[0][1] = treasure_map+1;
	AssertTrue(MineEffect(0, 0, 1, 2, &postState) == -1, "Invalid card - Less than curse");
	AssertTrue(MineEffect(0, 1, 3, 2, &postState) == -1, "Invalid card - more than treasure_map");
	
	//set back
	postState.hand[0][0] = copper;
	postState.hand[0][1] = treasure_map;
	
	//check cost choice1 + 3 is not > cost of choice2
	AssertTrue(MineEffect(0, 0, embargo, 2, &postState) == -1, "Cost of choice1 plus 3 is greater than cost of choice2");
	postState.hand[0][0] = copper;
	
	//MineEffect returns zero (treasure card selected)
	AssertTrue(MineEffect(0, 0, treasure_map, 2, &postState) == 0, "MineEffect returns 0");
	AssertTrue(isMineCardPresent(&postState) == 0, "Mine Card Removed");
	AssertTrue(postState.hand[0][0] != copper, "Correct card trashed");
	
	//check is player 2 unchanged
	Player2Comparisons(&preState, &postState);
	
	return 0;
}