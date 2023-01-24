
#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <windows.h>  

//#######################################################################################//
//   ______  __        _____   _______  __    __        __  _____   _______  __    __    //
//  |   _  \|  |      /  _  \ /   __  \|  |  /  /      |  |/  _  \ /   __  \|  |  /  /   //
//  |  |_|  |  |     |  | |  |   /  \__|  | /  /       |  |  | |  |   /  \__|  | /  /    //
//  |      /|  |     |  |_|  |  |      |  |/  /        |  |  |_|  |  |      |  |/  /     //
//  |   _  \|  |     |   _   |  |    __|  |\  \  __    |  |   _   |  |    __|  |\  \     //
//  |  |_|  |  |_____|  | |  |   \__/  |  | \  \|  \__/   |  | |  |   \__/  |  | \  \    //
//  |_______|________|__| |__|\_______/|__|  \__\\_______/|__| |__|\_______/|__|  \__\   //
//                                                                                       //
//#######################################################################################//

// (с) СуперКолесо и Шиквангог

using namespace std;
default_random_engine gen;


//рандомизация
int random(int low, int high)
{
	return low + rand() % (high - low + 1);
}

// ограничение для интерфейса
void DrawCoolBorder(char drawsymbol) {
	string border(60, drawsymbol);
	cout << border << endl;
}
//прорисовка карты 
void DrawCard(char drawChar, char emptyChar, int Rank, char Faction) {
	string firstAndLastRow(5, drawChar);
	cout << firstAndLastRow << endl;

	for (int row = 1; row < 6; ++row) {
		string betweenRow(5, emptyChar);

		char drawrank = 48 + Rank;


		// Отрисовка букв J, K или Q если карты это Шут, Король или Дама
		if (Rank == 11) {
			drawrank = '\u004A';
		}
		else  if (Rank == 12) {
			drawrank = '\u0051';
		}  if (Rank == 13) {
			drawrank = '\u004B';
		}

		betweenRow[0] = drawChar;
		betweenRow[4] = drawChar;

		// отрисовка мастей и ранга карты
		char drawfaction;
		if (Faction == 1) {
			drawfaction = 3;
		}
		else if (Faction == 2) {
			drawfaction = 4;
		}
		else if (Faction == 3) {
			drawfaction = 5;
		}
		else if (Faction == 4) {
			drawfaction = 6;
		}

		// отрисовка десятки
		if (row == 1) {
			if (Rank != 10) {
				betweenRow[1] = +drawrank;
				betweenRow[2] = drawfaction;
			}
			else {
				betweenRow[1] = '\u0031';
				betweenRow[2] = '\u0030';
				betweenRow[3] = drawfaction;
			}
		}

		if (row == 3) {
			betweenRow[2] = drawfaction;
		}

		if (row == 5) {
			if (Rank != 10) {
				betweenRow[2] = +drawrank;
				betweenRow[3] = drawfaction;
			}
			else {
				betweenRow[1] = '\u0031';
				betweenRow[2] = '\u0030';
				betweenRow[3] = drawfaction;
			}
		}

		cout << betweenRow << endl;
	}
	cout << firstAndLastRow << endl;


}


int main()
{
	setlocale(LC_ALL, "Russian");
	int game = true;
	int round = true;


	DrawCoolBorder('/');
	cout << "Введите изначальный банк игроков (оба банка равны друг другу): ";
	int bank;
	cin >> bank;
	system("CLS");

	int player1bank = bank;
	int player2bank = bank;

	int TURN = true;

	int VICTORY = false;
	string PLAYERCOMMAND;

	// 0 - Пустой слот
	// 1 - Туз

	srand(time(NULL));
	

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	// Для покраса текста

	while (game == true) {

		int BETTING_PHASE = true;

		int PLAYER1_BET = 0, PLAYER2_BET = 0;

		int cards[13] = { 4, 4, 4, 4 , 4, 4, 4, 4, 4 , 4, 4, 4, 4 };

		int PLAYER1CARDS[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
		int PLAYER2CARDS[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };

		int PLAYER1CARDFACTIONS[13];
		int PLAYER2CARDFACTIONS[13];

		int PLAYER1_START_CARD = random(1, 13);
		PLAYER1CARDS[0] = PLAYER1_START_CARD;
		int PLAYER1_START_CARD_FACTION = random(1, 4);
		PLAYER1CARDFACTIONS[0] = PLAYER1_START_CARD_FACTION;
		int PLAYER2_START_CARD = random(1, 13);
		PLAYER2CARDS[0] = PLAYER2_START_CARD;
		int PLAYER2_START_CARD_FACTION = random(1, 4);
		PLAYER2CARDFACTIONS[0] = PLAYER2_START_CARD_FACTION;

		int PLAYER1POINTS = 0;
		int PLAYER2POINTS = 0;

		PLAYER1POINTS = PLAYER1_START_CARD;
		if (PLAYER1_START_CARD > 10) {
			PLAYER1POINTS = 10;
		}

		PLAYER2POINTS = PLAYER2_START_CARD;
		if (PLAYER2_START_CARD > 10) {
			PLAYER2POINTS = 10;
		}

		cards[PLAYER1_START_CARD - 1] -= 1;
		cards[PLAYER2_START_CARD - 1] -= 1;;

		int cardnew = random(1, 13);

		while (cards[cardnew] == 0) {
			cardnew = random(1, 13);
		}

		PLAYER1CARDS[0] = PLAYER1_START_CARD;
		PLAYER1CARDFACTIONS[0] = PLAYER1_START_CARD_FACTION;

		int PLAYER1_CARD_COUNT = 1;
		int PLAYER2_CARD_COUNT = 1;

		PLAYER2CARDS[0] = PLAYER2_START_CARD;
		PLAYER2CARDFACTIONS[0] = PLAYER2_START_CARD_FACTION;

		while (round == true) {

			// Отрисовка КРУТООООГО барьера
			SetConsoleTextAttribute(h, 2);
			DrawCoolBorder('/');

			SetConsoleTextAttribute(h, 15);
			cout << "КАРТЫ ИГРОКА 1: \n" << endl;

			cout << "КОЛИЧЕСТВО ОЧКОВ ИГРОКА 1: ";
			cout << PLAYER1POINTS << endl;
			for (int i = 0; i < PLAYER1_CARD_COUNT; i++) {
				DrawCard('#', ' ', PLAYER1CARDS[i], PLAYER1CARDFACTIONS[i]);
				cout << endl;
			}
			cout << endl;

			DrawCoolBorder('-');

			cout << "КАРТЫ ИГРОКА 2: \n" << endl;

			cout << "КОЛИЧЕСТВО ОЧКОВ ИГРОКА 2: ";
			cout << PLAYER2POINTS << endl;
			for (int i = 0; i < PLAYER2_CARD_COUNT; i++) {
				DrawCard('#', ' ', PLAYER2CARDS[i], PLAYER2CARDFACTIONS[i]);
				cout << endl;
			}
			cout << endl;

			// Ставки
			SetConsoleTextAttribute(h, 2);

			string ready;
			int BettingIsDone = false;

			while (BETTING_PHASE == true) {
				if (BettingIsDone == false) {
					DrawCoolBorder('/');
					cout << "=ФАЗА СТАВОК= \n";
					cout << "Ставьте ставку пока оба игрока не подтвердят готовность. \n";
					DrawCoolBorder('/');
				}

				if (TURN == true) {
					int PLAYER1_BET_CURRENT = 0;

					cout << "БАНК ИГРОКА 1: " << player1bank << endl;
					cout << "ОБЩАЯ СТАВКА ИГРОКА 1: " << PLAYER1_BET << endl;
					cout << "СТАВКА ИГРОКА 1: " << endl;
					cin >> PLAYER1_BET_CURRENT;
					DrawCoolBorder('/');

					while (PLAYER1_BET_CURRENT > player1bank) {
						cout << "Ставка не может быть больше вашего банка! \n";
						cin >> PLAYER1_BET_CURRENT;
					}

					PLAYER1_BET += PLAYER1_BET_CURRENT;
					player1bank -= PLAYER1_BET_CURRENT;

					if (BettingIsDone == false) {
						BettingIsDone = true;
						TURN = false;
					}

				}
				if (TURN == false) {
					int PLAYER2_BET_CURRENT = 0;

					cout << "БАНК ИГРОКА 2: " << player2bank << endl;
					cout << "ОБЩАЯ СТАВКА ИГРОКА 2: " << PLAYER2_BET << endl;
					cout << "СТАВКА ИГРОКА 2: " << endl;
					cin >> PLAYER2_BET_CURRENT;
					DrawCoolBorder('/');

					while (PLAYER2_BET_CURRENT > player2bank) {
						cout << "Ставка не может быть больше вашего банка! \n";
						cin >> PLAYER2_BET_CURRENT;
					}

					PLAYER2_BET += PLAYER2_BET_CURRENT;
					player2bank -= PLAYER2_BET_CURRENT;
				}

				if (PLAYER1_BET > PLAYER2_BET) {
					cout << "Ставка первого игрока большей ставки второго игрока (" << PLAYER1_BET << " > " << PLAYER2_BET << "). Игрок 2, пожалуйста, повысьте вашу ставку:" << endl;
					TURN = false;
				}
				else if (PLAYER2_BET > PLAYER1_BET) {
					cout << "Ставка второго игрока большей ставки первого игрока (" << PLAYER2_BET << " > " << PLAYER1_BET << "). Игрок 1, пожалуйста, повысьте вашу ставку:" << endl;
					TURN = true;
					// Вот здесь нужно еще как-то возврат сделать, йа не понял.
				}
				else {
					cout << "Если оба игрока готовы, напишите команду 'YES'" << endl;
					cin >> ready;
					if (ready == "YES") {
						BETTING_PHASE = false;
						TURN = true;
					}
				}
			}

			string takecommand = "T";
			string standcommand = "S";

			SetConsoleTextAttribute(h, 2);
			DrawCoolBorder('/');
			cout << "T - взять карту \n";
			cout << "S - Закончить ход \n";
			DrawCoolBorder('/');
			if (TURN == true) {
				cout << "ХОД ИГРОКА 1:" << endl;
			} else if (TURN == false) {
				cout << "ХОД ИГРОКА 2:" << endl;
			}
			DrawCoolBorder('/');
			cout << "ВВЕДИТЕ КОММАНДУ: \n";
			cin >> PLAYERCOMMAND;
			system("CLS");

			if (TURN == true) {
				if (PLAYERCOMMAND.find(standcommand) != string::npos) {
					TURN = false;
				}

				else if (PLAYERCOMMAND.find(takecommand) != string::npos) {
					for (int i = 0; i < 13; i++) {
						if (PLAYER1CARDS[i] == 0) {
							int randomcardvar = random(1, 13);
							while (cards[randomcardvar - 1] == 0) {
								randomcardvar = random(1, 13);
							}

							PLAYER1CARDFACTIONS[i] = random(1, 4);

							PLAYER1_CARD_COUNT += 1;
							PLAYER1CARDS[i] = randomcardvar;

							// Подсчет карт
							if (randomcardvar > 10) {
								PLAYER1POINTS += 10;
							}
							else {
								PLAYER1POINTS += PLAYER1CARDS[i];
							}

							if (PLAYER1POINTS > 21) {
								cout << "Игрок 1 набрал больше 21 очка!";
								TURN = false;
							}
							break;
						}
					}
				}
			}
			else {
				if (PLAYERCOMMAND.find(standcommand) != string::npos) {
					round = false;
				}

				else if (PLAYERCOMMAND.find(takecommand) != string::npos) {
					for (int i = 0; i < 13; i++) {
						if (PLAYER2CARDS[i] == 0) {
							int randomcardvar = random(1, 13);
							while (cards[randomcardvar - 1] == 0) {
								randomcardvar = random(1, 13);
							}

							PLAYER2CARDFACTIONS[i] = random(1, 4);

							PLAYER2_CARD_COUNT += 1;
							PLAYER2CARDS[i] = randomcardvar;

							// Подсчет карт
							if (randomcardvar > 10) {
								PLAYER2POINTS += 10;
							}
							else {
								PLAYER2POINTS += PLAYER2CARDS[i];
							}

							if (PLAYER2POINTS > 21) {
								cout << "Игрок 2 набрал больше 21 очка!";
								round = false;
							}
							break;

						}
					}
				}

				DrawCoolBorder('/');
				system("CLS");
			}
		}
		while (round == false) {
			if (PLAYER1POINTS > 21 && PLAYER2POINTS > 21) {
				cout << "У обоих игроков больше 21 очка." << endl << "Ставки возвращены в банки игроков.";

				player1bank += PLAYER1_BET;
				player2bank += PLAYER2_BET;
				break;

			}
			if (PLAYER1POINTS == PLAYER2POINTS) {
				cout << "Значения очков обоих игроков равно." << endl << "Ставки возвращены в банки игроков.";

				player1bank += PLAYER1_BET;
				player2bank += PLAYER2_BET;
				break;

			}
			if (PLAYER1POINTS > 21) {
				cout << "Количество очков игрока 1 превысило 21. Игрок 2 - победил." << endl << "Обе ставки уходят Игроку 2.";

				player2bank += PLAYER1_BET + PLAYER2_BET;
				break;

			}
			if (PLAYER2POINTS > 21) {
				cout << "Количество очков игрока 2 превысило 21. Игрок 1 - победил." << endl << "Обе ставки уходят Игроку 1.";

				player1bank += PLAYER1_BET + PLAYER2_BET;
				break;

			}
			if (PLAYER1POINTS > PLAYER2POINTS) {
				cout << "Карты Игрока 1 имеют большее значение чем карты Игрока 2. Игрок 1 - победил." << endl << "Обе ставки уходят Игроку 1.";

				player1bank += PLAYER1_BET + PLAYER2_BET;
				break;

			}
			if (PLAYER2POINTS > PLAYER1POINTS) {
				cout << "Карты Игрока 2 имеют большее значение чем карты Игрока 1. Игрок 2 - победил." << endl << "Обе ставки уходят Игроку 2.";

				player2bank += PLAYER2_BET + PLAYER1_BET;
				break;

			}
		}
		string READY_TO_RESTART;
		cout << "Для начала нового раунда введите команду R" << endl;
		cin >> READY_TO_RESTART;

		if (READY_TO_RESTART == "R") {
			round = true;
			TURN = true;
			system("CLS");
		}

		if (player2bank <= 0) {
			VICTORY = true;
			game = false;
		}

		if (player1bank <= 0) {
			VICTORY = false;
			game = false;
		}
	}
	if (game == false) {
		system("CLS");
		if (VICTORY == true) {
			cout << "Игра окончена, игроку 2 нечего ставить, победитель - игрок 1!" << endl;
		} else if (VICTORY == false) {
			cout << "Игра окончена, игроку 1 нечего ставить, победитель - игрок 2!" << endl;
		}
	}

	return 0;
}
