/*
	Andy Schon
	CS362
	Assignment 4
	randomtestcard1.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "rngs.h"
#include <math.h>

int iteration = 1;

//Print pseudo bool result with test name
void AssertTrue(int result, char* test)
{
	if(result == 1)
		printf("PASSED: %s.\n", test);
	else 
		printf("FAILED: %s.\n", test);
}

void RunVillageEffect(int player, int handPos, struct gameState *post)
{
	printf("Iteration #%d:\n", iteration++);
	
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int effect = VillageEffect(player, handPos, post);

	//Test 1: Check VillageEffect returns 0
	AssertTrue(effect == 0, "VillageEffect(): return 0");
	
	//Test 2: Check that player has gained 0 cards
	AssertTrue(post->handCount[player] == pre.handCount[player], "Player gained 0 cards");

	//Test 3: Check the players deckCount decreased by 1 
	AssertTrue(post->deckCount[player] == pre.deckCount[player] - 1, "Cards drawn came from player's own pile");

	//Test 4: Village Card is gone
	AssertTrue(post->hand[player][handPos] != village, "Village card discarded");
	
	//Test 5: Check if number of actions has increased by 2
	AssertTrue(pre.numActions + 2 == post->numActions, "Number of actions has increased by two");

	//Test 6: Check if played card count increases by 1
	AssertTrue(pre.playedCardCount + 1 == post->playedCardCount, "Played card count increased by one");

	printf("\n");
}

int main() 
{
	srand((unsigned)time(NULL));
	
	int j, n, players, cardPos;

	struct gameState state;

	printf("Random Testing: Village Card\n\n");

	for (n = 0; n < 150; n++) 
	{
		//init/clear
		memset(&state,0,sizeof(struct gameState));

		//cards for game
		int k[10] = {adventurer, gardens, embargo, village, minion, 
					 mine, cutpurse, sea_hag, tribute, smithy};
		
		//random number of players (2-4)
		players = (rand()%3)+2;
		
		//"fill" state with intial supplyCount(s)
		initializeGame(players, k, rand()%1000, &state);

		for(j = 0; j < players; j++)
		{
			//random number of deck count (1 - MAX_DECK)
			state.deckCount[j] = (rand()%MAX_DECK)+1;

			//random number of discard count (1 - MAX_DECK)
			state.discardCount[j] = (rand()%MAX_DECK)+1;

			//random number of hand count (1 - MAX_HAND)
			state.handCount[j] = (rand()%MAX_HAND)+1;

			//random number of played card count (1 - MAX_DECK)
			state.playedCardCount = (rand()%MAX_DECK)+1;

			//random number of played cards (1 - MAX_DECK)
			state.playedCards[j] = (rand()%MAX_DECK)+1;

			//random village card in hand position (1 - handCount)
			cardPos = (rand()%(state.handCount[j])+1);
			state.hand[j][cardPos] = village;
		}
		
		//random number of coins (0 - 100)
		state.coins = rand()%101;

		//run with random player 
		RunVillageEffect((rand()%players), cardPos, &state);
	}
	
	return 0;
}