#include "Header.h"
#include <algorithm>

//portabilité vers Windows
#if (defined _WIN32 || defined _WIN64)
	#include <Windows.h>
	SetConsoleOutputCP(CP_UTF8);
#endif 


void pPlateau() {
	using namespace std;
	map <int, string> dico = {  {-1, "\u265F"},
								{-2, "\u265C"},
								{-3, "\u265E"},
								{-4, "\u265D"},
								{-5, "\u265B"},
								{-6, "\u265A"},
								{1, "\u2659"},
								{2, "\u2656"},
								{3, "\u2658"},
								{4, "\u2657"},
								{5, "\u2655"},
								{6, "\u2654"}, };
	
	cout << "   | A | B | C | D | E | F | G | H | \n";
	cout << "---+-------------------------------+ \n";
	for (int i = 0; i < 8; i++) {
		
		cout << " " << 8 - i  << " |";
		
		for (int j = 0; j < 8; j++) {
			if (plateau[i][j] < 0) {
				cout << " " << plateau[i][j] << " |";
			}
			else if (plateau[i][j] > 0) {
				cout << " " << plateau[i][j] << " |";

			}
			else {
				cout << "   |";
			}
		}
		cout << "\n   +--------------------------------\n";
	}
}

int inpt(int i) {
	using namespace std;
	map <char, int> alphabet = { {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7} };
	array <char, 8> arrphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	bool loop = true;
	char colonne;
	int rangee, id_piece, plateau_colonne, plateau_rangee;

	pPlateau();
	
	if (roi_echec(i)){
		cout<<"Attention! vous êtes en échec!\n\n";
	}
	
	do {
		cout << "Entrer votre coup (colonne rangée) :";
		cin >> colonne;
		cin >> rangee;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Entrer sous la forme [lettre de la colonne] [numero de la rangée]\n";
		}

		else {
			if (islower(colonne)) {
				colonne = toupper(colonne);
			}

			auto result1 = std::find(begin(arrphabet), end(arrphabet), colonne);

			if (rangee > 8 || rangee - 1 < 0 || result1 == std::end(arrphabet)) {
				cout << "Entrez des coordonees valides\n";
			}

			else {
			    
				plateau_rangee = 8 - rangee;//plateu = 8-7 = 1
				plateau_colonne = alphabet[colonne];//colonne = 7
				id_piece = ptrplateau[plateau_rangee][plateau_colonne];//ptrplateat[1][7] = 
				

				if (id_piece == 0 || (i == -1 && id_piece > 0) || (i == 1 && id_piece < 0)){
					cout<<"Entrez une case ou vous pouvez jouer\n";
				}
				
				else {
					loop = false;
				}
			}
		}
	} while (loop);
	
	return id_piece;
}

void bouger_jeu(int i){
	
	piece* coup = list_pieces[inpt(i)];
	coup->bouger(i);
	
	std::cout<<"\n\n\n";
}
