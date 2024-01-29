#include <iostream>
#include <time.h>

using namespace std;

enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_TYPE
{
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

#define	NAME_SIZE	32
#define	ITEM_DESC_LENGTH	512
#define	INVENTORY_MAX		20
#define	STORE_WEAPON_MAX	3
#define	STORE_ARMOR_MAX		3
#define	LEVEL_MAX			10

struct _tagItem
{
	char	strName[NAME_SIZE];
	char	strTypeName[NAME_SIZE];
	ITEM_TYPE	eType;
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory
{
	_tagItem	tItem[INVENTORY_MAX];
	int			iItemCount;
	int			iGold;
};

struct _tagPlayer
{
	char	strName[NAME_SIZE];
	char	strJobName[NAME_SIZE];
	JOB		eJob;
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iLevel;
	_tagItem	tEquip[EQ_MAX];
	bool		bEquip[EQ_MAX];
	_tagInventory	tInventory;
};

struct _tagMonster
{
	char	strName[NAME_SIZE];
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp; // Exp you get once you defeat the monster
	int		iGoldMin;
	int		iGoldMax;
};

struct _tagLevelUpStatus
{
	int	iAttackMin;
	int	iAttackMax;
	int	iArmorMin;
	int	iArmorMax;
	int	iHPMin;
	int	iHPMax;
	int	iMPMin;
	int	iMPMax;
};

int main()
{
	srand((unsigned int)time(0));
    
    // Exp list that you need to level up
	const int	iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000
	, 100000, 150000, 200000, 400000 };

	_tagLevelUpStatus	tLvUpTable[JOB_END - 1] = {};

	tLvUpTable[JOB_KNIGHT - 1].iAttackMin = 4;
	tLvUpTable[JOB_KNIGHT - 1].iAttackMax = 10;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMin = 8;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMax = 16;
	tLvUpTable[JOB_KNIGHT - 1].iHPMin = 50;
	tLvUpTable[JOB_KNIGHT - 1].iHPMax = 100;
	tLvUpTable[JOB_KNIGHT - 1].iMPMin = 10;
	tLvUpTable[JOB_KNIGHT - 1].iMPMax = 20;

	tLvUpTable[JOB_ARCHER - 1].iAttackMin = 10;
	tLvUpTable[JOB_ARCHER - 1].iAttackMax = 15;
	tLvUpTable[JOB_ARCHER - 1].iArmorMin = 5;
	tLvUpTable[JOB_ARCHER - 1].iArmorMax = 10;
	tLvUpTable[JOB_ARCHER - 1].iHPMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iHPMax = 60;
	tLvUpTable[JOB_ARCHER - 1].iMPMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iMPMax = 50;

	tLvUpTable[JOB_WIZARD - 1].iAttackMin = 15;
	tLvUpTable[JOB_WIZARD - 1].iAttackMax = 20;
	tLvUpTable[JOB_WIZARD - 1].iArmorMin = 3;
	tLvUpTable[JOB_WIZARD - 1].iArmorMax = 7;
	tLvUpTable[JOB_WIZARD - 1].iHPMin = 20;
	tLvUpTable[JOB_WIZARD - 1].iHPMax = 40;
	tLvUpTable[JOB_WIZARD - 1].iMPMin = 50;
	tLvUpTable[JOB_WIZARD - 1].iMPMax = 100;

    // Set the player info when you start
	_tagPlayer	tPlayer = {};

    // Player name
	cout << "Name : ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1); // null space

	int	iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		system("cls");
		cout << "1. Knight" << endl;
		cout << "2. Archer" << endl;
		cout << "3. Wizard" << endl;
		cout << "Please choose your job : ";
		cin >> iJob;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		else if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}



	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.iGold = 10000;

	switch (tPlayer.eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "Knight");
		tPlayer.iAttackMin = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iArmorMin = 15;
		tPlayer.iArmorMax = 20;
		tPlayer.iHPMax = 500;
		tPlayer.iHP = 500;
		tPlayer.iMP = 100;
		tPlayer.iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "Archer");
		tPlayer.iAttackMin = 10;
		tPlayer.iAttackMax = 15;
		tPlayer.iArmorMin = 10;
		tPlayer.iArmorMax = 15;
		tPlayer.iHPMax = 400;
		tPlayer.iHP = 400;
		tPlayer.iMP = 200;
		tPlayer.iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "Wizard");
		tPlayer.iAttackMin = 15;
		tPlayer.iAttackMax = 20;
		tPlayer.iArmorMin = 5;
		tPlayer.iArmorMax = 10;
		tPlayer.iHPMax = 300;
		tPlayer.iHP = 300;
		tPlayer.iMP = 300;
		tPlayer.iMPMax = 300;
		break;
	}

	// Create the monster.
	_tagMonster	tMonsterArr[MT_BACK - 1] = {};

	// Create a goblin
	strcpy_s(tMonsterArr[0].strName, "Goblin");
	tMonsterArr[0].iAttackMin = 20;
	tMonsterArr[0].iAttackMax = 30;
	tMonsterArr[0].iArmorMin = 2;
	tMonsterArr[0].iArmorMax = 5;
	tMonsterArr[0].iHP = 100;
	tMonsterArr[0].iHPMax = 100;
	tMonsterArr[0].iMP = 10;
	tMonsterArr[0].iMPMax = 10;
	tMonsterArr[0].iLevel = 1;
	tMonsterArr[0].iExp = 1000;
	tMonsterArr[0].iGoldMin = 500;
	tMonsterArr[0].iGoldMax = 1500;

	// Create a bear
	strcpy_s(tMonsterArr[1].strName, "Bear");
	tMonsterArr[1].iAttackMin = 80;
	tMonsterArr[1].iAttackMax = 130;
	tMonsterArr[1].iArmorMin = 60;
	tMonsterArr[1].iArmorMax = 90;
	tMonsterArr[1].iHP = 2000;
	tMonsterArr[1].iHPMax = 2000;
	tMonsterArr[1].iMP = 100;
	tMonsterArr[1].iMPMax = 100;
	tMonsterArr[1].iLevel = 5;
	tMonsterArr[1].iExp = 7000;
	tMonsterArr[1].iGoldMin = 6000;
	tMonsterArr[1].iGoldMax = 8000;

	// Create a dragon
	strcpy_s(tMonsterArr[2].strName, "Dragon");
	tMonsterArr[2].iAttackMin = 250;
	tMonsterArr[2].iAttackMax = 500;
	tMonsterArr[2].iArmorMin = 200;
	tMonsterArr[2].iArmorMax = 400;
	tMonsterArr[2].iHP = 30000;
	tMonsterArr[2].iHPMax = 30000;
	tMonsterArr[2].iMP = 20000;
	tMonsterArr[2].iMPMax = 20000;
	tMonsterArr[2].iLevel = 10;
	tMonsterArr[2].iExp = 30000;
	tMonsterArr[2].iGoldMin = 20000;
	tMonsterArr[2].iGoldMax = 50000;

	// Create an item list that will be on the store.
	_tagItem	tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreArmor[STORE_ARMOR_MAX] = {};

	/*
	char	strName[NAME_SIZE];
	char	strTypeName[NAME_SIZE];
	ITEM_TYPE	eType;
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
	*/

	// Set weapons info.
	// ================ Weapon 1 =================
	strcpy_s(tStoreWeapon[0].strName, "Knife");
	strcpy_s(tStoreWeapon[0].strTypeName, "Weapon");
	strcpy_s(tStoreWeapon[0].strDesc, "A simple knife");
	tStoreWeapon[0].eType = IT_WEAPON;
	tStoreWeapon[0].iMin = 5;
	tStoreWeapon[0].iMax = 10;
	tStoreWeapon[0].iPrice = 1000;
	tStoreWeapon[0].iSell = 500;

    // ================ Weapon 2 =================
	strcpy_s(tStoreWeapon[1].strName, "Sword");
	strcpy_s(tStoreWeapon[1].strTypeName, "Weapon");
	strcpy_s(tStoreWeapon[1].strDesc, "A normal sword");
	tStoreWeapon[1].eType = IT_WEAPON;
	tStoreWeapon[1].iMin = 20;
	tStoreWeapon[1].iMax = 40;
	tStoreWeapon[1].iPrice = 7000;
	tStoreWeapon[1].iSell = 3500;

    // ================ Weapon 3 =================
	strcpy_s(tStoreWeapon[2].strName, "Iron Sword");
	strcpy_s(tStoreWeapon[2].strTypeName, "Weapon");
	strcpy_s(tStoreWeapon[2].strDesc, "A sword made of Iron");
	tStoreWeapon[2].eType = IT_WEAPON;
	tStoreWeapon[2].iMin = 90;
	tStoreWeapon[2].iMax = 150;
	tStoreWeapon[2].iPrice = 30000;
	tStoreWeapon[2].iSell = 15000;

	// ================ Armor 1 =================
	strcpy_s(tStoreArmor[0].strName, "Leather Armor");
	strcpy_s(tStoreArmor[0].strTypeName, "Armor");
	strcpy_s(tStoreArmor[0].strDesc, "Armor made of Leather");
	tStoreArmor[0].eType = IT_ARMOR;
	tStoreArmor[0].iMin = 2;
	tStoreArmor[0].iMax = 5;
	tStoreArmor[0].iPrice = 1000;
	tStoreArmor[0].iSell = 500;

    // ================ Armor 2 =================
	strcpy_s(tStoreArmor[1].strName, "Stone Armor");
	strcpy_s(tStoreArmor[1].strTypeName, "Armor");
	strcpy_s(tStoreArmor[1].strDesc, "Armor made of Stone");
	tStoreArmor[1].eType = IT_ARMOR;
	tStoreArmor[1].iMin = 10;
	tStoreArmor[1].iMax = 20;
	tStoreArmor[1].iPrice = 7000;
	tStoreArmor[1].iSell = 3500;

    // ================ Armor 3 =================
	strcpy_s(tStoreArmor[2].strName, "Iron Armor");
	strcpy_s(tStoreArmor[2].strTypeName, "Armor");
	strcpy_s(tStoreArmor[2].strDesc, "Armor made of Iron");
	tStoreArmor[2].eType = IT_ARMOR;
	tStoreArmor[2].iMin = 70;
	tStoreArmor[2].iMax = 90;
	tStoreArmor[2].iPrice = 30000;
	tStoreArmor[2].iSell = 15000;


	while (true)
	{
		system("cls");
		cout << "*************************** Menu ***************************" << endl;
		cout << "1. Map�" << endl;
		cout << "2. Store " << endl;
		cout << "3. Inventory " << endl;
		cout << "4. Exit " << endl;
		cout << "Please select a menu : ";
		int	iMenu;
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_MAP:
	while (true)
		{
			system("cls");
			cout << "************************* Level *************************" << endl;
			cout << "1. Easy" << endl;
			cout << "2. Normal" << endl;
			cout << "3. Hard" << endl;
			cout << "4. Back" << endl;
			cout << "Please choose a map : ";
			cin >> iMenu;

	if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

	if (iMenu == MT_BACK)
			break;

	_tagMonster	tMonster = tMonsterArr[iMenu - 1];

		while (true)
	{
		system("cls");
		switch (iMenu)
	{
		case MT_EASY:
			cout << "************************* Easy *************************" << endl;
			break;
			case MT_NORMAL:
				cout << "************************* Normal *************************" << endl;
				break;
				case MT_HARD:
				cout << "************************* Hard *************************" << endl;
				break;
	}

		// Player info.
	cout << "================== Player ==================" << endl;
	cout << "Name : " << tPlayer.strName << "\tJob : " <<
		tPlayer.strJobName << endl;
	cout << "Level : " << tPlayer.iLevel << "\tExp : " <<
		tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;

		// Increase attack when equipping the weapon.
			if (tPlayer.bEquip[EQ_WEAPON] == true)
				{
			cout << "Attack : " << tPlayer.iAttackMin << " + " <<
			tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
			tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
					}

			else
					{
			cout << " Attack : " << tPlayer.iAttackMin << " - " <<
				tPlayer.iAttackMax;
					}

			if (tPlayer.bEquip[EQ_ARMOR] == true)
					{
			cout << "Armor : " << tPlayer.iArmorMin << " + " <<
			tPlayer.tEquip[EQ_ARMOR].iMin << " - " <<
			tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
					}

			else
					{
				cout << "Armor : " << tPlayer.iArmorMin << " - " <<
				tPlayer.iArmorMax << endl;
					}

				cout << "HP : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
				"\tMP : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

			if (tPlayer.bEquip[EQ_WEAPON])
				cout << "\tEquipped Weapon : " << tPlayer.tEquip[EQ_WEAPON].strName;

			else
				cout << "Equipped Weapon : None";

			if (tPlayer.bEquip[EQ_ARMOR])
				cout << "Equipped Armor : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;

			else
				cout << "\tEqupped Armor : None" << endl;

				cout << "Gold : " << tPlayer.tInventory.iGold << " Gold" << endl << endl;

		// Monster info.
			cout << "================== Monster ==================" << endl;
			cout << "Name : " << tMonster.strName << "\tLevel : " <<
			tPlayer.iLevel << endl;
			cout << "Attack : " << tMonster.iAttackMin << " - " <<
			tMonster.iAttackMax << "\tArmor : " << tMonster.iArmorMin <<
			" - " << tMonster.iArmorMax << endl;
			cout << "HP : " << tMonster.iHP << " / " << tMonster.iHPMax <<
			"\tMP : " << tMonster.iMP << " / " << tMonster.iMPMax << endl;
			cout << "Gained Exp : " << tMonster.iExp << "\tGained Gold : " <<
			tMonster.iGoldMin << " - " << tMonster.iGoldMax << endl << endl;

			cout << "1. Attack" << endl;
			cout << "2. Run away" << endl;
			cout << "Please select your next move : ";
			cin >> iMenu;

			if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		else if (iMenu == BATTLE_BACK)
			break;

		switch (iMenu)
					{
		case BATTLE_ATTACK:
					{
			int	iAttackMin = tPlayer.iAttackMin;
			int	iAttackMax = tPlayer.iAttackMax;

			if (tPlayer.bEquip[EQ_WEAPON])
				{
				iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMin;
				iAttackMax += tPlayer.tEquip[EQ_WEAPON].iMax;
				}

			int	iAttack = rand() % (iAttackMax - iAttackMin + 1) +
			iAttackMin;
			int	iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) +
			tMonster.iArmorMin;

			int	iDamage = iAttack - iArmor;
                        
		//if (iDamage < 1)
		//	iDamage = 1;
			iDamage = iDamage < 1 ? 1 : iDamage;

		// Decrease Monster's HP.
			tMonster.iHP -= iDamage;

			cout << tPlayer.strName << " attacked " << tMonster.strName <<
			" and caused " << iDamage << " damages!" << endl;

		// Clear the monster.
			if (tMonster.iHP <= 0)
		{
			cout << tMonster.strName << " Has died!" << endl;

			tPlayer.iExp += tMonster.iExp;
			int	iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) +
			tMonster.iGoldMin);
			tPlayer.tInventory.iGold += iGold;

			cout << "You earned " << tMonster.iExp << " Exp." << endl;
			cout << "You earned " << iGold << " Golds." << endl;

			tMonster.iHP = tMonster.iHPMax;
			tMonster.iMP = tMonster.iMPMax;

			// Level Up checking.
			if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1])
		{
			// Deduct Exp when died.
			tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];

			// Level increase.
			++tPlayer.iLevel;

			cout << "Level Up!" << endl;

			int	iJobIndex = tPlayer.eJob - 1;
			int	iHPUp = rand() % (tLvUpTable[iJobIndex].iHPMax - tLvUpTable[iJobIndex].iHPMin + 1) +
				tLvUpTable[iJobIndex].iHPMin;
			int	iMPUp = rand() % (tLvUpTable[iJobIndex].iMPMax - tLvUpTable[iJobIndex].iMPMin + 1) +
				tLvUpTable[iJobIndex].iMPMin;

			tPlayer.iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
			tPlayer.iAttackMax += tLvUpTable[iJobIndex].iAttackMax;
			tPlayer.iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
			tPlayer.iArmorMax += tLvUpTable[iJobIndex].iArmorMax;

			tPlayer.iHPMax += iHPUp;
			tPlayer.iMPMax += iMPUp;
                                
			tPlayer.iHP = tPlayer.iHPMax;
			tPlayer.iMP = tPlayer.iMPMax;
		}

			system("pause");
			break;
		}

			// Attack Player if monster is alive.
		iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) +
			tMonster.iAttackMin;

		int	iArmorMin = tPlayer.iArmorMin;
		int	iArmorMax = tPlayer.iArmorMax;

		if (tPlayer.bEquip[EQ_ARMOR])
			{
			iArmorMin += tPlayer.tEquip[EQ_ARMOR].iMin;
			iArmorMax += tPlayer.tEquip[EQ_ARMOR].iMax;
			}

		iArmor = rand() % (iArmorMax - iArmorMin + 1) + iArmorMin;

		iDamage = iAttack - iArmor;
                        
		//if (iDamage < 1)
		//	iDamage = 1;
		iDamage = iDamage < 1 ? 1 : iDamage;

		// Player HP decrease
		tPlayer.iHP -= iDamage;

		cout << tMonster.strName << " attacked " << tPlayer.strName <<
				"and caused " << iDamage << " damages!" << endl;

		// When Player died
		if (tPlayer.iHP <= 0)
	{
		cout << tPlayer.strName << "Has died!." << endl;

		int	iExp = tPlayer.iExp * 0.1f;
		int	iGold = tPlayer.tInventory.iGold * 0.1f;

		tPlayer.iExp -= iExp;
		tPlayer.tInventory.iGold -= iGold;

		cout << "You just lost " << iExp << " Exp." << endl;
		cout << "You just lost " << iGold << " Golds." << endl;

		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMP = tPlayer.iMPMax;
						}

		system("pause");
					}
			break;
					}

				}
			}
			break;
		case MM_STORE:
			while (true)
			{
				system("cls");
				cout << "************************* Store *************************" << endl;
				cout << "1. Weapon" << endl;
				cout << "2. Armor" << endl;
				cout << "3. Back" << endl;
				cout << "Please select the menu : ";
				cin >> iMenu;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (iMenu == SM_BACK)
					break;

				switch (iMenu)
				{
				case SM_WEAPON:
		while (true)
					{
			system("cls");

			cout << "************************ Weapon ************************" << endl;
	// Show the list
			for (int i = 0; i < STORE_WEAPON_MAX; ++i)
						{
			cout << i + 1 << ". Name : " << tStoreWeapon[i].strName <<
			"\tType : " << tStoreWeapon[i].strTypeName << endl;
			cout << "Attack : " << tStoreWeapon[i].iMin << " - " <<
			tStoreWeapon[i].iMax << endl;
			cout << "Sell Price : " << tStoreWeapon[i].iPrice <<
			"\tPrice : " << tStoreWeapon[i].iSell << endl;
			cout << "Description : " << tStoreWeapon[i].strDesc << endl << endl;
						}

			cout << STORE_WEAPON_MAX + 1 << ". Back" << endl;
			cout << "Budget : " << tPlayer.tInventory.iGold << " Gold" << endl;
			cout << "Left Space : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
			cout << "Please select the item : ";
			cin >> iMenu;

			if (cin.fail())
						{
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
						}

			else if (iMenu == STORE_WEAPON_MAX + 1)
				break;

			else if (iMenu < 1 || iMenu > STORE_WEAPON_MAX + 1)
						{
				cout << "Wrong selection." << endl;
				system("pause");
				continue;
						}
                        
			int	iWeaponIndex = iMenu - 1;

	// Check if the inventory is full.
			if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
				cout << "Your inventory is full." << endl;
				system("pause");
				continue;
						}

	// not enough money
			else if (tPlayer.tInventory.iGold < tStoreWeapon[iWeaponIndex].iPrice)
						{
				cout << "You don't have enough golds." << endl;
				system("pause");
				continue;
						}

						
		tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
		tStoreWeapon[iWeaponIndex];
		++tPlayer.tInventory.iItemCount;

		// deduct golds
		tPlayer.tInventory.iGold -= tStoreWeapon[iWeaponIndex].iPrice;

		cout << " You purchased " << tStoreWeapon[iWeaponIndex].strName << endl;
		system("pause");
					}
		break;
		case SM_ARMOR:
			while (true)
					{
			system("cls");

			cout << "************************* Armor *************************" << endl;
	// Show the list
			for (int i = 0; i < STORE_ARMOR_MAX; ++i)
						{
			cout << i + 1 << ".Name : " << tStoreArmor[i].strName <<
			"\tType : " << tStoreArmor[i].strTypeName << endl;
			cout << "Defend : " << tStoreArmor[i].iMin << " - " <<
			tStoreArmor[i].iMax << endl;
			cout << "Sell Price : " << tStoreArmor[i].iPrice <<
			"\tPrice : " << tStoreArmor[i].iSell << endl;
			cout << "Description : " << tStoreArmor[i].strDesc << endl << endl;
						}

			cout << STORE_ARMOR_MAX + 1 << ". Back" << endl;
			cout << "Budget : " << tPlayer.tInventory.iGold << " Gold" << endl;
			cout << "Left Space : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
			cout << "Please select the item : ";
			cin >> iMenu;

			if (cin.fail())
						{
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
						}

			else if (iMenu == STORE_ARMOR_MAX + 1)
				break;

			else if (iMenu < 1 || iMenu > STORE_ARMOR_MAX + 1)
						{
				cout << "Wrong selection." << endl;
				system("pause");
				continue;
						}

			int	iArmorIndex = iMenu - 1;

			if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
				cout << "Your inventory is full." << endl;
				system("pause");
				continue;
						}

			else if (tPlayer.tInventory.iGold < tStoreArmor[iArmorIndex].iPrice)
						{
				cout << "You don't have enough golds." << endl;
				system("pause");
				continue;
						}

			tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
				tStoreArmor[iArmorIndex];
			++tPlayer.tInventory.iItemCount;

			tPlayer.tInventory.iGold -= tStoreArmor[iArmorIndex].iPrice;

			cout << "You purchased " << tStoreArmor[iArmorIndex].strName << endl;
			system("pause");
					}
			break;
				}
			}
			break;
		case MM_INVENTORY:
			while (true)
			{
				system("cls");
				cout << "*********************** Inventory ***********************" << endl;
				cout << "================== Player ==================" << endl;
				cout << "Name : " << tPlayer.strName << "\tJob : " <<
					tPlayer.strJobName << endl;
				cout << "Level : " << tPlayer.iLevel << "\tExp : " <<
					tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;

				// Increase the attack when equipped the weapon
				if (tPlayer.bEquip[EQ_WEAPON] == true)
				{
					cout << "Attack: " << tPlayer.iAttackMin << " + " <<
						tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
						tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
				}

				else
				{
					cout << "Attack : " << tPlayer.iAttackMin << " - " <<
						tPlayer.iAttackMax;
				}

				// Increase the armor when equipped.
				if (tPlayer.bEquip[EQ_ARMOR] == true)
				{
					cout << "\tArmor : " << tPlayer.iArmorMin << " + " <<
						tPlayer.tEquip[EQ_ARMOR].iMin << " - " <<
						tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
				}

				else
				{
					cout << "\tArmor : " << tPlayer.iArmorMin << " - " <<
						tPlayer.iArmorMax << endl;
				}

				cout << "HP : " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
					"\tMP : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

				if (tPlayer.bEquip[EQ_WEAPON])
					cout << "Equipped Weapon : " << tPlayer.tEquip[EQ_WEAPON].strName;

				else
					cout << "Equipped Weapon: None";

				if (tPlayer.bEquip[EQ_ARMOR])
					cout << "\tEquipped Armor: " << tPlayer.tEquip[EQ_ARMOR].strName << endl;

				else
					cout << "\tEquipped Armor : None" << endl;

				cout << "Budget : " << tPlayer.tInventory.iGold << " Gold" << endl << endl;

				for (int i = 0; i < tPlayer.tInventory.iItemCount; ++i)
				{
					cout << i + 1 << ". Name : " << tPlayer.tInventory.tItem[i].strName <<
						"\tType : " << tPlayer.tInventory.tItem[i].strTypeName << endl;
					cout << "Attack/Armor : " << tPlayer.tInventory.tItem[i].iMin << " - " <<
						tPlayer.tInventory.tItem[i].iMax << endl;
					cout << "Sell Price : " << tPlayer.tInventory.tItem[i].iPrice <<
						"\tBuy Price : " << tPlayer.tInventory.tItem[i].iSell << endl;
					cout << "Description : " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
				}

				cout << tPlayer.tInventory.iItemCount + 1 << ". Back" << endl;
				cout << "Please select the item : ";
				cin >> iMenu;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (iMenu == tPlayer.tInventory.iItemCount + 1)
					break;

				else if (iMenu < 1 || iMenu > tPlayer.tInventory.iItemCount + 1)
				{
					cout << "Wrong selection." << endl;
					system("pause");
					continue;
				}

				// Find the item index.
				int	idx = iMenu - 1;

				EQUIP	eq;

				switch (tPlayer.tInventory.tItem[idx].eType)
				{
				case IT_WEAPON:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				}

				if (tPlayer.bEquip[eq] == true)
				{
					_tagItem	tSwap = tPlayer.tEquip[eq];
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					tPlayer.tInventory.tItem[idx] = tSwap;
				}


				else
				{
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];

					for (int i = idx; i < tPlayer.tInventory.iItemCount - 1; ++i)
					{
						tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i + 1];
					}

					--tPlayer.tInventory.iItemCount;

					// make true bc equipped.
					tPlayer.bEquip[eq] = true;
				}

				cout << tPlayer.tEquip[eq].strName << " You equipped the item." << endl;

				system("pause");
			}
			break;
		default:
			cout << "Wrong selection." << endl;
			break;
		}
	}

	return 0;
}