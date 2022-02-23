#include "header.h"

int main() {
	pion *pionB1 = new pion(1, 0);
	pion *pionB2 = new pion(1, 1);
	pion *pionB3 = new pion(1, 2);
	pion *pionB4 = new pion(1, 3);
	pion *pionB5 = new pion(1, 4);
	pion *pionB6 = new pion(1, 5);
	pion *pionB7 = new pion(1, 6);
	pion *pionB8 = new pion(1, 7);
	tour *tourB1 = new tour(2, 0);
	tour *tourB2 = new tour(2, 1);
	cavalier *cavalB1 = new cavalier(3, 0);
	cavalier *cavalB2 = new cavalier(3, 1);
	fou *fouB1 = new fou(4, 0);
	fou *fouB2 = new fou(4, 1);
	dame *dameB = new dame(5);
	roi *roiB = new roi(6);
	
	pion *pionN1 = new pion(-1, 0);
	pion *pionN2 = new pion(-1, 1);
	pion *pionN3 = new pion(-1, 2);
	pion *pionN4 = new pion(-1, 3);
	pion *pionN5 = new pion(-1, 4);
	pion *pionN6 = new pion(-1, 5);
	pion *pionN7 = new pion(-1, 6);
	pion *pionN8 = new pion(-1, 7);
	tour *tourN1 = new tour(-2, 0);
	tour *tourN2 = new tour(-2, 1);
	cavalier *cavalN1 = new cavalier(-3, 0);
	cavalier *cavalN2 = new cavalier(-3, 1);
	fou *fouN1 = new fou(-4, 0);
	fou *fouN2 = new fou(-4, 1);
	dame *dameN = new dame(-5);
	roi *roiN = new roi(-6);

	for (int i = 1; i < 2; i *= -1){
		bouger_jeu(i);
		
		if (list_pieces[16] == 0){
			std::cout<<"\n\nNoir à gagné !! \n\n\n";
			break;
		}
		else if (list_pieces[-16] == 0){
			std::cout<<"\n\nBlanc à gagné !! \n\n\n";
			break;
		}
	}
	return 0;
}