/*
	Andy Schon
	CS362
	cardtest1.c
	- Testing AdventurerEffect
		Tests
			- P1 Hand Count increased by 2
			- Amount of Treasure cards in hand increased by 2
			- Top 2 cards in hand are Treasure cards
			- Adventurer card remains in P1 hand
			- P2 unchanged after AdventurerEffect called
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

//evaluates if Adventurer card is still in hand
int isAdventurerCardPresentInHand(struct gameState *state)
{
	int h;
	for(h = 0; h < state->handCount[0]; h++)
	{
		if(state->hand[0][h] == adventurer)
			return 1;
	}
	
	return 0;
}

//evailuates if card is treasure type or not
int isTreasureCard(int card)
{
	if(card == copper || card == silver || card == gold)
		return 1;
	else
		return 0;
}

//identifies how many treasure cards are in player 1's hand
int NumTreasureCardsInHand(struct gameState *state)
{
	int treasureCards = 0;
	int i;
	for(i = 0; i < state->handCount[0]; i++)
	{
		if(((state->hand[0][i]) == copper) || 
		   ((state->hand[0][i]) == silver) || 
		   ((state->hand[0][i]) == gold))
		   {
			   treasureCards++;
		   }
	}
	return treasureCards;	
}

int NoDiscardedCardsAreTreasure(struct gameState *state)
{
	int i;
	for(i = 0; i < state->discardCount[0]; i++)
	{
		int card = state->discard[0][i];
		if(card == copper || card == silver || card == gold){ return 0;	}
	}
	return 1;
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

int main (int argc, char** argv)
{
	printf("\n----------------------------------------\n");
	printf("cardtest1: Test AdventurerEffect function");
	printf("\n----------------------------------------\n");

	//create 
	struct gameState preState, postState;

	//init
	memset(&preState,0,sizeof(struct gameState));

	//cards for game
	int k[10] = {adventurer, gardens, embargo, village, minion, 
				 mine, cutpurse, sea_hag, tribute, smithy};

	//"fill" state with intial supplyCount(s)
	initializeGame(2, k, 7645, &preState);
	
	//add adventurer card
	preState.hand[0][2] = adventurer;
		
	//set eql
	memcpy (&postState, &preState, sizeof(struct gameState));
		
	//check basic return value of AdventurerEffect
	AssertTrue(actionAdventurer(&postState, 2) == 0, "AdventurerEffect returns 0");
	
	//check to make sure our hand now has 2 more cards
	AssertTrue(preState.handCount[0] + 2 == postState.handCount[0], "2 cards added correctly");	
	
	AssertTrue(NoDiscardedCardsAreTreasure(&postState) == 1, "No card in Discard are treasure.");
	
	//check player 2 altered or not
	Player2Comparisons(&preState, &postState);
	
	return 0;
}