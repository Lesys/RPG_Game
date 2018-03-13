// Include all files
#include "../include/fonction.h"

char menu_choices[NB_CHOICES_POSSIBLE][LENGTH_MAX_MENU_CHOICE] = {"Continue", "Create a new character", "Leave"};

int main(int argc, char* argv[]) {
	int menu_chose = -1, i = 0;
	Character* c = NULL;

	printf("Welcome to the RPG console mode\nHere are your choices:\n");

	while (menu_chose != NB_CHOICES_POSSIBLE) { // Means while user is not leaving
		menu_chose = -1;

		putchar('\n');

		while (menu_chose < 1 || menu_chose > NB_CHOICES_POSSIBLE) {
			for (i = 1; i <= NB_CHOICES_POSSIBLE; i++)
				printf("%d) %s\n", i, menu_choices[i - 1]);
			scanf("%d", &menu_chose);
		}

		printf("So you chose to %s\n", menu_choices[menu_chose - 1]);

		switch(menu_chose) { // Different possibilities
			case 1: printf("Continuing (not implemented)\n"); // Continue with a character already existing
				break;
			case 2: menu_chose = -1; // Creating a new character
				while (menu_chose < 1 || menu_chose > 3) {
					printf("New creation:\n1) New character\n2) Copy a character\n3) Cancel\n");
					scanf("%d", &menu_chose);
				}

				if (menu_chose != 3) {

					if (menu_chose == 2) { // Duplicate a character
						printf("Which one you want to copy?? (not implemented)\n");
					}

					// Copying if said to, else sending NULL (== starting a character from lvl 1)
					if ((c = CreateCharacter(c))) { // If everything is good (return an adress)
						DisplayCharacter(c);
						FreeCharacter(c);
					}
					else // Return NULL
						printf("The character has not been created\n");
				}
				else
					printf("Cancelling\n");

				break;
			case 3: break; // Just leaving
			default: Error(10); // OOB
				break;
		}
		// To continue, there have to be a file not empty
	}

	printf("\nBye bye\n");

	return 0;
}