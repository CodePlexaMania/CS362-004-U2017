/*
	Andy Schon
	CS362
	unittest3.c
	- Testing drawCard function
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

void Player1EmptyDeckChecks(struct gameState *preState, struct gameState *postState)
{
//check played card count	
	AssertTrue(postState->playedCardCount == 0, "did not affect number of played cards");

	//check that drawCard added to p1 hand and only one card
	AssertTrue(postState->hand[0][preState->handCount[0]] == preState->deck[0][preState->deckCount[0] - 1] , "added card to correct player's hand");	
	AssertTrue(postState->handCount[0] == preState->handCount[0] + 1, "only added one card to player 1's hand");
	
	//check p1 deck
	AssertTrue(memcmp(preState->deck[0], postState->deck[0], preState->deckCount[0] * sizeof(int)) == 0,  "cards not drawn still in player 1 deck");
	AssertTrue(preState->deckCount[0] == postState->deckCount[0] + 1,  "player 1 deck count decremented by one");
	
	//check p1 discard 
	AssertTrue(memcmp(preState->discard[0], postState->discard[0], MAX_HAND * sizeof(int)) == 0,  "player 1 discard remains unchanged");
	AssertTrue(preState->discardCount[0] == postState->discardCount[0],  "player 1 discard count remains unchanged");
}

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
	printf("unittest4: Test drawCard function");
	printf("\n----------------------------------------\n");
	
	//create 
	struct gameState preState, postState;

	//init
	memset(&preState,0,sizeof(struct gameState));

	//cards for game
	int k[10] = {adventurer, gardens, embargo, village, minion, 
				 mine, cutpurse, sea_hag, tribute, smithy};

	//"fill" state
	initializeGame(2, k, 123, &preState);
	
	//copy/duplicate state for testing
	memcpy (&postState, &preState, sizeof(struct gameState));
	
	printf("Test qith NO cards in player deck:\n");

	AssertTrue(drawCard(0, &postState) == 0, "returns 0");

	//Check fallout from drawCard
	Player1EmptyDeckChecks(&preState, &postState);
		
	//player 2 gameState check
	Player2Comparisons(&preState, &postState);
	
	//fill up hand
	int i = -1;
	while(++i < MAX_HAND && postState.deckCount[0] != 0){ drawCard(0, &postState); }
	
	//continue test only if fill hand worked
	if(!(i >= MAX_HAND))
	{		
		printf("Test with cards in player deck:\n");
	
		//Player 1 get 2 cards
		gainCard(gold, &postState, 0, 0);
		gainCard(silver, &postState, 0, 0);
		
		//set equal states
		memcpy (&preState, &postState, sizeof(struct gameState));
		
		AssertTrue(drawCard(0, &postState) == 0, "returns 0");

		//check played card state	
		AssertTrue(memcmp(preState.playedCards, postState.playedCards, MAX_HAND * sizeof(int)) == 0,  "played cards are unchanged");
		AssertTrue(preState.playedCardCount == postState.playedCardCount,  "played card count is unchanged");

		//player 1 state check
		//check the state of the hand
		AssertTrue((postState.hand[0][preState.handCount[0]] == silver || postState.hand[0][preState.handCount[0]] == gold) && postState.hand[0][preState.handCount[0]] != postState.deck[0][0] , "Correct card added to player 1's hand");	
		AssertTrue(postState.handCount[0] == preState.handCount[0] + 1, "only one card added to player 1");

		//check state of deck
		AssertTrue(postState.deck[0][preState.deckCount[0]] == silver || postState.deck[0][preState.deckCount[0]] == gold,  "player 1 discard cards now in deck");
		AssertTrue(1 == postState.deckCount[0],  "player 1's deck count is now one");

		//check state of discard 
		AssertTrue(0 == postState.discardCount[0],  "player 1's discard count is now zero");

		//player 2 gameState check
		Player2Comparisons(&preState, &postState);
	}
	
	return 0;
}