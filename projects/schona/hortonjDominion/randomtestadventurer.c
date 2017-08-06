/*
	Andy Schon
	CS362
	Assignment 4
	randomtestadventurer.c
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

int isTreasureCard(int card) 
{
	if (card == copper || card == silver || card == gold) return 1;
	else return 0;
}

void AdvEffect(int player, struct gameState *post, int cardPos)
{
	printf("Iteration #%d:\n", iteration++);
	
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int effect = actionAdventurer(post, cardPos);

	//Test: Check actionAdventurer returns 0
	AssertTrue(effect == 0, "actionAdventurer(): return 0");

	//Test: Check the players deckCount decreased at minimum by 2 
	AssertTrue(post->deckCount[player] <= pre.deckCount[player] + 2, "Gained cards came from player's own pile");

	//Test: Check the drawn cards are both treasure cards
	AssertTrue(isTreasureCard(post->hand[player][post->handCount[player] - 1]) && 
			   isTreasureCard(post->hand[player][post->handCount[player] - 2]), 
			   "Last 2 cards are treasure cards");

	//Test: Check to make sure that discard count is greater than or equal 0
	AssertTrue(post->discardCount[player] >= pre.discardCount[player], "Discard count >= 0");
			 			 
	//Test: check numActions is same as we are only calling Adventurer Effect which does not discard
	AssertTrue(post->playedCardCount == pre.playedCardCount, "Player's numActions has not changed");
	
	//Test: check played card count is same as we are only calling Adventurer Effect which does not discard
	AssertTrue(post->numActions == pre.numActions, "Player's playedCardCount has not changed");
	
	//Test: check coins is same as we are only calling Adventurer Effect which does not discard
	AssertTrue(post->coins == pre.coins, "Player's coins has not changed");
	
	//Test: Check that other than the above tests, nothing else changed
	pre.handCount[player] = post->handCount[player];
	pre.deckCount[player] = post->deckCount[player];
	pre.discardCount[player] = post->discardCount[player];

	//copy all
	memcpy(pre.deck[player], post->deck[player], sizeof(int) * pre.deckCount[player]);
	memcpy(pre.discard[player], post->discard[player], sizeof(int) * pre.discardCount[player]);
	memcpy(pre.playedCards, post->playedCards, sizeof(int) * pre.playedCardCount);
	
	//set cards same
	int i;
	for (i = 0; i < MAX_HAND; i++) {
		pre.hand[player][i] = post->hand[player][i];
	}

	//check no other changes occurred
	AssertTrue(memcmp(&pre, post, sizeof(struct gameState)) == 0, "No other changes to game state");

	printf("\n");
}

int main() 
{
	srand((unsigned)time(NULL));
	
	int j, n, players, cardPos;

	struct gameState state;

	printf("Random Testing: Adventurer Card\n\n");

	for (n = 0; n < 1000; n++) 
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
			//random number of deck count (0 - MAX_DECK)
			state.deckCount[j] = (rand()%MAX_DECK+1);

			//random number of discard count (1 - MAX_DECK)
			state.discardCount[j] = (rand()%MAX_DECK)+1;

			//random number of hand count (1 - MAX_HAND)
			state.handCount[j] = (rand()%MAX_HAND)+1;

			//random number of played card count (1 - MAX_DECK)
			state.playedCardCount = (rand()%MAX_DECK)+1;

			//random number of played cards (1 - MAX_DECK)
			state.playedCards[j] = (rand()%MAX_DECK)+1;

			//random adventurer card in hand position (1 - handCount)
			cardPos = (rand()%(state.handCount[j])+1);
			state.hand[j][cardPos] = adventurer;
		}
		
		//random number of coins (0 - 100)
		state.coins = rand()%101;
		
		//run with random player 
		AdvEffect((rand()%players), &state, cardPos);
	}
	
	return 0;
}