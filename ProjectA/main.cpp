#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <time.h>
#include <Windows.h>

#include "Classes.h"
#include "fight_system.h"
#include "utility_funtions.h"

//Sleep´s
#define WAIT 1500
#define MINIWAIT 650

//Globale Variabeln, einfach keine beachtung schneken ist Schmutz für schmutz User 
int WAITSTACK = WAITSTACK + WAIT;

// ===========================
//		Spiel Funktion
// ===========================
int checkLevelUP(Stats_spieler& Player) {
	int antwort;
	if (Player.get_Exp() == Player.get_NeedExp() || Player.get_Exp() >= Player.get_NeedExp()) { // <- BENÖTIGTE EXP MIT DEN LEVEL STEIGERN
		chainread("\nDu hast ein LevelUp Ereicht!! :D , Good Job.\n"
			"Du hast nun die Moeglichkeit Punkte zu Investieren.\n");

		printf("[1] Max HP\n");
		Sleep(MINIWAIT);
		printf("[2] Strength\n");
		Sleep(MINIWAIT);
		printf("[3] Defends\n");

		do {
			antwort = inputZahl();
			switch (antwort)
			{
			case 1:
				Player.set_MaxHp(Player.get_MaxHp() + 5); // Hardcode, weil Gamedesign.
				Player.set_Exp(Player.get_Exp() - 100); // Um dem Exp Balken zurückzusetzen.
				chainread("Du hast Deine Maximale HP erhoht <3\n");
				chainread("Du hast nun eine Maximale HP von: %d", Player.get_MaxHp());
				Player.set_CurrentHp(Player.get_MaxHp()); // Insta Heal auf MaxHp.
				break;
			case 2:
				Player.set_Strength(Player.get_Strength() + 1);
				Player.set_Exp(Player.get_Exp() - 100); // Um dem Exp Balken zurückzusetzen.
				chainread("Du hast Deine Strength erhoht ;)\n");
				chainread("Du hast nun eine Starker von: %d", Player.get_Strength());
				break;
			case 3:
				Player.set_Defends(Player.get_Defends() + 1);
				Player.set_Exp(Player.get_Exp() - 100); // Um dem Exp Balken zurückzusetzen.
				chainread("Du hast dein Verteigung erhoht --[]\n");
				chainread("Du hast nun eine Verteidigung von: %d", Player.get_Defends());
				break;
			default:
				chainread("Ungultige Auswahl. Bitte Versuchs erneut.\n");
				Sleep(WAIT);
				break;
			}
		} while (antwort != 1 && antwort != 2 && antwort != 3);
		Player.set_Level(Player.get_Level() + 1);
		Player.set_NeedExp(Player.get_NeedExp() + 5);
		Player.save();
		Sleep(WAIT);
		return Player.get_Exp();
		return Player.get_Level(); // überprüfung LevelUp Gelungen
	}
	return 0;
}


// ===========================
//		 Main Programm
// ===========================

void main() {
	Stats_spieler Player;
	Stats_enemy Enemy;
	FILE* main_datei;
	char ant_switch;
	char temp_antwort;
	bool fehlermeldung = false;
	bool escape_check = false;
	bool death = false;
	int temp_antwort_int;
	int gamefile = 0;
	int tutorial = Player.get_Tutorial();
	// ===========================
	//			Main Menu
	// ===========================

	do {
		system("CLS");
		chainread("Willkommen Spieler! Bei Project A\nWas Mochtest du Tuen?\n");
		printf("[1]\t Neues Spiel\n");
		Sleep(MINIWAIT);
		printf("[2]\t Spiel Laden\n");
		Sleep(MINIWAIT);
		printf("[3]\t Credits\n");
		Sleep(MINIWAIT);
		printf("[x]\t Spiel Beenden\n");


		//Hauptmenu
		ant_switch = inputChar();

		switch (ant_switch)
		{
			//New Gamex
		case '1':
			Player.save();
			chainread("Neues Spiel wird erstellt");
			waitPoint(3);
			printf("\n");
			chainread("Neues Speil wurde erstelt.\n");
			printf("\n");
			Sleep(WAIT); // Sleep in Millisekunden
			Player.set_Gamefile(1);
			break;
			// Loading Game
		case'2':
				Player.load();
			if (Player.get_Gamefile() == 1) { // Standart konstruktor hat null DESHALB lädt der garned erst.
				chainread("Geladene Spierdatein Daten:\n");;
				printf("HP: % d / % d", Player.get_CurrentHp(), Player.get_MaxHp());
				Sleep(MINIWAIT);
				printf("\nStr: %d", Player.get_Strength());
				Sleep(MINIWAIT);
				printf("\nDef: %d", Player.get_Defends());
				Sleep(MINIWAIT);
				printf("\nLvl: %d", Player.get_Level());
				Sleep(MINIWAIT);
				printf("\nTode: %d", Player.get_Death());

				Sleep(MINIWAIT);
				printf("\n");
			}
			else
			{
				chainread("Du Hat keine Vorhandene Spieldaten. Bitte Erstelle erst ein Spielstand.");
			}
			break;
			// Credits
		case'3':
			chainread("Developer:\nAnzinono\n\nGameDesign:\nAnzinono\n\n");
			printf("\n");
			system("PAUSE");
			break;

			// Exit
		case'x':
			return;
			printf("\n");
			system("PAUSE");
			break;
		default:
			chainread("Kann es sein, dass du dumm bist oder sowas?\n");
			chainread("-> ");
			waitPoint(3);
			chainread(" Ja bin Ich.");
			Sleep(WAITSTACK); // Spieler IMMER BESTRAFEN wenn er eine dumme Eingabe macht. ROFL
			break;
		}
	} while (ant_switch != '1' && ant_switch != '2' || Player.get_Gamefile() != 1);



	// ========================
	//			Tutorial
	// ========================

	//Maybe Komplett von neu aufbauen oder Gut Fixen.




	// ==========================
	//			Main Game
	// ==========================
	do {
		system("CLS");
		if (death == true) {
			Player.set_Death(Player.get_Death() + 1);
			chainread("Deine Seele wurde zum Bonfire gebracht.\nUnd Dein Koerper wurde wiederhergestellt, Tarnished\n");
			death = false;
		}
		chainread("Was mochtest du am Bonfire machen?\n\n");
		printf("Bonfire:\n");
		Sleep(MINIWAIT);
		printf("[K] Kampfen!\n");
		Sleep(MINIWAIT);
		printf("[A] Ausruhen\n");
		Sleep(MINIWAIT);
		printf("[S] Speichern\n");
		Sleep(MINIWAIT);
		printf("[D] DarkSouls\n");
		Sleep(MINIWAIT);
		printf("[O] Optionen\n");
		Sleep(MINIWAIT);
		printf("[X] Spiel Beenden\n");

		ant_switch = inputChar();

		switch (ant_switch)
		{
			// Spiel beenden
		// Kampf
		case 'k':
			Enemy.generate(Player); // Enemy Generiert
			chainread("AUFPASSEN! Ein %s ist erschienen! ZEIT FUER DEN KAMPF!", Enemy.get_Name());
			do {
				fightMenu(Player, Enemy);

				if (Enemy.get_HpCurrent() >= 0 && Enemy.get_HpCurrent() != 0) {
					enemyTurn(Enemy, Player);
				}

				// Gegner HP = 0, Spieler HP = 0, Fliehen = true
			} while (Enemy.get_HpCurrent() >= 0 && Enemy.get_HpCurrent() != 0 && escape_check != true && Player.get_CurrentHp() >= 0 && Player.get_CurrentHp() != 0);


			// Wenn Spieler Tot ist.
			if (Player.get_CurrentHp() <= 0) {
				death = true;
				chainread("\nSCHEISSE!!! Du bist Gestorben!? Ich hol dich schnell hier raus!\n\n");
				chainread("Deine Seele, wurde aufgesammelt");
				waitPoint(3);
				Player.load();
			}

			// Exp Ausgabe / Gegner Tot
			if (Enemy.get_HpCurrent() <= 0 || Enemy.get_HpCurrent() == 0) {
				chainread("Der %s ist TOT.\n", Enemy.get_Name());
				chainread("Du hast %d Exp Erhalten.\n", Enemy.get_GiveExp());
				Player.set_Exp(Player.get_Exp() + Enemy.get_GiveExp());
				checkLevelUP(Player);
			}

			printf("\n");
			Sleep(WAIT);
			break;

			//Ausruhen
		case 'a':
			chainread("Es ist Abend und du Geniesst die Sicht aufm Himmel.\n"
				"Der Blau Violette Himmel, die Verbranten Baeume von Elden.\n");
			waitPoint(5);
			Player.set_CurrentHp(Player.get_MaxHp());
			chainread("Du bist eingeschlafen und hast dich Ausgeruht, HP: %d/%d", Player.get_CurrentHp(), Player.get_MaxHp());
			chainread("\nDeine Kraft sammelt  sich einmaelich: %d/%d Exp ", Player.get_Exp(), Player.get_NeedExp());

			Sleep(WAIT);
			printf("\n");
			break;

			// Spiel Speichern
		case 's':
			chainread("Das Spiel wird Gespeichert");
			waitPoint(3);
			Player.save();
			chainread("\nDas Spiel wurde Gespeichert.");
			printf("\n");
			Sleep(WAIT);
			break;
		case 'x':
			chainread("Moechtest du das Spiel wirklich Beenden? [Y|N]\n");
			temp_antwort = inputChar();

			if (temp_antwort == 'y') {
				chainread("Das Spiel wird Automatisch Gespeichert");
				Player.save();
				waitPoint(3);
				chainread("\nDas spiel wurde Gespeichert\n");

				chainread("\nDas Spiel wird beendent");
				waitPoint(3);
				return;
			}
			if (temp_antwort == 'n') {
				chainread("Spiel wird nicht beendet.");
			}
			if (temp_antwort != 'n' && temp_antwort != 'y') {
				chainread("Ungultige Auswahl. Spiel wird nicht Beendet!!!\n");
			}
			printf("\n");
			Sleep(WAIT);
			break;

			// Deathcount
		case 'd':
			chainread("Eure seele ist %d mal zum Opfer Gefallen.\n", Player.get_Death());
			printf("\n");
			Sleep(WAIT);
			break;

			// Option
		case 'o':
			chainread("Da es nur die Text Geschwindigkeit einzustellen gibt es keine Option :P\n");
			chainread("Also... Wie schnell mochtest du es haben? Von 1 bis 10.\n1 = Schnell\n10 = Langsam\n5 = Standart\n");	
			do {
				temp_antwort_int = inputZahl();

				if (temp_antwort_int >= 1 && temp_antwort_int <= 10) {
					textspeed = temp_antwort_int;

					chainread("Das ist hier ein Beispiel Text.");
					Sleep(WAIT);
					chainread("\nBist du dir sicher, dass du diese Geschwindigkeit behalten möchtest? [Y|N]\n");
					temp_antwort = inputChar();

					if (temp_antwort != 'n' && temp_antwort != 'y') {
						chainread("Ungültige Eingabe. Aus Sicherheitsgründen wird diese Eingabe als [N] gewertet.");
						temp_antwort = 'n'; // Standardmäßig als [N] werten
					}
				}
				else {
					chainread("Ungültige Eingabe. Bitte gib eine Zahl zwischen 1 und 10 ein.\n");
					temp_antwort = 'n'; // Standardmäßig als [N] werten
				}
			} while (temp_antwort != 'y');
			break;

			//Default
		default:
			chainread("Ungultige Auswahl. Bitte Versuchs erneut.\n");
			Sleep(WAIT);
			break;
		}
	} while (true);
}