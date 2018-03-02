// Include all files
#include "../include/fonction.h"

char menu_choices[NB_CHOICES_POSSIBLE][LENGTH_MAX_MENU_CHOICE] = {"Continue", "Create a new character", "Leave"};

int main(int argc, char* argv[]) {
	int menu_chose = -1, i = 0;
	printf("Welcome to the RPG console mode\nHere are your choices:\n");

	while (menu_chose != NB_CHOICES_POSSIBLE) { // Means while user is not leaving
		menu_chose = -1;

		putchar('\n');

		while (menu_chose < 1 || menu_chose > NB_CHOICES_POSSIBLE) {
			for (i = 1; i <= NB_CHOICES_POSSIBLE; i++)
				printf("%d) %s\n", i, menu_choices[i - 1]);
			scanf("%d", &menu_chose);
		}

		printf("So you chose to %s\n", menu_choices[menu_chose]);

		switch(menu_chose) {
			case 1: printf("Continuing (not implemented\n");
				break;
			case 2: menu_chose = -1;
				while (menu_chose < 1 || menu_chose > 3) {
					printf("New creation:\n1) New character\n2) Copy a character\n3) Cancel\n");
					scanf("%d", &menu_chose);
				}

				if (menu_chose != 3) {
					Character* c = NULL;

					if (menu_chose == 2) {
						printf("Which one you want to copy?? (not implemented)");
					}

					if (CreateCharacter(c)) // Copying if said to, else sending NULL
						printf("The character has not been created\n");
					else
						DisplayCharacter(c);
				}
				else
					printf("Cancelling\n");

				break;
			default: printf("The choice is not wanted\n");
		}
		// To continue, there have to be a file not empty
	}

	printf("\nBye bye\n");

	return 0;
}