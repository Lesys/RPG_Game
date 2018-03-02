// This will be a character
typedef struct  {
	char* name; // Name of the character
	int type, lvl; // Type (class) and level of the character
	int hp, hp_max; // Amout of current HP (Health Point) and Maximum HP
	int mp, mp_max; // Amout of current MP (Mana Point) and Maximum MP
	int str, intel, def, def_mag; // Current stats
	// (Strength == Physical attack, Intelligence == Magic attacks, Defense == Physical Defense, Magical defense)
} Character;

// Monsters don't have lvl, they have variance in their stats

// This will be a basic monster
typedef struct {
	char* name; // Name of the monster
	int hp, hp_max; // Amout of current HP (Health Point) and Maximum HP
} Monster;

// This will be boss
// Boss has stats too, but no mana (== infinite mana)
typedef struct {
	char* name; // Name of the monster
	int hp, hp_max; // Amout of current HP (Health Point) and Maximum HP
	int str, intel, def, def_mag; // Current stats
} Boss;