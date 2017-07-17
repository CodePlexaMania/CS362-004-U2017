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
	
	//set 
	int x;
	for(x = 0; x < MAX_HAND; x++)
	{
		preState.hand[0][x] = 5;
		preState.deck[0][x] = 5;
		preState.discard[0][x] = 5;
	}
	
	//add adventurer card
	preState.hand[0][2] = adventurer;
	
	//set counts as decribed above
	preState.handCount[0] = 5;
	preState.deckCount[0] = 5;
	preState.discardCount[0] = 5;
	
	//set eql
	memcpy (&postState, &preState, sizeof(struct gameState));

	//check basic return value of AdventurerEffect
	AssertTrue(AdventurerEffect(0, &postState) == 0, "AdventurerEffect returns 0");
	
	//check to make sure our hand now has 2 more cards
	AssertTrue(preState.handCount[0] + 2 == postState.handCount[0], "2 cards added correctly");
	
	//check to ensure both added cards are treasure cards
	AssertTrue((NumTreasureCardsInHand(&preState) + 2 == NumTreasureCardsInHand(&postState)), "2 cards added are treasure cards");
	
	//check to make sure the top two cards added are the treasure cards
	AssertTrue(isTreasureCard(postState.hand[0][postState.handCount[0]-1]) == 1 && 
	           isTreasureCard(postState.hand[0][postState.handCount[0]-2]) == 1, 
			   "Top 2 cards are Treasure cards");
	
	//check to ensure adventurer card has not left hand
	AssertTrue(isAdventurerCardPresentInHand(&postState) == 1, "Adventurer card stil in P1 hand");
	
	//check player 2 altered or not
	Player2Comparisons(&preState, &postState);
	
	return 0;
}