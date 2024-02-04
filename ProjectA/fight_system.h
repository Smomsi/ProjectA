//fightsystem.h
#pragma once

int critChance(int schaden);
int takeDmg(int str, int def);
int heal(int max_hp);
void escape(bool escape_try);

void fightMenu(Stats_spieler& Player_fight, Stats_enemy& Enemy_fight);
//void enemyGenerated(Stats_enemy Generator_enemy, Stats_spieler Player);
void enemyTurn(Stats_enemy& Enemy_fight, Stats_spieler& Player_fight);
