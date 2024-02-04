// Classes.cpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <time.h>
#include <Windows.h>

#include "Classes.h"
#include "utility_funtions.h"

#define MAX_MONSTER_NAME 5
// ========================
//		Stats_spieler
// ========================
// Standart Konstruktur
Stats_spieler::Stats_spieler() {
	max_hp = 10;
	current_hp = 10;
	strength = 5;
	defends = 0;
	level = 1;
	exp = 0;
	needexp = 100;
	death = 0;
	tutorial = 0;
	gamefile = 0;
}

// Setter
void Stats_spieler::set_MaxHp(int hpmax) {
	this->max_hp = hpmax;
}
void Stats_spieler::set_CurrentHp(int hpcurrent) {
	this->current_hp = hpcurrent;
}
void Stats_spieler::set_Strength(int str) {
	this->strength = str;
}
void Stats_spieler::set_Defends(int def) {
	this->defends = def;
}
void Stats_spieler::set_Level(int lvl) {
	this->level = lvl;
}
void Stats_spieler::set_Exp(int exp) {
	this->exp = exp;
}
void Stats_spieler::set_NeedExp(int nexp) {
	this->needexp = nexp;
}
void Stats_spieler::set_Death(int tot) {
	this->death = tot;
}
void Stats_spieler::set_Tutorial(int tuto) {
	this->tutorial = tuto;
}
void Stats_spieler::set_Gamefile(int game) {
	this->gamefile = game;
}

//Getter
int Stats_spieler::get_MaxHp() {
	return max_hp;
}
int Stats_spieler::get_CurrentHp() {
	return current_hp;
}
int Stats_spieler::get_Strength() {
	return strength;
}
int Stats_spieler::get_Defends() {
	return defends;
}
int Stats_spieler::get_Level() {
	return level;
}
int Stats_spieler::get_Exp() {
	return exp;
}
int Stats_spieler::get_NeedExp() {
	return needexp;
}
int Stats_spieler::get_Death() {
	return death;
}
int Stats_spieler::get_Tutorial() {
	return tutorial;
}
int Stats_spieler::get_Gamefile() {
	return gamefile;
}

//File Methode - Save & load
void Stats_spieler::load() {
	FILE* datei;
	fopen_s(&datei, "speicherstand.txt", "r");
	if (datei == NULL) {
		printf("Die Datei konnte nicht geöffnet werden.\n");
	}
	else {
		fscanf_s(datei, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &max_hp, &current_hp, &strength, &defends, &level, &exp, &needexp, &death, &tutorial, &gamefile); // scheiß auf den Hinweiß, Funktioniert Trotzdem
		set_MaxHp(max_hp);
		set_CurrentHp(current_hp);
		set_Strength(strength);
		set_Defends(defends);
		set_Level(level);
		fclose(datei);
	}
}

void Stats_spieler::save() {
	FILE* datei;
	fopen_s(&datei, "speicherstand.txt", "w");
	if (datei == NULL) {
		printf("Die Datei konnte nicht geöffnet werden.\n");
	}
	else {
		fprintf(datei, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d", max_hp, current_hp, strength, defends, level, exp, needexp, death, tutorial, gamefile);
		fclose(datei);
	}
}


// ========================
//			Enemy
// ========================


//Standart Konstruktor - Nutzung Testwerten. Später Random werte

Stats_enemy::Stats_enemy() {
	hp_max = 10;
	hp_current = 10;
	strength = 5;
	give_exp = 5;
	level = 1;
	const char* defaultName = "DefaultEnemy";
	strncpy_s(name, defaultName, sizeof(name) - 1);
	name[sizeof(name) - 1] = '\0';
}


//setter
void Stats_enemy::set_HpMax(int hpmax) {
	this->hp_max = hpmax;
}
void Stats_enemy::set_HpCurrent(int hpcurrent) {
	this->hp_current = hpcurrent;
}
void Stats_enemy::set_Strength(int str) {
	this->strength = str;
}
void Stats_enemy::set_Level(int lvl) {
	this->level = lvl;
}
void Stats_enemy::set_GiveExp(int exp) {
	this->give_exp = exp;
}
void Stats_enemy::set_Name(const char* name) {
	strncpy_s(this->name, name, sizeof(this->name) - 1);
	this->name[sizeof(this->name) - 1] = '\0';  // Null-Terminierung sicherstellen
}


//Getter
int Stats_enemy::get_HpMax() {
	return hp_max;
}
int Stats_enemy::get_HpCurrent() {
	return hp_current;
}
int Stats_enemy::get_Strength() {
	return strength;
}
int Stats_enemy::get_Level() {
	return level;
}
int Stats_enemy::get_GiveExp() {
	return give_exp;
}
const char* Stats_enemy::get_Name() const {// Wird nicht in Chainread format ausgegeben

	return name;
}

// Methdoen
void Stats_enemy::generate(Stats_spieler Player) {
	srand(time(NULL));
	int exp = 10; // Exp basiert auf Stärke und HP des Gegners.
	int hp = 0;
	int base_hp = 10;
	float hp_each_lvl = 5.5;
	int str = 0;
	int base_dmg = 2;
	int lvl = 0;
	int rmn = rand() % MAX_MONSTER_NAME; // Random Monster Name

	const char* monster_name[MAX_MONSTER_NAME] = {
		"Wolf",
		"Zombie",
		"Kobold",
		"Demon",
		"Schleim"
	};

	// Gegner Rechnungen, die Werte des Gegners basieren auf dem Level, das er hat.

	lvl = Player.get_Level() + rand() % 4;	// Lvl Unterschied von Max 3! Plvl= 4 ELvl= 3 || 4 || 5 || 6 
	hp = base_hp + lvl * hp_each_lvl;		// Normaler Spieler Schaden bei 5.
	str = ((base_dmg * lvl) + 3) / 5;		// (base_dmg * lvl) + 2 / multiplayer
	exp = (10 * lvl) / 2;					// Geht zwar in 5er Schritten, aber ist akzeptabel

	set_Name(monster_name[rmn]); // Ist das dies ein Produktiver Aufruf? ein Setter innerhalb eine Methode zu nutzen??
	this->give_exp = exp;
	this->hp_max = hp;
	this->hp_current = hp_max;
	this->strength = str;
	this->level = lvl;

	/*	Welcher Aufrufe ist effektiver? Performancer sparrender? Theroretisch den Diesen Aufruft weil er direkt auf die Privat Member zugreift.
	*	nicht über ein Getter/Setter geht, die frage wie setze ich ein Aufruf für name wo der wert aber Ivaule ist?
	this->name = monster_name[rmn]
	this->give_exp = exp;
	this->hp_max = hp;
	this->hp_current = hp_max;
	this->strength = str;
	this->level = lvl;
	*/

}

