/*
	Andy Schon
	CS362
	Assignment 4
	randomtestcard2.c
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

void RunCouncilRoomEffect(int player, int handPos, struct gameState *post)
{
	printf("Iteration #%d:\n", iteration++);
	
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int effect = CouncilRoomEffect(player, handPos, post);

	//Test 1: Check CouncilRoomEffect returns 0
	AssertTrue(effect == 0, "CouncilRoomEffect(): return 0");
	
	//Test 2: Check that player who played council_room card has gained 3 cards
	//Draw 4 - discard
	AssertTrue(post->handCount[player] == pre.handCount[player] + 3, "Player that played card gained 3 cards");

	//Test 3: Check the player who played card deckCount decreased by 4 
	AssertTrue(post->deckCount[player] == pre.deckCount[player] - 4, "Cards drawn came from player's own pile");

	//Test 4: Check that numBuys increased by 1
	AssertTrue(post->numBuys == pre.numBuys + 1, "NumBuys increased by 1");
	
	//Test 5: CouncilRoom Card is gone
	AssertTrue(post->hand[player][handPos] != council_room, "Council Room Card not in hand");
	
	//Test 6: Check if played card count increases by 1
	AssertTrue(pre.playedCardCount + 1 == post->playedCardCount, "Played card count increased by one");
	
	//Test 7 - (playerCount-1)*2
	int i;
	for (i = 0; i < post->numPlayers; i++)
	{
		if ( i != player )
		{
			AssertTrue(post->handCount[i] == pre.handCount[i] + 1, "Other player drew card as well");
		}
	}
	
	printf("\n");
}

int main() 
{
	srand((unsigned)time(NULL));
	
	int j, n, players, cardPos;

	struct gameState state;

	printf("Random Testing: Council Room Card\n\n");

	for (n = 0; n < 550; n++) 
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

			//random council_room card in hand position (1 - handCount)
			cardPos = (rand()%(state.handCount[j])+1);
			state.hand[j][cardPos] = council_room;
		}
		
		//random number of coins (0 - 100)
		state.coins = rand()%101;

		//run with random player 
		RunCouncilRoomEffect((rand()%players), cardPos, &state);
	}
	
	return 0;
}