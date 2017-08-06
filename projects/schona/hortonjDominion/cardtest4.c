/*
	Andy Schon
	CS362
	cardtest4.c
	- Testing actionVillage
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

int isVillageCardPresent(struct gameState *state)
{
	int i;
	for(i = 0; i < state->handCount[0]; i++)	
	{
		if(state->hand[0][i] == village) return 1;
	}
	return 0;
}
int main (int argc, char** argv)
{
	printf("\n----------------------------------------\n");
	printf("cardtest4: Test actionVillage function");
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
	
	postState.hand[0][2] = village;
	
	//check actionVillage returns 0
	AssertTrue(actionVillage(&postState, 2) == 0, "actionVillage returns 0");
	
	//check hand count same number of cards
	AssertTrue(preState.handCount[0] == postState.handCount[0], "Hand count incremented by one");
	
	//check if number of actions has increased by 2
	AssertTrue(preState.numActions + 2 == postState.numActions, "Number of actions has increased by two");

	//check if played card count increases by 1
	AssertTrue(preState.playedCardCount + 1 == postState.playedCardCount, "Discard count increased by one");
	
	//check if village card is removed from hand
	AssertTrue(isVillageCardPresent(&postState) == 0, "Village card discarded");
	
	//check if player 2 unchanged
	Player2Comparisons(&preState, &postState);	
	
	return 0;
}