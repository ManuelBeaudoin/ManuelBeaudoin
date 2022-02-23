#include "Header.h"
#define X coup->position[0]
#define Y coup->position[1]

bool echec_mat(int i){
	piece* coup;
	std::vector <std::array<int, 2>> liste;
//pour les piece blancehes
	if (i == 1){
		//vérifier chaque piece de l'équipe
		for (int j = 0; j <= static_cast<int>(list_id_max.size()); j++){
			coup = list_pieces[list_id_max[j]];
			liste = coup->list();
			
			// vérifier chaque coup de la liste des coups de la piece
			for (int x = 0; x > static_cast<int>(liste.size()); x++){
				if (!(coup_echec(i, liste[x], coup))){
					return false; 
				}
			}

		}
	}
//pour les piece noires
	if (i == -1){
		for (int j = 0; j <= static_cast<int>(list_id_min.size()); j++){
			coup = list_pieces[list_id_min[j]];
			liste = coup->list();
			
			// vérifier chaque coup de la liste des coups de la piece
			for (int x = 0; x > static_cast<int>(liste.size()); x++){
				
				if (!(coup_echec(i, liste[x], coup))){ //si le coup enleve l'échec pas échec et mat
					return false; 
				}
			}
		}
	}
	
//si on continue la le roi est en échec et mat
	return true;
}

bool partie_nulle(int i){
    if (!(roi_echec(i))){
        return echec_mat(i);        //vérifie si un coup peut être joué sans mettre en échec
    }
    else 
        return false;               //si le roi est en échec pas nul
}

bool roi_echec(int i){
	
	if (i == 1){
		piece* coup = list_pieces[16];

//menacé par des cavaliers et des pions
		if ( (Y + 1 < 8 && plateau[X + 2][Y + 1] == -3 && X + 2 < 8)  || 
			 (Y - 1 >= 0 && X + 2 < 8 && plateau[X + 2][Y - 1] == -3) ||
			 (X - 2 >= 0 && Y + 1 < 8 && plateau[X - 2][Y + 1] == -3) || 
			 (X - 2 >= 0 && Y - 1 >= 0 && plateau[X - 2][Y - 1] == -3)||
			 (X + 1 < 8 && Y + 2 < 8 && plateau[X + 1][Y + 2] == -3)  || 
			 (X + 1 < 8 && Y - 2 >= 0 && plateau[X + 1][Y - 2] == -3) ||
			 (X - 1 >= 0 && Y + 2 < 8 && plateau[X - 1][Y + 2] == -3) || 
			 (X - 1 >= 0 && Y - 2 >= 0 && plateau[X - 1][Y - 2] == -3)||
			 (X - 1 >= 0 && Y + 1 < 8 && plateau[X - 1][Y + 1] == -1) ||
			 (X - 1 >= 0 && Y - 1 >= 8 && plateau[X - 1][Y - 1] == -1)){
			   return true;
			}   

//menacé par des tours ou des fous ou des dames
		for (int j = 0; i < 8; j++){  					
			//vérifie si il n'y a pas une piece entre le roi et les attaquants
			if ( (X + j < 8 && plateau[X + j][Y] > 0)  ||
				 (X - j >= 0 && plateau[X - j][Y] > 0) ||
				 (Y + j < 8 && plateau[X][Y + j] > 0)  ||
				 (Y - j >= 0 && plateau[X][Y - j]  > 0)||
				 (X + j < 8 && Y + j < 8 && plateau[X + j][Y + j] > 0)   ||
				 (X - j >= 0 && Y - j >= 0 && plateau[X - j][Y - j] > 0) ||
				 (X - j >= 0 && Y + j < 8 && plateau[X - j][Y + j]  > 0) ||
				 (X + j < 8 && Y - j >= 0 && plateau[X + j][Y - j]  > 0) ){
					 break;
				 }
			//vérifie les pieces qui menacent direct le roi 
			if ( (X + j < 8 && (plateau[X + j][Y] == -2 || plateau[X + j][Y] == -5)) ||
				 (X - j >= 0 && (plateau[X - j][Y] == -2 || plateau[X - j][Y] == -5))||
				 (Y + j < 8 && (plateau[X][Y + j] == -2 || plateau[X][Y + j] == -5)) ||
				 (Y - j >= 0 && (plateau[X][Y - j] == -2 || plateau[X][Y - j] == -5))||
				 (X + j < 8 && Y + j < 8 && (plateau[X + j][Y + j] == -4 || plateau[X + j][Y + j] == -5))  ||
				 (X - j >= 0 && Y - j >= 0 && (plateau[X - j][Y - j] == -4 || plateau[X - j][Y - j] == -5))||
				 (X - j >= 0 && Y + j < 8 && (plateau[X - j][Y + j] == -4 || plateau[X - j][Y + j] == -5)) ||
				 (X + j < 8 && Y - j >= 0 && (plateau[X + j][Y - j] == -4 || plateau[X + j][Y - j] == -5)) ){
					return true;
			}
		}
	
		return false;
	}

	else if (i == -1){
		piece* coup = list_pieces[-16];

//menacé par des cavaliers et des pions
		if ( (Y + 1 < 8 && X + 2 < 8 && plateau[X + 2][Y + 1] == 3)  || 
			 (Y - 1 >= 0 && X + 2 < 8 && plateau[X + 2][Y - 1] == 3) ||
			 (X - 2 >= 0 && Y + 1 < 8 && plateau[X - 2][Y + 1] == 3) || 
			 (X - 2 >= 0 && Y - 1 >= 0 && plateau[X - 2][Y - 1] == 3)||
			 (X + 1 < 8 && Y + 2 < 8 && plateau[X + 1][Y + 2] == 3)  || 
			 (X + 1 < 8 && Y - 2 >= 0 && plateau[X + 1][Y - 2] == 3) ||
			 (X - 1 >= 0 && Y + 2 < 8 && plateau[X - 1][Y + 2] == 3) || 
			 (X - 1 >= 0 && Y - 2 >= 0 && plateau[X - 1][Y - 2] == 3)||
			 (X - 1 >= 0 && Y + 1 < 8 && plateau[X - 1][Y + 1] == 1) ||
			 (X - 1 >= 0 && Y - 1 >= 8 && plateau[X - 1][Y - 1] == 1)){
			   return true;
			}   

//menacé par des tours ou des fous ou des dames
		for (int j = 0; i < 8; j++){  					
			//vérifie si il n'y a pas une piece entre le roi et les attaquants
			if ( (X + j < 8 && plateau[X + j][Y] < 0)  ||
				 (X - j >= 0 && plateau[X - j][Y] < 0) ||
				 (Y + j < 8 && plateau[X][Y + j] < 0)  ||
				 (Y - j >= 0 && plateau[X][Y - j] < 0)||
				 (X + j < 8 && Y + j < 8 && plateau[X + j][Y + j] < 0)   ||
				 (X - j >= 0 && Y - j >= 0 && plateau[X - j][Y - j] < 0) ||
				 (X - j >= 0 && Y + j < 8 && plateau[X - j][Y + j]  < 0) ||
				 (X + j < 8 && Y - j >= 0 && plateau[X + j][Y - j]  < 0) ){
					 break;
				 }
			//vérifie les pieces qui menacent direct le roi 
			if ( (X + j < 8 && (plateau[X + j][Y] == 2 || plateau[X + j][Y] == 5)) ||
				 (X - j >= 0 && (plateau[X - j][Y] == 2 || plateau[X - j][Y] == 5))||
				 (Y + j < 8 && (plateau[X][Y + j] == 2 || plateau[X][Y + j] == 5)) ||
				 (Y - j >= 0 && (plateau[X][Y - j] == 2 || plateau[X][Y - j] == 5))||
				 (X + j < 8 && Y + j < 8 && (plateau[X + j][Y + j] == 4 || plateau[X + j][Y + j] == 5))  ||
				 (X - j >= 0 && Y - j >= 0 && (plateau[X - j][Y - j] == 4 || plateau[X - j][Y - j] == 5))||
				 (X - j >= 0 && Y + j < 8 && (plateau[X - j][Y + j] == 4 || plateau[X - j][Y + j] == 5)) ||
				 (X + j < 8 && Y - j >= 0 && (plateau[X + j][Y - j] == 4 || plateau[X + j][Y - j] == 5)) ){
					return true;
			}
		}
	
		return false;
	}
}

bool coup_echec(int i, std::array<int, 2> coup, piece* piec){
	int copie[8][8];
	bool resultat;
//sauvegarder une copie du plateau de jeu
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			copie[i][j] = ptrplateau[i][j];
		}
	}
	
	plateau[piec->position[0]][piec->position[1]] = 0;
	plateau[coup[0]][coup[1]] = piec->valeur;

	resultat = roi_echec(i);

//retourner la valeur initiale du plateau
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			plateau[i][j] = copie[i][j];
		}
	}

	return resultat;
}

bool fin_partie(){
	// A faire 



};