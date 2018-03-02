#define NB_CHARACTER_POSSIBLE 3
#define LENGTH_MAX_NAME_CHARACTER 10
#define LENGTH_MAX_NICKNAME_CHARACTER 20
#define NAME_FILE_CHARACTER_SAVE "character_save.sav"

Character* CreateCharacter(Character*);
Character* CopyCharacter(Character* c_org, Character* c_cpy);
Character* NewCharacter(Character*);
Character* CreatingCharacter(int, Character*);
Character* ImplementStats(Character* c, int str, int intel, int def, int def_mag, int hp_max, int mp_max, int type);
void DisplayCharacter(Character*);
int SaveCharacter(Character*);