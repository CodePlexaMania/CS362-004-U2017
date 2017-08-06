/*
	Andy Schon
	CS362
	unittest3.c
	- Testing whoseTurn function
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
	printf("unittest3: Test whoseTurn function");
	printf("\n----------------------------------------\n");
	
	//create 
	struct gameState state;

	//init
	memset(&state,0,sizeof(struct gameState));

	//cards for game
	int k[10] = {adventurer, gardens, embargo, village, minion, 
				 mine, cutpurse, sea_hag, tribute, smithy};

	//"fill" state
	initializeGame(2, k, 46, &state);
	
	//After start of game, player 1 goes first
	AssertTrue(whoseTurn(&state) == 0, "Player 1's turn");

	//end palyer's turn to check for next player's turn
	endTurn(&state);
	
	//check if Player 2 is now the currect turn
	AssertTrue(whoseTurn(&state) == 1, "Player 2's turn");
	
	//end Player 2's turn
	endTurn(&state);
	
	//Evaluate if ending Player 2's turn has returned back to Player 1's turn
	AssertTrue(whoseTurn(&state) == 0, "Player 1's turn again");
	
	return 0;
}