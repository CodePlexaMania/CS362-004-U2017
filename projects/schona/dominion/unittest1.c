/*
	Andy Schon
	CS362
	unittest1.c
	- Testing getCost function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <stdio.h>

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
	printf("unittest1: Test getCost function");
	printf("\n----------------------------------------\n");
	
	//Test that getCost returns the correct value for each card as expected
	AssertTrue(getCost(curse) == 0, "curse card cost = 0");
	AssertTrue(getCost(estate) == 2, "estate card cost = 2");
	AssertTrue(getCost(duchy) == 5, "duchy card cost = 5");
	AssertTrue(getCost(province) == 8, "province card cost = 8");
	AssertTrue(getCost(copper) == 0, "copper card cost = 0");
	AssertTrue(getCost(silver) == 3, "silver card cost = 3");
	AssertTrue(getCost(gold) == 6, "gold card cost = 6");
	AssertTrue(getCost(adventurer) == 6, "adventurer card cost = 6");
	AssertTrue(getCost(council_room) == 5, "council_room card cost = 5");
	AssertTrue(getCost(feast) == 4, "feast card cost = 4");
	AssertTrue(getCost(gardens) == 4, "gardens card cost = 4");
	AssertTrue(getCost(mine) == 5, "mine card cost = 5");
	AssertTrue(getCost(remodel) == 4, "remodel card cost = 4");
	AssertTrue(getCost(smithy) == 4, "smithy card cost = 4");
	AssertTrue(getCost(village) == 3, "village card cost = 3");
	AssertTrue(getCost(baron) == 4, "baron card cost = 4");
	AssertTrue(getCost(great_hall) == 3, "great_hall card cost = 3");
	AssertTrue(getCost(minion) == 5, "minion card cost = 5");
	AssertTrue(getCost(steward) == 3, "steward card cost = 3");
	AssertTrue(getCost(tribute) == 5, "tribute card cost = 5");
	AssertTrue(getCost(ambassador) == 3, "ambassador card cost = 3");
	AssertTrue(getCost(cutpurse) == 4, "cutpurse card cost = 4");
	AssertTrue(getCost(embargo) == 2, "embargo card cost = 2");
	AssertTrue(getCost(outpost) == 5, "outpost card cost = 5");
	AssertTrue(getCost(salvager) == 4, "salvager card cost = 4");
	AssertTrue(getCost(sea_hag) == 4, "sea_hag card cost = 4");
	AssertTrue(getCost(treasure_map) == 4, "treasure_map card cost = 4");
	AssertTrue(getCost(27) == -1, "27: non-existent card returns -1");
	AssertTrue(getCost(-1) == -1, "-1: non-existent card returns -1");	
	
	return 0;	
}