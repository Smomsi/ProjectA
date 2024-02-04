#pragma once
using namespace std;

class Stats_spieler
{
private:
	int max_hp = 0;
	int current_hp = 0;
	int strength = 0;
	int defends = 0;
	int level = 0;
	int exp = 0;
	int needexp = 0;
	int death = 0;
	int tutorial = 0;
	int gamefile = 0;

public:
	//Standart Konstrukter
	Stats_spieler();

	//setter
	void set_MaxHp(int hpmax);
	void set_CurrentHp(int hpcurrent);
	void set_Strength(int str);
	void set_Defends(int def);
	void set_Level(int lvl);
	void set_Exp(int exp);
	void set_NeedExp(int nexp);
	void set_Death(int death);
	void set_Tutorial(int tuto);
	void set_Gamefile(int game);
	//Getter
	int get_MaxHp();
	int get_CurrentHp();
	int get_Strength();
	int get_Defends();
	int get_Level();
	int get_Exp();
	int get_NeedExp();
	int get_Death();
	int get_Tutorial();
	int get_Gamefile();

	//File Methode - Save & load
	void load();
	void save();
};

class Stats_enemy
{

private:
	int hp_max = 0;
	int hp_current = 0;
	int strength = 0;
	int level = 0;
	int give_exp = 0;
	char name[20] = "DefaultEnemy"; // ist mit Null zu bewerten, Danke :D

public:
	//Standart Konstruktor - Nutzung Testwerten. Später Random werte
	Stats_enemy();

	//setter
	void set_HpMax(int hpmax);
	void set_HpCurrent(int hpcurrent);
	void set_Strength(int str);
	void set_Level(int lvl);
	void set_GiveExp(int exp);
	void set_Name(const char* name);


	//Getter
	int get_HpMax();
	int get_HpCurrent();
	int get_Strength();
	int get_Level();
	int get_GiveExp();
	const char* get_Name() const;

	// Funktion
	void generate(Stats_spieler Player);

};