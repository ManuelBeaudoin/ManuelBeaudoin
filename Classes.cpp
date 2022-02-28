#include "Header.h"
#include <algorithm>


extern std::vector <int> list_id_min = {};
extern std::vector <int> list_id_max = {};

extern std::map<int, piece*> list_pieces = {};
extern int plateau [8][8] = {
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 }
};
extern int ptrplateau[8][8] = {
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 }
};


piece::~piece(){
	std::vector<int>::iterator new_end;
	std::cout<<"\n\nvous avez tué un(e) "<<this->nom<<"!\n\n";
	list_pieces.erase(indentifiant);
	if (indentifiant < 0){
		new_end = remove(list_id_min.begin(), list_id_min.end(), indentifiant);
	}

	else {
		new_end = remove(list_id_max.begin(), list_id_max.end(), indentifiant);
	}
};
void piece::info() {
	std::array <char, 8> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	std::cout << "cette piece est un(e): "<< this->nom << std::endl;
	std::cout << "elle se situe aux points: " << '(' << alphabet[position[1]] << "," << 8 - position[0] << ")\n";
};
void piece::bouger(int i) {
	bool inpt = true;
	int nombre;
	int op0 = position[0];
	int op1 = position[1];
	
	std::vector <std::array<int, 2>> coupsPossibles = list();
	
	if (coupsPossibles.size() == static_cast<std::vector<int>::size_type>(0)){
		info();
		std::cout<<"\nIl n'y a pas de coups possibles \n\n";
		bouger_jeu(i);
	}
	
	else {
		std::array <char, 8> alphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };

		info();

		std::cout << "coups possibles:" << std::endl;
		int j = 0;
		for (std::array<int, 2> i : coupsPossibles) {
			std::cout << j << " : (" << alphabet[i[1]] << ',' << 8 - i[0] << ")\n";
			j++;
		}
		std::cout<<"\nChanger de piece: 50\nAbandonner la partie: 60\n";
		std::cout << std::endl;
	
		do {
			inpt = true;
			
			std::cout << "\nQue voulez vous jouer: ";
			std::cin >> nombre;
			
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Entrez un coup valide\n";
				inpt = false;
			}
			
			if (nombre == 50){}
			
			else if (nombre >= coupsPossibles.size()){
				std::cout<<"Entrez un des coups possibles\n";
				inpt =false;
			}

		} while (inpt != true);
		
		//choisir une autre piece
		if (nombre == 50) {
			bouger_jeu(i);
		}
		
		//abbandonner la partie (tuer le roi)
		else if (nombre == 60) {
			list_pieces[i*16] = 0;
		}
		
		else {
			position = coupsPossibles[nombre];
			
			if (ptrplateau[position[0]][position[1]] != 0) {
				piece* coup = list_pieces[ptrplateau[position[0]][position[1]]];
				delete coup;
			}
			
			plateau[op0][op1] = 0;
			plateau[position[0]][position[1]] = valeur;  
			ptrplateau[op0][op1] = 0;
			ptrplateau[position[0]][position[1]] = indentifiant;
		}
	}
};


pion::pion(int bord, int num) {
	if (bord < 0) {
		valeur = -1;
		position[0] = 6;
		indentifiant = (8 - num) * -1;
		list_id_min.push_back(indentifiant);
		
	}
	else {
		valeur = 1;
		position[0] = 1;
		indentifiant = (8 - num);
		indentifiant = (8 - num);
		list_id_max.push_back(indentifiant);
	
	}
	
	position[1] = num;
	
	nom = "Pion";
	
	list_pieces[indentifiant] = this;
	ptrplateau[position[0]][position[1]] = indentifiant;
	plateau[position[0]][position[1]] = valeur;

};
std::vector <std::array<int, 2>> pion::list() {
	std::array <int, 2> coup;
	std::vector <std::array<int, 2>> coupsPossibles;
	if (valeur == -1) {
		if (position[0] == 6 && plateau[position[0] - 1][position[1]] == 0 && plateau[position[0] - 2][position[1]] == 0) {
			coup[0] = { position[0] - 2 }; coup[1] = { position[1] };
			coupsPossibles.push_back(coup);
			coup = { position[0] - 1, position[1] };
			coupsPossibles.push_back(coup);
		}
		else if (plateau[position[0] - 1][position[1]] == 0 && position[0] - 1 >= 0) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1] };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 1][position[1] - 1] > 0 && position[0] - 1 >= 0 && position[1] - 1 >= 0) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1] - 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 1][position[1] + 1] > 0 && position[0] - 1 >= 0 && position[1] + 1 < 8) {
	        coup[0] = { position[0] - 1 }; coup[1] = { position[1] + 1 };
			coupsPossibles.push_back(coup); 
		}
	}
	
	if (valeur == 1) {
		if (position[0] == 1 && plateau[position[0] + 1][position[1]] == 0 && plateau[position[0] + 2][position[1]] == 0) {
			coup[0] = { position[0] + 2 }; coup[1] = { position[1] };
			coupsPossibles.push_back(coup);
			coup = { position[0] + 1, position[1] };
			coupsPossibles.push_back(coup);
		}
		else if (plateau[position[0] + 1][position[1]] == 0 && position[0] + 1 < 8) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 1][position[1] + 1] < 0 && position[0] + 1 < 8 && position[1] + 1 < 8) {
			if (position[0] + 1 < 8 && position[1] + 1 < 8) {
				coup[0] = { position[0] + 1 }; coup[1] = { position[1] + 1 };
				coupsPossibles.push_back(coup);
			}
		}
		if (plateau[position[0] + 1][position[1] - 1] < 0 && position[0] - 1 < 8 && position[1] - 1 >= 0) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] - 1 };
			coupsPossibles.push_back(coup);
		}
	}

	return coupsPossibles;
};


tour::tour(int bord, int num) {
	
	if (bord < 0) {
		valeur = -2;
		position[0] = 7;
		indentifiant = (10 - num) * -1;
		list_id_min.push_back(indentifiant);

	}
	else {
		valeur = 2;
		position[0] = 3;
		indentifiant = (10 - num);
		list_id_max.push_back(indentifiant);
	}
	if (num == 0)
		position[1] = 0;
	else
		position[1] = 7;
	

	nom = "Tour";
	
	list_pieces[indentifiant] = this;
	ptrplateau[position[0]][position[1]] = indentifiant;
	plateau[position[0]][position[1]] = valeur;

};
std::vector <std::array<int, 2>> tour::list() {
	int i = 1;
	std::array <int, 2> coup;
	std::vector <std::array<int, 2>> coupsPossibles;
    
    if (valeur == -2) {
		while (true) { //haut
			if (plateau[position[0] + i][position[1]] == 0 && position[0] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] + i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] + i][position[1]] > 0 && position[0] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] + i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}
		i = 1;//safe
		
		while (true) { //bas
			if (plateau[position[0] - i][position[1]] == 0 && position[0] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] - i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] - i][position[1]] > 0 && position[0] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] - i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}
		i = 1;//safe
		
		while (true) { //droite
			if (plateau[position[0]][position[1] + i] == 0 && position[1] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0]][position[1] + i] > 0 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}
		i = 1;//safe
		
		while (true) { //gauche
			if (plateau[position[0]][position[1] - i] == 0 && position[1] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0]][position[1] - i] > 0 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}

 		}
	    i = 1;//safe
	}
	
	else if (valeur == 2) {
		while (true) { //haut
			if (plateau[position[0] + i][position[1]] == 0 && position[0] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] + i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] + i][position[1]] < 0 && position[0] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] + i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
		i = 1;
		
		while (true) { //bas
			if (plateau[position[0] - i][position[1]] == 0 && position[0] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] - i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] - i][position[1]] < 0 && position[0] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] - i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
		i = 1;

		while (true) { //droite
			if (plateau[position[0]][position[1] + i] == 0 && position[1] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0]][position[1] + i] < 0 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
		i = 1;

		while (true) { //gauche
			if (plateau[position[0]][position[1] - i] == 0 && position[1] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0]][position[1] - i] < 0 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
	}//safe

	return coupsPossibles;
};


cavalier::cavalier(int bord, int num) {;
	
	if (bord < 0) {
		valeur = -3;
		position[0] = 7;
		indentifiant = (12 - num) * -1;
		list_id_max.push_back(indentifiant);
	}
	else {
		valeur = 3;
		position[0] = 0;
		indentifiant = (12 - num);
		list_id_max.push_back(indentifiant);
	}
	if (num == 1)
		position[1] = 1;
	else
		position[1] = 6;
	

	nom = "Cavalier";
	
	list_pieces[indentifiant] = this;
	plateau[position[0]][position[1]] = valeur;
	ptrplateau[position[0]][position[1]] = indentifiant;

};
std::vector<std::array<int, 2>> cavalier::list() {
	int i = 1;
	std::array <int, 2> coup;
	std::vector <std::array<int, 2>> coupsPossibles;

	if (valeur == -3) {
		if (plateau[position[0] + 2][position[1] + 1] >= 0 && position[0] + 2 < 8 && position[1] + 1 < 8) {
			coup[0] = { position[0] + 2 }; coup[1] = { position[1] + 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 2][position[1] - 1] >= 0 && position[0] + 2 < 8 && position[1] - 1 >= 0) {
			coup[0] = { position[0] + 2 }; coup[1] = { position[1] - 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 2][position[1] + 1] >= 0 && position[0] - 2 >= 0 && position[1] + 1 < 8) {
			coup[0] = { position[0] - 2 }; coup[1] = { position[1] + 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 2][position[1] - 1] >= 0 && position[0] - 2 >= 0 && position[1] - 1 >= 0) {
			coup[0] = { position[0] - 2 }; coup[1] = { position[1] - 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 1][position[1] + 2] >= 0 && position[0] + 1 < 8 && position[1] + 2 < 8) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] + 2 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 1][position[1] - 2] >= 0 && position[0] + 1 < 8 && position[1] - 2 >= 0) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] - 2 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 1][position[1] + 2] >= 0 && position[0] - 1 >= 0 && position[1] + 2 < 8) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1] + 2 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 1][position[1] - 2] >= 0 && position[0] - 1 >= 0 && position[1] - 2 >= 0) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1] - 2 };
			coupsPossibles.push_back(coup);
		}
	}

	else if (valeur == 3) {
		if (plateau[position[0] + 2][position[1] + 1] <= 0 && position[0] + 2 < 8 && position[1] + 1 < 8) {
			coup[0] = { position[0] + 2 }; coup[1] = { position[1] + 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 2][position[1] - 1] <= 0 && position[0] + 2 < 8 && position[1] - 1 >= 0) {
			coup[0] = { position[0] + 2 }; coup[1] = { position[1] - 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 2][position[1] + 1] <= 0 && position[0] - 2 >= 0 && position[1] + 1 < 8) {
			coup[0] = { position[0] - 2 }; coup[1] = { position[1] + 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 2][position[1] - 1] <= 0 && position[0] - 2 >= 0 && position[1] - 1 >= 0) {
			coup[0] = { position[0] - 2 }; coup[1] = { position[1] - 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 1][position[1] + 2] <= 0 && position[0] + 1 < 8 && position[1] + 2 < 8) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] + 2 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 1][position[1] - 2] <= 0 && position[0] + 1 < 8 && position[1] - 2 >= 0) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] - 2 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 1][position[1] + 2] <= 0 && position[0] - 1 >= 0 && position[1] + 2 < 8) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1] + 2 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 1][position[1] - 2] <= 0 && position[0] - 1 >= 0 && position[1] - 2 >= 0) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1] - 2 };
			coupsPossibles.push_back(coup);
		}
	}

	return coupsPossibles;
};


fou::fou(int bord, int num) {
	if (bord < 0) {
		valeur = -4;
		position[0] = 7;
		indentifiant = (14 - num) * -1;
		list_id_min.push_back(indentifiant);
	}
	else {
		valeur = 4;
		position[0] = 0;
		indentifiant = (14 - num);
		list_id_max.push_back(indentifiant);
	}
	if (num == 1)
		position[1] = 2;
	else
		position[1] = 5;
	

	nom = "Fou";
	
	list_pieces[indentifiant] = this;
	ptrplateau[position[0]][position[1]] = indentifiant;
	plateau[position[0]][position[1]] = valeur;

};
std::vector <std::array<int, 2>> fou::list() {
	int i = 1;
	std::array <int, 2> coup;
	std::vector <std::array<int, 2>> coupsPossibles;

	if (valeur == -4) {
      while (true) { //haut gauche
         if (plateau[position[0] + i][position[1] + i] == 0 && position[0] + i < 8 && position[1] + i < 8) { // vide -> note et continue
            coup[0] = { position[0] + i }; coup[1] = { position[1] + i };
            coupsPossibles.push_back(coup);
            i++;
         }
         else if (plateau[position[0] + i][position[1] + i] > 0 && position[0] + i < 8 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
            coup[0] = { position[0] + i }; coup[1] = { position[1] + i };
            coupsPossibles.push_back(coup);
            break;
         }
         else { //meme equipe -> arrete
            break;
         }
      }//safe
      i = 1;
      
      while (true) { //bas droite
         if (plateau[position[0] - i][position[1] - i] == 0 && position[0] - i >= 0 && position[1] - i >= 0) { // vide -> note et continue
            coup[0] = { position[0] - i }; coup[1] = { position[1] - i };
            coupsPossibles.push_back(coup);
            i++;
         }
         else if (plateau[position[0] - i][position[1] - i] > 0 && position[0] - i >= 0 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
            coup[0] = { position[0] - i }; coup[1] = { position[1] - i };
            coupsPossibles.push_back(coup);
            break;
         }
         else { //meme equipe -> arrete
            break;
         }
      }//safe
      i = 1;
      
      while (true) { // bas droite
         if (plateau[position[0] - i][position[1] + i] == 0 && position[0] - i >= 0 && position[1] + i < 8) { // vide -> note et continue
            coup[0] = { position[0] - i }; coup[1] = { position[1] + i };
            coupsPossibles.push_back(coup);
            i++;
         }
         else if (plateau[position[0] - i][position[1] + i] > 0 && position[0] - i >= 0 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
            coup[0] = { position[0] - i }; coup[1] = { position[1] + i };
            coupsPossibles.push_back(coup);
            break;
         }
         else { //meme equipe -> arrete
            break;
         }
      }//safe
      i = 1;
     
      while (true) { //haut gauche
         if (plateau[position[0] + i][position[1] - i] == 0 && position[0] + i < 8 && position[1] - i >= 0) { // vide -> note et continue
            coup[0] = { position[0] + i }; coup[1] = { position[1] - i };
            coupsPossibles.push_back(coup);
            i++;
         }
         else if (plateau[position[0] + i][position[1] - i] > 0 && position[0] + i < 8 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
            coup[0] = { position[0] + i }; coup[1] = { position[1] - i };
            coupsPossibles.push_back(coup);
            break;
         }
         else { //meme equipe -> arrete
            break;
         }  
      }//safe
      i = 1;
	}//safe
    //safe
	else if (valeur == 4) {
		while (true) { //haut
			if (plateau[position[0] + i][position[1] + i] == 0 && position[0] + i < 8 && position[1] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] + i }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] + i][position[1] + i] < 0 && position[0] + i < 8 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] + i }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
		i = 1;//safe
		
		while (true) { //bas 
			if (plateau[position[0] - i][position[1] - i] == 0 && position[0] - i >= 0 && position[1] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] - i }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] - i][position[1] - i] < 0 && position[0] - i >= 0 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] - i }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
		i = 1;//safe
		
		while (true) { //droite
			if (plateau[position[0] - i][position[1] + i] == 0 && position[0] - i >= 0 && position[1] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] - i }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] - i][position[1] + i] < 0 && position[0] - i >= 0 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] - i }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}
		i = 1;//safe
		
		while (true) { //gauche
			if (plateau[position[0] + i][position[1] - i] == 0 && position[0] + i < 8 && position[1] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] + i }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] + i][position[1] - i] < 0 && position[0] + i < 8 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] + i }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}
		i = 1; //safe
	}
	//safe
	return coupsPossibles;
};


dame::dame(int bord) {
	if (bord < 0) {
		valeur = -5;
		position[0] = 7;
		indentifiant = 15 * -1;
		list_id_min.push_back(indentifiant);
	}
	else {
		valeur = 5;
		position[0] = 0;
		indentifiant = 15;
		list_id_max.push_back(indentifiant);
	}
	
	position[1] = 3;

	nom = "Dame";
	
	list_pieces[indentifiant] = this;
	ptrplateau[position[0]][position[1]] = indentifiant;
	plateau[position[0]][position[1]] = valeur;

};
std::vector <std::array<int, 2>> dame::list() {
	int i = 1;
	std::array <int, 2> coup;
	std::vector <std::array<int, 2>> coupsPossibles;

	if (valeur == -5) {
      while (true) { //haut gauche
         if (plateau[position[0] + i][position[1] + i] == 0 && position[0] + i < 8 && position[1] + i < 8) { // vide -> note et continue
            coup[0] = { position[0] + i }; coup[1] = { position[1] + i };
            coupsPossibles.push_back(coup);
            i++;
         }
         else if (plateau[position[0] + i][position[1] + i] > 0 && position[0] + i < 8 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
            coup[0] = { position[0] + i }; coup[1] = { position[1] + i };
            coupsPossibles.push_back(coup);
            break;
         }
         else { //meme equipe -> arrete
            break;
         }
      }//safe
      i = 1;
      
      while (true) { //bas droite
         if (plateau[position[0] - i][position[1] - i] == 0 && position[0] - i >= 0 && position[1] - i >= 0) { // vide -> note et continue
            coup[0] = { position[0] - i }; coup[1] = { position[1] - i };
            coupsPossibles.push_back(coup);
            i++;
         }
         else if (plateau[position[0] - i][position[1] - i] > 0 && position[0] - i >= 0 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
            coup[0] = { position[0] - i }; coup[1] = { position[1] - i };
            coupsPossibles.push_back(coup);
            break;
         }
         else { //meme equipe -> arrete
            break;
         }
      }//safe
      i = 1;
      
      while (true) { // bas droite
         if (plateau[position[0] - i][position[1] + i] == 0 && position[0] - i >= 0 && position[1] + i < 8) { // vide -> note et continue
            coup[0] = { position[0] - i }; coup[1] = { position[1] + i };
            coupsPossibles.push_back(coup);
            i++;
         }
         else if (plateau[position[0] - i][position[1] + i] > 0 && position[0] - i >= 0 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
            coup[0] = { position[0] - i }; coup[1] = { position[1] + i };
            coupsPossibles.push_back(coup);
            break;
         }
         else { //meme equipe -> arrete
            break;
         }
      }//safe
      i = 1;
     
      while (true) { //haut gauche
         if (plateau[position[0] + i][position[1] - i] == 0 && position[0] + i < 8 && position[1] - i >= 0) { // vide -> note et continue
            coup[0] = { position[0] + i }; coup[1] = { position[1] - i };
            coupsPossibles.push_back(coup);
            i++;
         }
         else if (plateau[position[0] + i][position[1] - i] > 0 && position[0] + i < 8 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
            coup[0] = { position[0] + i }; coup[1] = { position[1] - i };
            coupsPossibles.push_back(coup);
            break;
         }
         else { //meme equipe -> arrete
            break;
         }  
      }//safe
      i = 1;
	}//safe
    //safe

	else if (valeur == 5) {
		while (true) { //haut
			if (plateau[position[0] + i][position[1] + i] == 0 && position[0] + i < 8 && position[1] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] + i }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] + i][position[1] + i] < 0 && position[0] + i < 8 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] + i }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
		i = 1;//safe
		
		while (true) { //bas 
			if (plateau[position[0] - i][position[1] - i] == 0 && position[0] - i >= 0 && position[1] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] - i }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] - i][position[1] - i] < 0 && position[0] - i >= 0 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] - i }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
		i = 1;//safe
		
		while (true) { //droite
			if (plateau[position[0] - i][position[1] + i] == 0 && position[0] - i >= 0 && position[1] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] - i }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] - i][position[1] + i] < 0 && position[0] - i >= 0 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] - i }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}
		i = 1;//safe
		
		while (true) { //gauche
			if (plateau[position[0] + i][position[1] - i] == 0 && position[0] + i < 8 && position[1] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] + i }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] + i][position[1] - i] < 0 && position[0] + i < 8 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] + i }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}
		i = 1; //safe
	}
	//safe
	
	if (valeur == -5) {
		while (true) { //haut
			if (plateau[position[0] + i][position[1]] == 0 && position[0] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] + i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] + i][position[1]] > 0 && position[0] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] + i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}
		i = 1;//safe
		
		while (true) { //bas
			if (plateau[position[0] - i][position[1]] == 0 && position[0] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] - i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] - i][position[1]] > 0 && position[0] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] - i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}
		i = 1;//safe
		
		while (true) { //droite
			if (plateau[position[0]][position[1] + i] == 0 && position[1] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0]][position[1] + i] > 0 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}
		i = 1;//safe
		
		while (true) { //gauche
			if (plateau[position[0]][position[1] - i] == 0 && position[1] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0]][position[1] - i] > 0 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}

 		}
	    i = 1;//safe
	}
	//safe
	
	else if (valeur == 5) {
		while (true) { //haut
			if (plateau[position[0] + i][position[1]] == 0 && position[0] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] + i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] + i][position[1]] < 0 && position[0] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] + i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
		i = 1;
		
		while (true) { //bas
			if (plateau[position[0] - i][position[1]] == 0 && position[0] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] - i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0] - i][position[1]] < 0 && position[0] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] - i }; coup[1] = { position[1] };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
		i = 1;

		while (true) { //droite
			if (plateau[position[0]][position[1] + i] == 0 && position[1] + i < 8) { // vide -> note et continue
				coup[0] = { position[0] }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0]][position[1] + i] < 0 && position[1] + i < 8) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] }; coup[1] = { position[1] + i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
		i = 1;

		while (true) { //gauche
			if (plateau[position[0]][position[1] - i] == 0 && position[1] - i >= 0) { // vide -> note et continue
				coup[0] = { position[0] }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				i++;
			}
			else if (plateau[position[0]][position[1] - i] < 0 && position[1] - i >= 0) { //equipe ennemie -> arrete mais note
				coup[0] = { position[0] }; coup[1] = { position[1] - i };
				coupsPossibles.push_back(coup);
				break;
			}
			else { //meme equipe -> arrete
				break;
			}
		}//safe
	}//safe
	//safe
	
	return coupsPossibles;
};// safe, peut etre relire


roi::roi(int bord) {
	if (bord < 0) {
		valeur = -6;
		position[0] = 7;
		indentifiant = 16 * -1;
		list_id_min.push_back(indentifiant);
	}
	else {
		valeur = 6;
		position[0] = 0;
		indentifiant = 16;
		list_id_max.push_back(indentifiant);
	}
	
	position[1] = 4;
	nom = "Roi";

	
	list_pieces[indentifiant] = this;
	ptrplateau[position[0]][position[1]] = indentifiant;
	plateau[position[0]][position[1]] = valeur;
	
};
std::vector <std::array<int, 2>> roi::list() {
	int i = 1;
	std::array <int, 2> coup;
	std::vector <std::array<int, 2>> coupsPossibles;

	if (valeur == -6) {
		if (plateau[position[0] + 1][position[1]] >= 0 && position[0] + 1 < 8) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 1][position[1] - 1] >= 0 && position[0] + 1 < 8 && position[1] - 1 >= 0) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] - 1};
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 1][position[0] + 1] >= 0 && position[0] + 1 < 8 && position[1] + 1 < 8) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] + 1};
			coupsPossibles.push_back(coup);
		}
		//reculer FAIT 
		if (plateau[position[0] - 1][position[0]] >= 0 && position[0] - 1 >= 0) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1] };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 1][position[0] + 1] >= 0 && position[0] - 1 >= 0 && position[1] + 1 < 8) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1]+ 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 1][position[0] - 1] >= 0 && position[0] - 1 >= 0 && position[1] - 1 >= 0) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1] - 1 };
			coupsPossibles.push_back(coup);
		}
		//coté  FAIT
		if (plateau[position[0]][position[0] + 1] >= 0 && position[1] + 1 < 8) {
			coup[0] = { position[0] }; coup[1] = { position[1] + 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0]][position[0] - 1] >= 0 && position[1] - 1 >= 0) {
			coup[0] = { position[0] }; coup[1] = { position[1] - 1 };
			coupsPossibles.push_back(coup);
		}
	}
	else if (valeur == 6) {
		//fait

		if (plateau[position[0] + 1][position[1]] <= 0 && position[0] + 1 < 8) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 1][position[1] - 1] <= 0 && position[0] + 1 < 8 && position[1] - 1 >= 0) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] - 1};
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] + 1][position[0] + 1] <= 0 && position[0] + 1 < 8 && position[1] + 1 < 8) {
			coup[0] = { position[0] + 1 }; coup[1] = { position[1] + 1};
			coupsPossibles.push_back(coup);
		}
		//reculer FAIT 
		if (plateau[position[0] - 1][position[0]] <= 0 && position[0] - 1 >= 0) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1] };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 1][position[0] + 1] <= 0 && position[0] - 1 >= 0 && position[1] + 1 < 8) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1]+ 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0] - 1][position[0] - 1] <= 0 && position[0] - 1 >= 0 && position[1] - 1 >= 0) {
			coup[0] = { position[0] - 1 }; coup[1] = { position[1] - 1 };
			coupsPossibles.push_back(coup);
		}
		//coté  FAIT
		if (plateau[position[0]][position[0] + 1] <= 0 && position[1] + 1 < 8) {
			coup[0] = { position[0] }; coup[1] = { position[1] + 1 };
			coupsPossibles.push_back(coup);
		}
		if (plateau[position[0]][position[0] - 1] <= 0 && position[1] - 1 >= 0) {
			coup[0] = { position[0] }; coup[1] = { position[1] - 1 };
			coupsPossibles.push_back(coup);
		}
	}

	return coupsPossibles;
};//fini et relu