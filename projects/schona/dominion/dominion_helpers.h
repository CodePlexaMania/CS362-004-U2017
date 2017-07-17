#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);
//Below added to be able to test
/* Cards */
int AdventurerEffect(int currentPlayer, struct gameState *state);
int SmithyEffect(int currentPlayer, int handPos, struct gameState *state);
int MineEffect(int currentPlayer, int choice1, int choice2, int handPos, struct gameState *state);
int VillageEffect(int currentPlayer, int handPos, struct gameState *state);
/* Functions */
int whoseTurn(struct gameState *state);
int supplyCount(int card, struct gameState *state);

#endif
