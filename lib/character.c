#include "../include/fonction.h"

char characters[NB_CHARACTER_POSSIBLE][LENGTH_MAX_NAME_CHARACTER] = {"Warrior", "Wizard", "Paladin"};
char* character_sheet = "character_sheet.sav";

// Create a new character (if a character is in parameter, copy this one. else, create a new one)
Character* CreateCharacter(Character* c) {
	Character* c_new = InitCharacter();

	if (c) { // If the pointer is not NULL ==> Copy the character in the new one
		c_new = CopyCharacter(c, c_new);
	}
	else { // Create new character
		c_new = NewCharacter(c_new);
	}

	if (c_new) { // The character is correctly created (or not canceled)
		DisplayCharacter(c_new);

		if (SaveCharacter(c_new))
			c_new = NULL;
	}

	return c_new;
}
/*
	char* name; // Name of the character
	int hp, hp_max; // Amout of current HP (Health Point) and Maximum HP
	int mp, mp_max; // Amout of current MP (Mana Point) and Maximum MP
	int str, intel, def, def_mag; // Current stats*/

// Copy c_org in c_cpy and return c_cpy
Character* CopyCharacter(Character* c_org, Character* c_cpy) {
	
	if (c_org && c_cpy) { // If both are not NULL
		strcpy(c_org->name, c_cpy->name); // Copy the name

		// Copy the level and type
		c_cpy->lvl = c_org->lvl;
		c_cpy->type = c_org->type;

		// Copy HP & MP
		c_cpy->hp_max = c_org->hp_max;
		c_cpy->mp_max = c_org->mp_max;
		c_cpy->hp = c_cpy->hp_max;
		c_cpy->mp = c_cpy->mp_max;

		// Copy stats
		c_cpy->str = c_org->str;
		c_cpy->intel = c_org->intel;
		c_cpy->def = c_org->def;
		c_cpy->def_mag = c_org->def_mag;
	}
	else
		Error(1);

	return c_cpy; // Return NULL if was NULL, else new Character pasted
}

// Confirming the new character and the class
Character* NewCharacter(Character* c) {
	int i, num_char;

	printf("New possible characters:\n");
	for (i = 1; i <= NB_CHARACTER_POSSIBLE; i++)
		printf("%d°) %s\n", i, characters[i - 1]);

	// User input for his choice
	printf("\nYour choice: ");
	scanf("%d", &num_char);

	while (num_char < 0 || num_char > NB_CHARACTER_POSSIBLE + 1) { // While the choice is not possible
		printf("\nYou have to choose a number between 0 and %d included, 0 stop the creation\n", NB_CHARACTER_POSSIBLE);
		printf("\nYour choice: ");
		scanf("%d", &num_char);
	}

	num_char--;

	if (num_char == -1) { // Stopping the creation
		printf("You stopped the creation\n");
		c = NULL;
	}
	else { // Creating the new character
		printf("So you took the %s, well done.\nNow creating the character...\n", characters[num_char]);
		c = CreatingCharacter(num_char, c);
	}

	return c;
}

// Creating the character from 0 matching with the class he choses
Character* CreatingCharacter(int num_char, Character* c) {
	if (c) {
		c->lvl = 1;

		if (num_char == 0) // If warrior
			c = ImplementStats(c, 15, 3, 10, 5, 50, 10, num_char);
		else if (num_char == 1) // If wizard
			c = ImplementStats(c, 2, 17, 4, 13, 35, 35, num_char);
		else if (num_char == 2) // If paladin
			c = ImplementStats(c, 9, 7, 19, 18, 75, 20, num_char);
		else // If out of bounds
			Error(10);
	}
	else
		Error(1);

	c->lvl = 1; // Starting at level 1

	return c;
}

// Add the stats to the character
Character* ImplementStats(Character* c, int str, int intel, int def, int def_mag, int hp_max, int mp_max, int type) {
	if (c) {
		if (!str || !intel || !def || !def_mag || !hp_max || !mp_max) // If there is 0 on a stat
			Error(3);
		else {
			c->str = str;
			c->intel = intel;
			c->def = def;
			c->def_mag = def_mag;
			c->hp_max = hp_max;
			c->mp_max = mp_max;
			c->hp = c->hp_max;
			c->mp = c->mp_max;
			c->type = type;
		}
	}
	else
		Error(1);

	return c;
}

// Display all stats from the character
// MDF == Magical defense
void DisplayCharacter(Character* c) {
	printf("Here is your character:\n\nNAME: %s\nLVL: %d\nHP: %d/%d, MP: %d/%d\nSTR: %d\nINT: %d\nDEF: %d\nMDF: %d\n",
		c->name, c->lvl, c->hp, c->hp_max, c->mp, c->mp_max,	c->str, c->intel, c->def, c->def_mag);
}

// Asking if the character will be saved
int SaveCharacter(Character* c) {	
	char response = '?';
	int return_fonction = 1;

	while (response != 'Y' && response != 'y') { // Big loop if said NO first then NO again to save it. Leave is saved or deleted
		response = '?'; // Reinitialisation

		while (response != 'Y' && response != 'y' && response != 'N' && response != 'n') {
			printf("Do you want to save the character created? (Y/y:N/n): ");

			while ((response = getchar()) == '\n');
			//scanf("%c", &);
		}

		if (response == 'Y' || response == 'y') {
			printf("Chose a name for your character: ");
			scanf("%s", c->name);

			while (!c->name || IsNameExist(c->name)) { // Check if the name is already in the file
				printf("The name is already used, chose another one: ");
				scanf("%s", c->name);
			}

			printf("Saving the character...\n");

			if (SaveInFile(c))
				printf("The character has been saved succesfully\n");
			else
				Error(2);
		}
		else {
			response = '?'; // Reinitialisation
			while (response != 'Y' && response != 'y' && response != 'N' && response != 'n') {
				printf("The character will not be save. Do you want to continue anyway? (Y/y:N/n): ");
				while ((response = getchar()) == '\n');
			}

			if (response == 'Y' || response == 'y')
				return_fonction = 0;
		}
	}

	return return_fonction;
}

int RestoreFromFile() {
	int return_fonction = 1;
	char* nickname = (char*)malloc(LENGTH_MAX_NICKNAME_CHARACTER * sizeof(char));
	FILE* f_character = fopen(NAME_FILE_CHARACTER_SAVE, "r");

	if (f_character) {
		//int i = 0;
		printf("Which character do you want to restore (write the name): ");
		scanf("%s", nickname);

		fclose(f_character);
	}
	else
		return_fonction = 0;

	return return_fonction;
}

int SaveInFile(Character* c) {
	int return_fonction = 1;

	FILE* f_character = fopen(NAME_FILE_CHARACTER_SAVE, "a"); // Open the file at the end to add the new character

	if (f_character) {
		// Writing the name of the character, the type, lvl, current hp, hp_max, current mp, mp_max, str, int, def and mdf
		fprintf(f_character, "%s:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d\n", c->name, c->type, c->lvl, c->hp, c->hp_max, c->mp, c->mp_max, c->str, c->intel, c->def, c->def_mag);
		fclose(f_character);
	}
	else
		return_fonction = 0;

	return return_fonction;
}

// Searching for a nickname if it exist or not
int IsNameExist(char* name) {
	int return_fonction = 0;
	char* name_in_file = (char*)malloc(sizeof(char) * LENGTH_MAX_NICKNAME_CHARACTER);
	FILE* f_character = fopen(NAME_FILE_CHARACTER_SAVE, "r");

	if (f_character) {
		while (!return_fonction && fscanf(f_character, "%s:", name_in_file)) {
			printf("name_in_file: %s\n", name_in_file);
			if (!strcmp(name, name_in_file)) // If same string
				return_fonction = 1;
		}

		fclose(f_character);
	}
	
	free(name_in_file);

	return return_fonction;
}

// Free a character
void FreeCharacter(Character* c) {
	free(c->name);
	free(c);
}

// Initialize a character
Character* InitCharacter() {
	Character* c = (Character*) malloc(sizeof(Character));
	c->name = (char*) malloc(LENGTH_MAX_NICKNAME_CHARACTER * sizeof(char));

	return c;
}