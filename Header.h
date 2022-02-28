#ifndef HEADER_H
#define HEADER_H

#include <iostream>	 // Partout
#include <iterator>  // Dans inpt, partie.cpp
#include <string>	 // Dans Classes, constructeurs
#include <vector>	 // partout 
#include <limits>	 // Avec Algorithm
#include <tuple>	 // Dans classes partout
#include <array>	
#include <map>


class piece {
public:
	void info();
	void bouger(int i);

	friend bool roi_echec(int i);
	friend bool coup_echec(int i,std::array<int, 2>, piece* coup);
	friend bool echec_mat(int i);
	friend bool partie_nulle(int i);

	virtual ~piece();
	
	std::string nom;

protected:	
	virtual std::vector <std::array<int, 2>> list(){};
	
	std::array<int, 2> position;
	int indentifiant;
	int valeur;
};

class cavalier : public piece {
public:
	cavalier(int bord, int num);

private:
	std::vector <std::array<int, 2>> list();
};
class tour : public piece {
public:
	tour(int bord, int num);
	//void bouger();
private:
	std::vector <std::array<int, 2>> list();
};
class pion : public piece {
public:
	pion(int bord, int num);
	//void bouger();
private:
	std::vector <std::array<int, 2>> list();
};
class fou : public piece {
public:
	fou(int bord, int num);
	//void bouger();
private:
	std::vector <std::array<int, 2>> list();
};
class dame : public piece {
public:
	dame(int bord);
	//void bouger();
private:
	std::vector <std::array<int, 2>> list();
};
class roi : public piece {
public:
	//void bouger();
	roi(int bord);
private:
	std::vector <std::array<int, 2>> list();
};


extern std::vector <int> list_id_min;				// liste des pieces blanches en vie
extern std::vector <int> list_id_max;				// liste des pieces noires en vie
extern std::map<int, piece*> list_pieces;			// ptr des pieces avec ptrplateau
extern int plateau[8][8];							// pour afficher les pieces
extern int ptrplateau[8][8];						// plateau permettant de retrouver le pointeur de la piece avec map list_piece
 

void pPlateau();									// Affiche le plateau
void bouger_jeu(int i);								// Bouge prend l'iput du joueur puis bouge la piece


int inpt(int i); 									// le coup que joue le joueur

bool fin_partie(int i);									// verifie si partie finie (vrai si partie est finie)
bool echec_mat(int i);								// vérifie si échec et mat
bool partie_nulle(int i);							// verifie si partie nulle
bool roi_echec(int i);								// verifie si roi echec 
bool coup_possible_echec(int i, piece* piece);		// verifie si le coup met le roi en echec
bool coups_echec(int i);							// coup légal ?


#endif // HEADER_H