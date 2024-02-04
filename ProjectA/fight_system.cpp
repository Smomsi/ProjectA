//fightsystem.cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <time.h>
#include <Windows.h>

#include "Classes.h"
#include "fight_system.h"
#include "utility_funtions.h"

#define WAIT 1500
#define MINIWAIT 750


int critChance(int schaden) {
	int chance_number = 0;
	srand(time(NULL));
	chance_number = rand() % 100 + 1;

	if (chance_number <= 20) { // <= 20% Krit Chance
		return schaden * 2;
	}
	else {
		return schaden;
	}
}

int takeDmg(int str, int def) {
	int schaden = 0;

	return schaden = str - def;
}

int heal(int max_hp) {
	// Ausgabe ist der Wert der Geiheilt wirt - Heilungswert , nicht die Aktuelle HP!
	// Z.b MaxHP = 10 dann heal = 3.
	int give_hp = 0;

	return give_hp = max_hp * 0.3;
}

bool doge(Stats_spieler& Player) {
	int chance_number = 0;
	int doge_d = 0; // Für die Defends
	bool doge_try = true;
	doge_d = 1 * Player.get_Defends(); // x * Player.get_Defends() ; x = Multiplayer
	srand(time(NULL));
	chance_number = rand() % 100 + 1;
	
	if (chance_number <= 20 + doge_d) { // <= 20% Doge Chance + Defends
		return doge_try = true;
	}
	else {
		return doge_try = false;
	}
}

void escape(bool escape_try = false) {
	int chance_number = 0;
	srand(time(NULL));
	chance_number = rand() % 100 + 1;

	if (chance_number <= 40) { // <= 40% Doge Chance 
		chainread("\nDu bist Weggelaufen! Wie ein versager...\n");
		escape_try = true;
	}
	else {
		chainread("\nDein Mindset ist zu Confidence um Wegzurennen.\n");
		escape_try = false;
	}
}


void enemyTurn(Stats_enemy& Enemy_fight, Stats_spieler& Player_fight) { // Enemy werte nicht mitgenommen von Fight

	chainread("Pass auf! Der %s GREIFT DICH AN!! Sei Bereit!", Enemy_fight.get_Name());
	printf("\n");
	waitPoint(3);

	if (doge(Player_fight) == true) {
		chainread("\nWHAM!!! KROAS. DU HAST EINFACH DEN ANGRIFF GEDOGE?!? Bist du in der Matrix oder wat?\n");
	}else{
		chainread("\nZAP! BOOM! Du hast %d Schaden bekommen.\n",takeDmg(Enemy_fight.get_Strength(),Player_fight.get_Defends()));
		Player_fight.set_CurrentHp(Player_fight.get_CurrentHp() - takeDmg(Enemy_fight.get_Strength(), Player_fight.get_Defends()));
	}
	Sleep(WAIT);
}

void fightMenu(Stats_spieler& Player_fight, Stats_enemy& Enemy_fight) {
	char ant_kampf;
	bool fm = false;
	bool escape_try = false;
	int crit_temp = 0;

	do {
		if (fm == true) {
			system("CLS");
		}
		fm = false; // <==  Fehlerzug muss immer Rückgängig gemacht werden.
		//system("CLS");
		chainread("\nDu bist dran! Wahle deine Action!\n");
		printf("Dein Status:\n");
		Sleep(MINIWAIT);
		printf("HP: % d / % d", Player_fight.get_CurrentHp(), Player_fight.get_MaxHp());
		Sleep(MINIWAIT);
		printf("\nStr: %d", Player_fight.get_Strength());
		Sleep(MINIWAIT);
		printf("\nDef: %d", Player_fight.get_Defends());
		Sleep(MINIWAIT);
		printf("\nLvl: %d", Player_fight.get_Level());

		chainread("\n[Kampf] | [Heilen] | [Analyse] | [Fliehen]\n");

		ant_kampf = inputChar();
		switch (ant_kampf)
		{
			//==================
			//		Kampf
			//==================
		case'k':
			crit_temp = critChance(Player_fight.get_Strength());
			Enemy_fight.set_HpCurrent(Enemy_fight.get_HpCurrent() - crit_temp);
			if (crit_temp > Player_fight.get_Strength()) {
				chainread("WOW KRASS!! Du hast ein KRITISCHEN SCHADEN gemacht.\n");
				chainread("Du hast -%d Schaden an den Gegner: %s gemacht.\n\n", crit_temp, Enemy_fight.get_Name());
				Sleep(WAIT);
			}
			else {
				chainread("Du hast -%d Schaden an den %s gemacht.\n\n", Player_fight.get_Strength(), Enemy_fight.get_Name());
			}
			Sleep(WAIT);
			break;


			//==================
			//		Heilung
			//==================
		case'h':
			if (Player_fight.get_CurrentHp() == Player_fight.get_MaxHp() && Player_fight.get_CurrentHp() >= Player_fight.get_MaxHp()) {
				chainread("Du kannst dich jetzt nicht Heilen!\n");
				Sleep(WAIT);
				fm = true;
			}
			else {
				Player_fight.set_CurrentHp(Player_fight.get_CurrentHp() + heal(Player_fight.get_MaxHp()));
				chainread("Du hast dich um +%d HP Geheilt.\nAktuelle HP:%d/%d \n", heal(Player_fight.get_MaxHp()), Player_fight.get_CurrentHp(), Player_fight.get_MaxHp());

			}
			break;


			//==================
			//		Analyse
			//==================
		case'a':
			chainread("\nDer %s hat folgende werte, \nHP: %d/%d\nStr: %d\nLvl: %d\n",
				Enemy_fight.get_Name(), Enemy_fight.get_HpCurrent(), Enemy_fight.get_HpMax(), Enemy_fight.get_Strength(), Enemy_fight.get_Level());
			break;


			//==================
			//		Fliehen
			//==================
		case'f':
			waitPoint(3);
			escape(escape_try);
			Sleep(WAIT);
			break;

			//==================
			//		Default
			//==================
		default:
			chainread("Kann es sein, dass du dumm bist oder sowas?\n");
			chainread("-> ");
			waitPoint(3);
			chainread("Ja bin Ich.");
			break;

		}
	} while (fm == true);
}


