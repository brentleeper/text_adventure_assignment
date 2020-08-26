/*
Name:  			Final Project
Programmer:		Brent Leeper
Class:  		COSC 1336.001
Date:			11/22/2016
*/
 
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef enum	{								//enumerates and creates data type 'direction' (used to determine user input for movement between adjacent locations)
		north,  						
		east,						
		south,						
		west						
				} direction;

typedef enum	{								//enumerates and creates data type 'dictionary' (used to determine if user input is a known word)
		help,
		search,
		flare_dict,
		pilot,
		rubbage_dict,
		cave_dict, 
		briefcase,
		open,
		shelter_dict,
		pistol,
		attendant,
		inventory,
		debris
				} dictionary;

economy_class(int *flare, int *mountain, int compass, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch);		//function prototypes
first_class(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch);
int string_search(char string[], char search[]);
cockpit(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch);
crash_site(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch);
forest_south(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch);
rubbage(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch);
cave(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch);
forest_east(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch);
mountain_top(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch);
delay(void);
inventory_func(int *flare, int *gun, int *keys, int *shelt_srch, int *cv_srch);
dictionary search_dictionary(char command[]);
direction find_direction(char command[]);

int main(void)
{
	int flare = 0;													//initialization of variables
	int *pflare = &flare;
	int mountain = 0;
	int *pmountain = &mountain;
	int moves = 0;
	int *pmoves = &moves;
	int gun = 0;
	int *pgun = &gun;
	int keys = 0;
	int *pkeys = &keys;
	int shelter_searches = 0;
	int *pshelt_srch = &shelter_searches;
	int cave_search = 0;
	int *pcv_srch = &cave_search;
	int start = 0;
	char capture[3];

	printf("\n\tYou are traveling home for the holidays from overseas.\n\tYou think to yourself ... 'Time with the family will be nice!'\n");		// start of game story 
	
	printf("\n\tBut Suddenly,\n\n\t\tBOOM!! BOOM!! BOOM!!\n");

	printf("\n\tSomething has gone terribly wrong! The plane has lost power.\n");

	printf("\n\tYou hear the pilot say,\n\n\t\t 'BRACE FOR IMPACT!!'\n");

	printf("\n\tYou are slammed forward and knocked unconscious.\n\n\n\n");

	delay();

	do {																																			//welcome text and user start or quit
		printf("\n\t\t\t\tWelcome to\n\t\t\t------------------------\n\t\t\t Unexpected Destination\n\t\t\t------------------------\n\n");

		printf("\n\tTo start:\t1");
		printf("\n\tTo quit:\t2");
		printf("\n\n\t> ");
		scanf("%d",&start);
		gets(capture);
	} while (start != 1 && start != 2);																												//only accepts 1 or 2 as user input

	if (start == 1)																																	//if user enters 1. Game start
	{
		printf("________________________________________________________________________________________________________\n\n");
		printf("\n\tEnter 'help' at any time for instructions\n\n");
		printf("________________________________________________________________________________________________________\n\n");

		economy_class(pflare, pmountain, 0, pgun, pmoves, pkeys, pshelt_srch, pcv_srch);															//calls economy_class function
	}																											
	else
	{																																				//if user enters 2. Game quit (all other numbers filtered in above loop)	
		return 0;
	}

	return 0;
}

economy_class(int *flare, int *mountain, int compass, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)				//runs situation when user moves to 'economy_class' from valid adjacent location
{
	direction dir = 0;
	char command[100];																												//user input stored in 'command'
	int phrase = 0;
	dictionary look_up = -1;

	if (compass == 0)																												//user starts game with no compass. If user returns to economy_class, compass will equal 1 and display other text.
	{
		printf("\n\tNot sure how much time has passed, you wake up dazed, confused, and unsure of your bearings.\n\tLooking around, you start to remember ... You are seated in the economy class of the airliner.\n\tObserving further, you realize that you are the SOLE SURVIVOR!\n\n");
		printf("\n\tStaggering while trying to stand up, a briefcase falls from the overhead compartment hitting you on the head.\n\n\tOuch! ... \n\n\tYou need to find your way out of here!!\n\n");
	}
	else
	{																																//displayed if user returns to economy_class after initial visit at game start.
		printf("\n\n\t----------------------------------\n\tYou are back in the economy class.\n\t----------------------------------\n\n\tIt sure is eerie in here with the deceased ... \n\tYou should head back.\n");
		printf("\n\tFirst class is to your west.\n");
	}
	do
	{
		do {																// gets user input and validates using 'find_direction' and 'search_dictionary' functions 
			printf("\n\t> ");
			gets(command);

			printf("Got Command: %s\n", command);

			*moves = *moves + 1;											// counts user moves (adds 1 to number of moves)

			dir = find_direction(command);									// 'dir' takes returned value of 'find_direction' (returns -1 if user command is not found)
			
			if (dir == -1)
			{
				look_up = search_dictionary(command);						// 'look_up' takes returned value of 'search_dictionary' (returns -1 if user command is not found)
			}
			else
			{
				look_up = -1;
			}

			if (look_up == -1 && dir == -1)									// if user command is not found in 'find_direction' or 'look_up'. Display error message 
			{
				if (phrase == 0)			
					printf("\n\tWhat??\n\n");
				else if (phrase == 1)
					printf("\n\tI don't understand??\n\n");					//(error messages is different for 1st, 2nd, and 3rd invalid user input)
				else
					printf("\n\tI don't know that word...\n\n");
				phrase++;
			}
		} while (dir < 0 && look_up < 0);


		if (dir == west)														//user command is "west"
		{
			if (compass == 0)													//if user has not found compass
			{
				printf("\n\tMaybe you should search that briefcase?\n");
			}
			else
			{																	//if user has found compass
				first_class(flare, mountain, gun, moves, keys, shelt_srch, cv_srch); //call first_class function (signifying a movement to a new environment)
			}
		}
		else if (dir == north)													//user command is 'north'
		{
			printf("\n\tThe plane has crashed up against a cliff ... no going this way ...\n");
		}
		else if (dir == east)													//user command is 'east'
		{
			printf("\n\tElectrical wiring hangs down from above ... sparking and surging. \n\n\t\t\t'ZAP! POP! ZZZZZ!'\n");
		}
		else if (dir == south)													//user command is 'south'
		{
			printf("\n\tThe emergency exit is jammed shut!!\n");
		}
		else if (look_up == search)													//user command is 'search'
		{
			if (compass == 0)													//if user has not found compass
			{
				printf("\n\tSearch what??\n");
			}
			else
			{																	//if user has found compass
				printf("\n\tNothing to search.\n");
			}
		}
		else if (look_up == open)													//user command is 'open'
		{
			if (compass == 0)													//if user has not found compass
			{
				printf("\n\tOpen what??\n");
			}
			else
			{																	//if user has found compass
				printf("\n\tNothing to open.\n");
			}
		}
		else if (look_up == briefcase)												//user command is 'briefcase'
		{
			if (compass == 0)													//if user has not found compass
			{
				printf("\n\tYou found a compass in the briefcase!!\n\tLooks like the First Class cabin is west of here!\n");
				compass++;
			}
			else                                                               //if user has found compass
			{
				printf("\n\tYou've already searched the briefcase...\n");
			}
		}
		else if (look_up == help)													//user command is 'help'
		{
			help_func();														//call help_func
		}

		else if (look_up == inventory)												//user command is 'inventory'
		{
			if (compass > 0)													//if user has found compass
			{
				inventory_func(flare, gun, keys, shelt_srch, cv_srch);			//call inventory function
			}
			else
			{																	//user has not found compass
				printf("\n\tNo items are in your inventory\n");
			}
		}
	} while (dir != west || compass == 0);

}

first_class(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)			//runs situation when user moves to 'first_class' from valid adjacent location
{
	direction dir = 0;
	char command[100];																			//holds user input
	int phrase = 0;
	dictionary look_up = -1;


	printf("\n\n\t--------------------------------------\n\tYou are in first class on the airliner\n\t--------------------------------------\n\n\tNothing but rows and rows of those who did not survive.\n\tAt the front of the plane, still strapped in, is the flight attendant who just served you lunch.\n\tMight not want to spend much time here.\n\tTo the south is an exit and to the west is the cockpit.\n");
				
	do
	{
		do {
			printf("\n\t> ");
			gets(command);
				
			*moves = *moves + 1;																//adds 1 to user moves

			dir = find_direction(command);														//compares user input, searches for direction	

			if (dir == -1)
			{
				look_up = search_dictionary(command);											//queries dictionary, returns value if user input is a match to a term 
			}
			else
			{
				look_up = -1;
			}

			if (look_up == -1 && dir == -1)
			{
				if (phrase == 0)
				printf("\n\tWhat??\n\n");														
				else if(phrase == 1)
				printf("\n\tI don't understand??\n\n");
				else 
				printf("\n\tI don't know that word...\n\n");
				phrase++;
			}
			
		} while (dir < 0 && look_up < 0);
		
																							//depending on user direction command one option below will run
		if (dir == west)
		{
			if (*keys > 0)																			
			{
				cockpit(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);					//moves user to location 'cockpit' by calling 'cockpit' command
			}
			else
			{
				printf("\n\tThe cockpit is locked.\n\n");
			}
		}
		else if (dir == north)
		{
			printf("\n\tThe plane has crashed up against a cliff ... no going this way ...\n");
		}
		else if (dir == east)
		{
			economy_class(flare, mountain, 1, gun, moves, keys, shelt_srch, cv_srch);				//moves user to location 'economy_class' by calling 'economy_class' command
		}
		else if (dir == south)
		{
			if (*keys == 0)
			{
				printf("\n\tThe exit is locked.\n\t");
			}
			else
			{
				crash_site(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);					//moves user to location 'crash_site' by calling 'crash_site' command
			}
		}
		
																								//determin what user command was and run code depending on input
		else if (look_up == search)
		{
			printf("\n\tSearch what??\n");
		}
		else if (look_up == briefcase)
		{
			printf("\n\tWhat about it??\n");
		}
		else if (look_up == help)
		{
			help_func();																			//calls 'help_func'
		}
		else if (look_up == inventory)
		{
			inventory_func(flare, gun, keys, shelt_srch, cv_srch);									//calls 'inventory_func'
		}
		else if (look_up == attendant)
		{
			if (*keys == 0)																			//if user has not found keys 
			{
				printf("\n\tYou found a set of keys in the flight attendant's pocket\n\t");
				*keys = *keys + 1;
			}
			else
			{																						//if user has found keys
				printf("\n\tYou already searched the flight attendant.\n\t");
			}
		}
		
	} while (dir != east);

}

cockpit(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)						//runs situation when user moves to 'cockpit' from valid adjacent location
{
	direction dir = 0;
	char command[100];
	int phrase = 0;
	dictionary look_up = -1;

	printf("\n\n\t--------------------------------------\n\tYou are in the cockpit of the airliner\n\t--------------------------------------\n\n\tNeither of the pilots survived ...\n");
				
	do
	{
		do {
			printf("\n\t> ");
			gets(command);																								//takes user input

			*moves = *moves + 1;

			dir = find_direction(command);																				//determines if user input is direction command

			if (dir == -1)																								
			{
				look_up = search_dictionary(command);																	//determines if user input is dictionary command
			}
			else
			{
				look_up = -1;
			}

			if (look_up == -1 && dir == -1)																				//if user input is not found
			{
				if (phrase == 0)
					printf("\n\tWhat??\n\n");
				else if (phrase == 1)
					printf("\n\tI don't understand??\n\n");
				else
					printf("\n\tI don't know that word...\n\n");
				phrase++;
			}
		} while (dir < 0 && look_up < 0);


		if (dir != east && look_up == -1)
		{
			printf("\n\tWhat are you thinking?? How would you go that way??\n\tFirst class is to the east\n");
		}
		else if (dir == east)
		{
			first_class(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);									//moves user to 'first_class' by calling the 'first_class' function
		}
		

		else if (look_up == search)
		{
			printf("\n\tSearch what??\n");
		}
		else if (look_up == pilot)
		{
			if (*gun == 0)
			{
				printf("\n\tYou found a pistol.\n");
				*gun = *gun + 1;
			}
			else
			{
				printf("\n\tYou already searched the pilots.\n\t");
			}
		}
		else if (look_up == help)
		{
			help_func();																						//calls 'help_func'
		}
		else if (look_up == inventory)
		{
			inventory_func(flare, gun, keys, shelt_srch, cv_srch);												//calls 'inventory_func'
		}
		
	} while (dir != east);
}

crash_site(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)											//runs situation when user moves to 'crash_site' from valid adjacent location
{
	direction dir = 0;
	char command[100];
	int phrase = 0;
	dictionary look_up = -1;

	printf("\n\n\t----------------------------------------------\n\tYou are outside the airliner at the crash site\n\t----------------------------------------------\n\n\tThe plane crashed just south of a large cliff... no going that way.\n\tJust behind the plane, to the east,  is rubbage from the destruction of the tail of the plane.\n\tTo the south and far to the east, nothing but a grand forest. No telling what lies beyond the tree line.\n\tAnd a few miles to the west is a towering mountain.\n ");
				
	do {
		do {
			printf("\n\t> ");
			gets(command);																			//takes user input


			*moves = *moves + 1;

			dir = find_direction(command);															//determines if user input is a directional command

			if (dir == -1)
			{
				look_up = search_dictionary(command);												//determines if user input is dictionary command
			}
			else
			{
				look_up = -1;
			}

			if (look_up == -1 && dir == -1)															//if user input is not found
			{
				if (phrase == 0)
					printf("\n\tWhat??\n\n");
				else if (phrase == 1)
					printf("\n\tI don't understand??\n\n");
				else
					printf("\n\tI don't know that word...\n\n");
				phrase++;
			}
		} while (dir < 0 && look_up < 0);

		if (dir == west)
		{
			cave(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);					//move user to 'cave' by calling the 'cave' function
		}
		else if (dir == north)
		{
			first_class(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);			//move user to 'first_class' by calling the 'first_class' function
		}
		else if (dir == east)
		{
			rubbage(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);				//move user to 'rubbage' by calling the 'rubbage' function
		}
		else if (dir == south)
		{
			forest_south(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);			//move user to 'forest_south' by calling the 'forest_south' function
		}

		else if (look_up == search)
		{
			printf("\n\tNothing to search ... \n");
		}
		else if (look_up == help)
		{
			help_func();																	//calls 'help_func'
		}
		else if (look_up == inventory)
		{
			inventory_func(flare, gun, keys, shelt_srch, cv_srch);							//calls 'inventory_func'			
		}
	
	} while (dir != north && dir != east && dir != south && dir != west);
}

cave(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)				//runs situation when user moves to 'cave' from valid adjacent location
{
	direction dir = 0;
	char command[100];
	int phrase = 0;
	dictionary look_up = -1;

	printf("\n\n\t---------------------------------------------\n\tYou are at a cave at the base of the mountain\n\t---------------------------------------------\n\n\tThe mountain top is further west and \n\tthe crash site is a few miles east of here.\n\n\t");
	
	if (*cv_srch == 0)
	{
		printf("I wouldn't go in the cave if I were you!!\n");
	}
				  
	do
	{
		do {
			printf("\n\t> ");
			gets(command);																			//takes user input


			*moves = *moves + 1;

			dir = find_direction(command);															//determines if user input is a directional command

			if (dir == -1)
			{
				look_up = search_dictionary(command);												//determines if user input is dictionary command
			}
			else
			{
				look_up = -1;
			}

			if (look_up == -1 && dir == -1)															//if user input is not found
			{
				if (phrase == 0)
					printf("\n\tWhat??\n\n");
				else if (phrase == 1)
					printf("\n\tI don't understand??\n\n");
				else
					printf("\n\tI don't know that word...\n\n");
				phrase++;
			}
		} while (dir < 0 && look_up < 0);


		if (dir == west)
		{
			mountain_top(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);				//move user to 'mountain_top' by calling the 'mountain_top' function
		}
		else if (dir == north)
		{
			printf("\n\tA cliff looms overhead ... no going this way ...\n");
		}
		else if (dir == east)
		{
			crash_site(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);					//move user to 'crash_site' by calling the 'crash_site' function
		}
		else if (dir == south)
		{
			forest_south(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);				//move user to 'forest_south' by calling the 'forest_south' function
		}

		else if (look_up == search)
		{
			if (*cv_srch == 0)
			{
				printf("\n\tSearch what??\n");
			}
			else
			{
				printf("\n\tNothing to search...\n");
			}
		}
		else if (look_up == cave_dict)																//if user input is cave (search cave)
		{
			if (*cv_srch > 0)																	// if user has already searched the cave
			{
				printf("\n\tThe bear's body lies on the rocky cave floor. Cold. Lifeless.\n\n\tCome on, you need to find your way off this island\n");
				cave(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);					//move user to 'cave' by calling the 'cave' function
			}
			if (*gun == 0 && *flare == 0)														//if user does not have the pistol (gun) or the flare
			{
				printf("\n\n\tRUN!!\n\tIT'S A BEAR!!\n\n\tThe bear grabs hold of you and .... \n");
				printf("\n\tGAME OVER\n\n");
				exit(EXIT_SUCCESS);																//game over
			}
			else
			{
				printf("\n\tUpon entering the cave you find yourself face-to-face with a bear!!\n\n");  //if user has flare or pistol (gun)
				printf("\n\tQuick, defend yourself!\n\n");
				do{
					do {

						*cv_srch = *cv_srch + 1;

						printf("\n\t> ");
						gets(command);																		//takes user input

						*moves = *moves + 1;

						dir = find_direction(command);														//determines if user input is a directional command

						if (dir == -1)
						{
							look_up = search_dictionary(command);											//determines if user input is a directional command
						}
						else
						{
							look_up = -1;
						}

						if (look_up == -1 && dir == -1)														//if user inputs invalid command or spells command incorrectly 
						{
							printf("\n\tToo late!\n\n\t The bear grabs ahold of you!!\n\n\tLooks like you're dinner ...\n\n");
							printf("\n\tGAME OVER\n\n");
							exit(EXIT_SUCCESS);																//game over
						}	
					} while (dir < 0 && look_up < 0);

					
					if (dir == west)																	
					{
						printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
					}
					else if (dir == north)
					{
						printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
					}
					else if (dir == east)
					{
						printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
					}
					else if (dir == south)
					{
						printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
					}

					else if (look_up == search)
					{
						printf("\n\tNothing to search.\n\tHurry and defend yourself!!\n");
					}
					else if (look_up == flare_dict)															//if user input is flare
					{
						if (*flare > 0)
						{
							printf("\n\tYou fire the flare gun!\n\n");

							delay();

							printf("\n\tThe flare strikes the bear.\n\tThe flare only angers the bear!!\n\n\t\tRUN!!\n\n\tThe bear grabs ahold of you and...\n");

							printf("\n\tGAME OVER\n\n");
							exit(EXIT_SUCCESS);															//game over
						}
						else
						{
							printf("\n\tYou don't have a flare!!\n");
						}
					}
					else if (look_up == pistol)																//if user input is pistol
					{
						if (*gun > 0)
						{
							printf("\n\tYou fire the pistol!\n\n");

							delay();
							printf("\n\tBANG!! BANG!!\n\n");
							delay();
																										//bear is killed
							printf("\n\tYour bullets strike the bear.\n\tThe bear collapses.\n\tThat was close!!\n\n\tWe should get out of here!\n");

							delay();

							cave(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);				//move user to 'cave' by calling the 'cave' function
						}
						else
						{
							printf("\n\tYou don't have a pistol!!\n\t");
						}
					}
					else if (look_up == help)				
					{
						help_func();																	//calls 'help_func'								
					}
					else if (look_up == inventory)
					{
						printf("\n\t---------------------\n\tInventory unavailable\n\t---------------------\n\n");
					}
				} while (look_up != pistol || look_up != flare_dict);
			}
		}
		else if (look_up == help)
		{
			help_func();																				//calls 'help_func'	
		}
		else if (look_up == inventory)
		{
			inventory_func(flare, gun, keys, shelt_srch, cv_srch);										//calls 'inventory_func'
		}
		
	} while (dir != east && dir != west && dir != south);
}	   
										
rubbage(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)		//runs situation when user moves to 'rubbage' from valid adjacent location
{
	direction dir = 0;
	char command[100];
	int phrase = 0;
	dictionary look_up = -1;

	printf("\n\n\t----------------------------------------------\n\tYou are amongst the rubbage of the plane crash\n\t----------------------------------------------\n\n\tLooks like the tail of the plane detached during the crash.\n\tLuggage and other random items, as well debris, are littered all around.\n\t");
				
	do
	{
		do {
			printf("\n\t> ");
			gets(command);														//takes user input

			*moves = *moves + 1;

			dir = find_direction(command);										//determines if user input is a directional command

			if (dir == -1)
			{
				look_up = search_dictionary(command);							//determines if user input is dictionary command
			}
			else
			{
				look_up = -1;
			}

			if (look_up == -1 && dir == -1)										//if user input is not found
			{
				if (phrase == 0)
					printf("\n\tWhat??\n\n");
				else if (phrase == 1)
					printf("\n\tI don't understand??\n\n");
				else
					printf("\n\tI don't know that word...\n\n");
				phrase++;
			}
		} while (dir < 0 && look_up < 0);


		if (dir == west)
		{
			crash_site(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);		//move user to 'crash_site' by calling the 'crash_site' function
		}
		else if (dir == north)
		{
			printf("\n\tThe plane has crashed up against a cliff ... no going this way ...\n");
		}
		else if (dir == east)
		{
			forest_east(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);	//move user to 'forest_east' by calling the 'forest_east' function
		}
		else if (dir == south)
		{
			forest_south(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);  //move user to 'forest_south' by calling the 'forest_south' function
		}
	

		else if (look_up == search)
		{
			printf("\n\tSearch What??\n");
		}
		else if (look_up == rubbage_dict || look_up == debris)
		{
			if (*flare == 0)												//if user has not found flare
			{
				printf("\n\tYou found a flare gun! This might come in handy.\n");
				*flare = *flare + 1;
			}
			else
			{																//if user has already found flare
				printf("\n\tThere is nothing else of use.\n");
			}
		}
		else if (look_up == help)
		{
			help_func();													//calls 'help_func'
		}
		else if (look_up == inventory)
		{
			inventory_func(flare, gun, keys, shelt_srch, cv_srch);			//calls 'inventory_func'
		}
	
	} while (dir != east && dir != west && dir != south);
}

forest_south(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)		//runs situation when user moves to 'forest_south' from valid adjacent location
{
	direction dir = 0;
	char command[100];
	int phrase = 0;
	dictionary look_up = -1;

	printf("\n\n\t---------------------------------------------\n\tYou are in the forest south of the crash site\n\t---------------------------------------------\n\n\tNothing here, it might be best not to wonder any further. You might not be able to find your way back!\n");;
				  

	do
	{
		do {
			printf("\n\t> ");	
			gets(command);																		//takes user input

			*moves = *moves + 1;

			dir = find_direction(command);														//determines if user input is a directional command

			if (dir == -1)
			{
				look_up = search_dictionary(command);											//determines if user input is dictionary command
			}
			else
			{
				look_up = -1;
			}

			if (look_up == -1 && dir == -1)														//if user input is not found
			{
				if (phrase == 0)
					printf("\n\tWhat??\n\n");
				else if (phrase == 1)
					printf("\n\tI don't understand??\n\n");
				else
					printf("\n\tI don't know that word...\n\n");
				phrase++;
			}
		} while (dir < 0 && look_up < 0);


		if (dir == west)
		{
			printf("\n\tYou are lost deep in the forest never able to find your way out.\n");   //user lost in forest
			printf("\n\tGAME OVER\n");
			exit(EXIT_SUCCESS);																	//game over
		}
		else if (dir == north)
		{
			crash_site(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);					//move user to 'crash_site' by calling the 'crash_site' function
		}
		else if (dir == east)
		{
			printf("\n\tYou are lost deep in the forest never able to find your way out.\n");	//user lost in forest
			printf("\n\tGAME OVER\n");
			exit(EXIT_SUCCESS);																	//game over
		}
		else if (dir == south)
		{
			printf("\n\tYou are lost deep in the forest never able to find your way out.\n");	//user lost in forest
			printf("\n\tGAME OVER\n");
			exit(EXIT_SUCCESS);																	//game over
		}
	
		else if (look_up == search)
		{
			printf("\n\tNothing to search\n");
		}
		else if (look_up == help)
		{
			help_func();																		//calls 'help_func'
		}
		else if (look_up == inventory)
		{
			inventory_func(flare, gun, keys, shelt_srch, cv_srch);								//calls 'inventory_func'
		}
	
	} while (dir != north);
}

forest_east(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)	//runs situation when user moves to 'forest_east' from valid adjacent location
{
	direction dir = 0;
	char command[100];
	int phrase = 0;
	dictionary look_up = -1;
	
	if (*mountain == 0)																			//if user has not been to the moutain_top
	{
		printf("\n\n\t-------------------------------------------------------------------\n\tYou are in the forest east of the crash site and beyond the rubbage\n\t-------------------------------------------------------------------\n\n\tMight be best to turn back so that you don't get lost.\n\tMaybe you should head to the mountain to get a view of the area...\n");
	}				  
	else
	{																							//if user has been to the moutain_top
		printf("\n\t-------------------------------------------------------------------\n\tYou are in the forest east of the crash site and beyond the rubbage\n\t-------------------------------------------------------------------\n\tWhat is that?\n\n\tJust north, a distinctive shape. Perhaps a cabin or makeshift shelter...\n");
	}				
	do {
		do {
			printf("\n\t> ");
			gets(command);																		//takes user input

			*moves = *moves + 1;

			dir = find_direction(command);														//determines if user input is a directional command

			if (dir == -1)
			{
				look_up = search_dictionary(command);											//determines if user input is dictionary command
			}
			else
			{
				look_up = -1;
			}
				
			if (look_up == -1 && dir == -1)														//if user input is not found
			{
				if (phrase == 0)
					printf("\n\tWhat??\n\n");
				else if (phrase == 1)
					printf("\n\tI don't understand??\n\n");
				else
					printf("\n\tI don't know that word...\n\n");
				phrase++;
			}
		} while (dir < 0 && look_up < 0);


		if (dir == west)
		{
			rubbage(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);				//move user to 'rubbage' by calling the 'rubbage' function
		}
		else if (dir == north)
		{
			if (*mountain == 0)																//if user has not visited the mountain_top
			{
				printf("\n\tYou are lost deep in the forest never able to find your way out.\n");		//user is lost
				printf("\n\tGAME OVER\n");
				exit(EXIT_SUCCESS);															//game over
			}
			else
			{																				//if user has visited mountain_top
				shelter(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);			//move user to 'shelter' by calling the 'shelter' function
			}
		}
		else if (dir == east)
		{
			if (*mountain == 0)																//if user has not visited the mountain_top
			{
				printf("\n\tYou are lost deep in the forest never able to find your way out.\n");		//user is lost
				printf("\n\tGAME OVER\n");
				exit(EXIT_SUCCESS);															//game over
			}
			else                                                                            //if user has visited the mountain_top
			{
				beach(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);				//move user to 'beach' by calling the 'beach' function
			}
		}
		else if (dir == south)
		{
			if (*mountain == 0)																//if user has not visited the mountain_top
			{
				printf("\n\tYou are lost deep in the forest never able to find your way out.\n");	//user is lost
				printf("\n\tGAME OVER\n");
				exit(EXIT_SUCCESS);															//game over
			}
			else
			{																				//if user has visited the mountain_top
				printf("\n\tThe only thing in this direction is miles and miles of wildnerness.\n");
			}
		}
		

		else if (look_up == search)
		{
			printf("\n\tNothing to search\n");
		}
		else if (look_up == help)
		{
			help_func();																	//calls 'help_func'
		}
		else if (look_up == inventory)
		{
			inventory_func(flare, gun, keys, shelt_srch, cv_srch);							//calls 'inventory_func'
		}
	
	} while (dir != north && dir != west && dir != east);
}

mountain_top(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)		//runs situation when user moves to 'mountain_top' from valid adjacent location
{
	direction dir = 0;
	char command[100];
	int phrase = 0;
	int restart = 0;
	dictionary look_up = -1;

	*mountain = *mountain + 1;

	printf("\n\n\t--------------------------------------------------------\n\tYou are on the mountain top and can see a great distance\n\t--------------------------------------------------------\n\n\tYou can see the crash site and the rubbage. Beyond it is the edge of the forest.\n\tBut even further beyond the forest you see that the land gives way to water.\n\n\tYou're pretty high up. Be careful not to take a bad step.\n");
				
	do
	{
		do {
			printf("\n\t> ");
			gets(command);																	//takes user input

			*moves = *moves + 1;

			dir = find_direction(command);													//determines if user input is a directional command

			if (dir == -1)
			{
				look_up = search_dictionary(command);										//determines if user input is dictionary command
			}
			else
			{
				look_up = -1;
			}

			if (look_up == -1 && dir == -1)													//if user input is not found
			{
				if (phrase == 0)
					printf("\n\tWhat??\n\n");
				else if (phrase == 1)
					printf("\n\tI don't understand??\n\n");
				else
					printf("\n\tI don't know that word...\n\n");
				phrase++;
			}
		} while (dir < 0 && look_up < 0);													//if user input is directional command


		if (dir == west)
		{
			printf("\n\tPeeking over the edge you slip and fall ... way, way down.\n");		//user falls
			printf("\n\tGAME OVER\n\n");
			exit(EXIT_SUCCESS);															//gave over
		}
		else if (dir == north)
		{
			printf("\n\tPeeking over the edge you slip and fall ... way, way down.\n");		//user falls
			printf("\n\tGAME OVER\n\n");
			exit(EXIT_SUCCESS);																
		}
		else if (dir == east)
		{
			cave(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);				//move user to 'cave' by calling the 'cave' function
		}
		else if (dir == south)
		{
			printf("\n\tPeeking over the edge you slip and fall ... way, way down.\n");		//user falls
			printf("\n\tGAME OVER\n\n");
			exit(EXIT_SUCCESS);															//game over
		}
	

		else if (look_up == search)
		{
			printf("\n\tNothing to search.\n");
		}
		else if (look_up == help)
		{
			help_func();																//calls 'help_func'
		}
		else if (look_up == inventory)
		{
			inventory_func(flare, gun, keys, shelt_srch, cv_srch);						//calls 'inventory_func'
		}
	
	} while (dir != east);
}

beach(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)		//runs situation when user moves to 'beach' from valid adjacent location
{
	direction dir = 0;
	char command[100];
	int phrase = 0;
	dictionary look_up = -1;

	printf("\n\n\t------------------------------------\n\tYou have found your way to the beach\n\t------------------------------------\n\n\tLooking out across the water, all you see is the horizon.\n");
				 
	delay();

	printf("\n\tBut wait...\n\tA faint hum\n\t");

	delay();

	printf("\n\tA small sea plane comes into view!!\n");

	delay();

	if (*flare == 0 && *gun == 0)														//if user has not found pistol (gun) or flare
	{
		printf("\n\tIf only we had some way to signal them!\n\tYou watch as your only hope flies off into the distance ...\n\n");
		printf("\n\tGAME OVER\n\n");
		printf("\n\tHINT: Look for a way to signal the plane!\n\n");

		exit(EXIT_SUCCESS);																//game over
	}
	else if (*flare > 0 || *gun > 0)													//if user has found either flare or pistol (gun)
	{
		printf("\n\tQuick, do something to get their attention!\n");
	}

	do
	{
		do {
			printf("\n\t> ");
			gets(command);																//takes user input

			*moves = *moves + 1;

			dir = find_direction(command);												//determines if user input is a directional command

			if (dir == -1)
			{
				look_up = search_dictionary(command);									//determines if user input is dictionary command
			}
			else
			{
				look_up = -1;
			}

			if (look_up == -1 && dir == -1)												//if user input is not found or command is spelled incorrectly
			{
				printf("\n\tYou missed the opportunity to signal them!\n\tYou watch as your only hope flies off into the distance ...\n\n");
				printf("\n\tGAME OVER\n\n");
				exit(EXIT_SUCCESS);														//game over
			}
		} while (dir < 0 && look_up < 0);


		if (dir == west)
		{
			printf("\n\tYou can't go back!\n\tThis might be your only shot!\n");
		}
		else if (dir == north)
		{
			printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
		}
		else if (dir == east)
		{
			printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
		}
		else if (dir == south)
		{
			printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
		}


		else if (look_up == search)
		{
			printf("\n\tNothing to search.\n\tHurry and shoot the flare!!\n");
		}
		else if (look_up == flare_dict)													//if user input is flare
		{
			printf("\n\tYou fire the flare! But did they notice??\n");

			delay();

			printf("\n\tYES!! YES!!\n\n\tThey are turning around!\n");

			delay();

			printf("\n\tThey have landed.\n\tThe men bind your wounds and take you onboard.\n");

			delay();

			printf("\n\tYou've been rescued!\n\n\tYOU WIN!!\n\n");
			printf("\t\tMOVES %i\n\n", *moves);										//displays user moves

			exit(EXIT_SUCCESS);														// WIN!!
		}
		else if (look_up == pistol)														//if user input is pistol
		{
			printf("\n\tYou fire the pistol! But did they notice??\n");

			delay();

			printf("\n\tThe plan continues on it's path\n");

			printf("\n\tYou watch as your only hope flies off into the distance ...\n\n");
			printf("\n\tGAME OVER\n\n");
			exit(EXIT_SUCCESS);														//game over

		}
		else if (look_up == help)
		{
			help_func();															//calls 'help_func'
		}
		else if (look_up == inventory)
		{
			inventory_func(flare, gun, keys, shelt_srch, cv_srch);					//calls 'inventory_func'
		}
	
	} while (look_up != flare_dict);
}

shelter(int *flare, int *mountain, int *gun, int *moves, int *keys, int *shelt_srch, int *cv_srch)		//runs situation when user moves to 'shelter' from valid adjacent location
{
	direction dir = 0;
	char command[100];
	int phrase = 0;
	dictionary look_up = -1;
	

	printf("\n\n\t------------------------------------------------------\n\tYou have found an abandoned shelter deep in the forest\n\t------------------------------------------------------\n\n\tI wouldn't go any further, you could get lost!\n\n\tMight be careful. Not sure if anyone is still around.\n");
				  
	do
	{
		do {
			printf("\n\t> ");
			gets(command);														//takes user input

			*moves = *moves + 1;

			dir = find_direction(command);										//determines if user input is a directional command

			if (dir == -1)
			{
				look_up = search_dictionary(command);							//determines if user input is dictionary command
			}
			else
			{
				look_up = -1;
			}

			if (look_up == -1 && dir == -1)										//if user input is not found
			{
				if (phrase == 0)
					printf("\n\tWhat??\n\n");
				else if (phrase == 1)
					printf("\n\tI don't understand??\n\n");
				else
					printf("\n\tI don't know that word...\n\n");
				phrase++;
			}
		} while (dir < 0 && look_up < 0);


			if (dir == west)							
		{
			printf("\n\tYou are lost deep in the forrest never able to find your way out.\n");		//user lost 
			printf("\n\tGAME OVER\n");
			exit(EXIT_SUCCESS);												//game over
		}
		else if (dir == north)	
		{
			printf("\n\tYou are lost deep in the forrest never able to find your way out.\n");		//user lost
			printf("\n\tGAME OVER\n");
			exit(EXIT_SUCCESS);												//game over
		}
		else if (dir == east)
		{
			printf("\n\tYou are lost deep in the forrest never able to find your way out.\n");		//user lost
			printf("\n\tGAME OVER\n");
			exit(EXIT_SUCCESS);												//game over
		}
		else if (dir == south)
		{
			forest_east(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);	//move user to 'forest_east' by calling the 'forest_east' function
		}
		

		else if (look_up == search)
		{
			if (*shelt_srch == 0)											//if user has not searched the shelter
			{
				printf("\n\tSearch what??\n");
			}
			else
			{																//if user has searched shelter
				printf("\n\tNothing to search\n");
			}
		}
		else if (look_up == shelter_dict)									
		{
			if (*shelt_srch > 0)											//if user has searched shelter
			{
				printf("\n\tYou already searched the shelter\n\t");
				shelter(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);		//move user to 'shelter' by calling the 'shelter' function
			}
			if (*gun == 0 && *flare == 0)									//if user has not found flare or pistol (gun)
			{
				printf("\n\tUpon entering the shelter you find yourself face-to-face with a hungry pack of wolves!!\n\n\t\tRUN!!\n\n\tWorking as a team, the wolves quickly catch up and surround you. \n\n\tLooks like you're dinner.\n\n\n\tIf only you had some way to protect yourself ...\n\n");
				printf("\n\tGAME OVER\n\n");
				exit(EXIT_SUCCESS);											//game over
			}
			else
			{																//if user has found flare or pistol (gun)

				printf("\n\tUpon entering the shelter you find yourself face-to-face with a hungry pack of wolves!!\n\n");
				printf("\n\tQuick, defend yourself!\n\n");
				do {

					*shelt_srch = *shelt_srch + 1;

					printf("\n\t> ");
					gets(command);											//takes user input

					*moves = *moves + 1;

					dir = find_direction(command);							//determines if user input is a directional command

					if (dir == -1)
					{
						look_up = search_dictionary(command);				//determines if user input is dictionary command
					}
					else
					{
						look_up = -1;
					}

					if (look_up == -1 && dir == -1)							//if user input is not found or command is spelled incorrectly
					{
						printf("\n\tToo late!\n\n\t The wolves surround you.\n\n\tLooks like you're dinner ...\n\n");
						printf("\n\tGAME OVER\n\n");
						exit(EXIT_SUCCESS);									//game over
					}
				} while (dir < 0 && look_up < 0);


				if (dir == west)
				{
					printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
				}
				else if (dir == north)
				{
					printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
				}
				else if (dir == east)
				{
					printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
				}
				else if (dir == south)
				{
					printf("\n\tYou can't go now!\n\tThis might be your only shot!\n");
				}
				

				else if (look_up == search)
				{
					printf("\n\tNothing to search.\n\tHurry and defend yourself!!\n");
				}
				else if (look_up == flare_dict)								//if user input is flare
				{ 
					if (*flare > 0)										
					{
						printf("\n\tYou fire the flare gun!\n\n");

						delay();

						printf("\n\tThe flare strikes one of the wolves and the others scatter off into the woods.\n\tThat was close!!\n\n\tWe should get out of here!\n");

						delay();

						shelter(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);	//move user to 'shelter' by calling the 'shelter' function
					}
					else
					{
						printf("\n\tYou don't have a flare!!\n");
					}
				}
				else if (look_up == pistol)									//if user input if pistol
				{
					if (*gun > 0)
					{
						printf("\n\tYou fire the pistol!\n\n");

						delay();
						printf("\n\tBANG!! BANG!!\n\n");
						delay();

						printf("\n\tYour bullets strike two of the wolves and the others scatter off into the woods.\n\tThat was close!!\n\n\tWe should get out of here!\n");

						delay();

						shelter(flare, mountain, gun, moves, keys, shelt_srch, cv_srch);	//move user to 'shelter' by calling the 'shelter' function
					}
					else
					{
						printf("\n\tYou don't have a pistol!!\n\t");
					}
				}
				else if (look_up == help)
				{
					help_func();															//calls 'help_func'
				}
				else if (look_up == inventory)
				{
					printf("\n\t---------------------\n\tInventory unavailable\n\t---------------------\n\n");
				}				
				
			} while (look_up != pistol || look_up != flare_dict);

			}
			
			else if (look_up == help)
			{
				help_func();																		//calls 'help_func'
			}
			else if (look_up == inventory)
			{
				inventory_func(flare, gun, keys, shelt_srch, cv_srch);								//calls 'inventory_func'
			}
			
	} while (dir != south);
}

int string_search(char string[], char search[])											//used to search for a string within another string
{
	int i = 0;
	int j = 0;
	int index = 0;

	while (string[i] != NULL)															//while string[i] is not NULL
	{

		while ((string[i] != search[0]) && (string[i] != NULL))							//while string[i] is not equal to search[0] and string[i] is not NULL (searching for first character of user input within the given string until a matching first character is found or a NULL value is reached)
		{
			i++;																		//increment i
		}

		if (string[i] == NULL)															//if string [i] equals NULL
		{
			return -1;																	//return -1, indicating the string was not found
		}

		index = i;																		//index take the value of i

		while ((string[i] == search[j]) && (string[i] != NULL) && (search[j] != NULL)) // while string[i] is equal to search[j] and string[i] is not NULL and search[j] is not equal to NULL (searching for matching sets in strings, other than matching first character only)
		{
			i++;																		//verifies that all characters in user input match a given string
			j++;
		}
		if (search[j] == NULL)															//once search[j] equals NULL, the current value for 'index' is the starting location of the match (index equals the number of time the first, or outer most, while loop completed.)
		{
			return index;																//returns the starting location of the match 
		}
		if (string[i] == NULL)															//if string[i] is equal to NULL the full string did not match
		{
			return -1;																	//return -1, indicating no match was found	
		}

		i = index + 1;																	//i takes value of index + 1
		j = 0;																			//j is reset to 0 and the loop restarts	
	}
}

direction find_direction(char command[])											//used to determine if user input is a directional command and return the corresponding value
{
	int search_status = 0;
	char N[] = "orth";
	char E[] = "ast";
	char S[] = "outh";
	char W[] = "est";

	search_status = string_search(command, W);								//search for west 
	if (search_status != -1)
	{
		return west;									//if west is found, return its corresponding value
	}

	search_status = string_search(command, N);								//search for north 
	if (search_status != -1)
	{
		return north;									//if north is found, return its corresponding value
	}

	search_status = string_search(command, S);								//search for south 
	if (search_status != -1)
	{
		return south;									//if south is found, return its corresponding value
	}

	search_status = string_search(command, E);								//search for east 
	if (search_status != -1)
	{
		return east;									//if east is found, return its corresponding value
	}
	if (search_status == -1)												//no direction found
		return -1;										//return value signifying no match
}

dictionary search_dictionary(char command[])											//used to determine if user input is a dictionary command and return the corresponding value
{
	int search_status = 0;
	char H[] = "elp";
	char S[] = "earch";
	char F[] = "lare";
	char P[] = "ilot";
	char R[] = "ubbage";
	char C[] = "ave";
	char B[] = "riefcase";
	char O[] = "pen";
	char SH[] = "helter";
	char PI[] = "istol";
	char A[] = "ttendant";
	char I[] = "nventory";
	char D[] = "ebris";

	search_status = string_search(command, H);					//search for 'help'
	if (search_status != -1)
	{
		return help;								//if help is found, return its corresponding value
	}
	search_status = string_search(command, B);					//search for 'briefcase'
	if (search_status != -1)
	{
		return briefcase;							//if briefacse is found, return its corresponding value
	}
	search_status = string_search(command, F);					//search for 'flare'
	if (search_status != -1)
	{
		return flare_dict;							//if flare is found, return its corresponding value
	}
	search_status = string_search(command, P);					//search for 'pilot'
	if (search_status != -1)
	{
		return pilot;								//if pilot is found, return its corresponding value
	}
	search_status = string_search(command, R);					//search for 'rubbage'
	if (search_status != -1)
	{
		return rubbage_dict;						//if rubbage is found, return its corresponding value
	}
	search_status = string_search(command, C);					//search for 'cave'
	if (search_status != -1)
	{
		return cave_dict;							//if cave is found, return its corresponding value
	}
	search_status = string_search(command, O);					//search for 'open'
	if (search_status != -1)
	{
		return open;								//if open is found, return its corresponding value
	}
	search_status = string_search(command, SH);					//search for 'shelter'
	if (search_status != -1)
	{
		return shelter_dict;						//if shelter is found, return its corresponding value
	}
	search_status = string_search(command, PI);					//search for 'pistol'
	if (search_status != -1)
	{
		return pistol;								//if pistol is found, return its corresponding value
	}
	search_status = string_search(command, A);					//search for 'attendant'
	if (search_status != -1)
	{
		return attendant;							//if attendant is found, return its corresponding value
	}
	search_status = string_search(command, I);					//search for 'inventory'
	if (search_status != -1)
	{
		return inventory;							//if inventory is found, return its corresponding value
	}
	search_status = string_search(command, D);					//search for 'debris'
	if (search_status != -1)
	{
		return debris;								//if debris is found, return its corresponding value
	}
	search_status = string_search(command, S);					//search for 'search'
	if (search_status != -1)
	{
		return search;								//if search is found, return its corresponding value
	}
	if (search_status == -1)									//user input not found				
		return -1;									//return value signifying no match
}

help_func(void)											//used to display helpful information to the user
{
	printf("\n\n\n__________________________________________________________________\n");
	printf("\nThe game works based on directional commands such as:\n\n\t'North',\n\t'East',\n\t'South', and\n\t'West'\n\nThere are also other recognized words such as:\n\n\t'Search' and \n\t'Inventory'\n\nAnd there are situational words:\n\n\tYou'll have to think hard!!\n\n" );
	printf("__________________________________________________________________\n\n\n");
}

delay(void)												//used to create delay for dramatic effect
{
	for (int i = 1; i <= 32000; i++)						// creates delay
	{
		for (int j = 1; j <= 32000; j++)
		{
		}
	}
}

inventory_func(int *flare, int *gun, int *keys, int *shelt_srch, int *cv_srch)   //takes pointers to all relevant data and displays user's current inventory based on each varible's value
{
	printf("\n\n____________________________________________\n");

	printf("\n\tCompass");													//if user has found compass
	
	if (*keys > 0)															//if user has found keys
	{
		printf("\t\t|\tKeys");
	}
	if (*gun > 0)															//if user has found pistol (gun)
	{
		printf("\n\n\tPistol");
	}
	if (*flare > 0)															//if user has found flare
	{
		if (*gun > 0)
		{
			printf("\t\t|\tFlare");
		}
		else
		{
			printf("\n\tFlare");
		}
	}
	if (*shelt_srch > 0)													//if user has killed the wolves
	{
		printf("\n\n\tWolf hide");
	}
	if (*cv_srch > 0)														//if user has killed the bear
	{
		if (*shelt_srch > 0)
		{
			printf("\t|\tBear skin");
		}
		else
		{
			printf("\n\n\tBear skin");
		}
	}
	printf("\n\n____________________________________________\n\n\n");
}
