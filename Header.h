#ifndef HEADER_H
#define HEADER_H
#include <algorithm> // Dans void inpt, Partie.cpp
#include <iostream>	 // Partout
#include <iterator>  // Dans inpt, partie.cpp
#include <string>	 // Dans Classes, constructeurs
#include <vector>	 // Dans 
#include <limits>
#include <tuple>
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


extern std::vector <int> list_id_min;
extern std::vector <int> list_id_max;
extern std::map<int, piece*> list_pieces;
extern int plateau[8][8];
extern int ptrplateau[8][8];


void pPlateau();
void bouger_jeu(int i);


int inpt(int i); 									// le coup que joue le joueur

bool fin_partie();									// verifie si partie finie
bool echec_mat(int i);								// vérifie si échec et mat
bool partie_nulle(int i);							// verifie si partie nulle
bool roi_echec(int i);								// verifie si roi echec 
bool coup_possible_echec(int i, piece* piece);		// verifie si le coup met le roi en echec
bool coups_echec(int i);							// coup légal ?


#endif // HEADER_H