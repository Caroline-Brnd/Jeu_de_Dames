#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#define boardSize 10
#define getSign(a) (a < 0) ? -1:1

/// Structure du pion
typedef struct piece
{
	int player;
	int x;
	int y;
	int isPiece;
}piece;

/// Procédure permettant d'initialiser le damier
void initCheckers(piece *, int, int, int);

/// Procédure permettant d'afficher le damier
void printCheckers(piece *, int, int);

/// Fonction qui test si le jeu continu ou si un joueur a perdu
int keepPlaying(piece *, int, int);

/// Fonction qui va enregistrer les coordonnées du pion choisi par l'utilisateur
piece takeInput (piece *, int, int);

/// Fonction qui permet de sélectionner un pion sur le damier
void selectionOfPiece(int, int *, piece *, piece *);

/// Procédure permettant d'enregistrer un mouvement possible
void moveFunction(int *, int *, char *, int, int, int, int);

/// Procédure permettant de chercher les différents mouvements possibles selon les capacités du jeton
void checkMovements(int, piece *, int, piece, int *, int *, int *, int *, char *, char *);

/// Procédure permettant d'afficher les mouvements possibles, pour le jeton sélectionné, à l'utilisateur
void printMove(int, char *);

/// Procédure qui teste les entrées de l'utilisateur puis les enregistre
void recordMovement(int, char *, int *, int *, int);

/// Procédure qui teste si le pion devient une dame en fonction de son emplacement
void becomeDraught(int, int, piece *, int, int *, int *);

/// Procédure qui permet de permuter 2 jetons sur le damier
void permutation(piece *, piece *);

/// Fonction qui teste si le jeton a mangé un autre jeton
int hasJumpEat(int, int, int, piece, int, int);

/// Fonction qui supprime un jeton si nécessaire
void deletePiece(piece *, int, piece, int, int);

/// Fonction de déplacement principal
int move(piece p, piece *, int, int, int, char *, int *);

/// Procédure de comparaison entre 2 jeux de dames
void compareBoard(piece *, piece *, int , int);

/// Procédure permettant d'établir les tests du programme
void testMovements(piece *, piece *, int, int, int, int, int, char *, int *, int, int);

/// Procédure permettant de comparer deux tableaux de déplacements
void compareMovements(char *, char *, int, int);