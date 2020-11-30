#include "dames.h"

/**
 * @param board
 		damier
 * @param height
		hauteur du damier
 * @param width
 		largeur du damier
 * @param zero
 		si l'on veut mettre tout le damier vide, est égal à 1 sinon il est égal à 0
 */
void initCheckers(piece * board, int height, int width, int zero)
{
	int line, col;
	for (line = 0; line < height; ++line)
	{
		for (col = 0; col < width; ++col)
		{
			if ((!(col & 1) && !(line & 1)) || (col & 1 && line & 1))
				board[line * width + col].player = -1;  // Cases interdites
			else
			{
				switch(zero)
				{
					case 0:
						if (line < 4)
							board[line * width + col].player = 1; // Cases des pions noirs (X)

						else if (line > 5) 
							board[line * width + col].player = 2; // Cases des pions blancs (O)
						
						else
							board[line * width + col].player = 0; // Case jouable
						break;
					case 1: // Cas où on crée un damier vide
						board[line * width + col].player = 0;
						break;
				}
				
			}
			
			board[line * width + col].x = col;
			board[line * width + col].y = line; 
			board[line * width + col].isPiece = 1;
		}
	}
}

/**
 * @param board
 		damier
 * @param height
		hauteur du damier
 * @param width
 		largeur du damier
 */
void printCheckers(piece * board, int height, int width)
{
    int i, line, col;
    printf("\t");
    for (i = 0; i < width; ++i)
    {
        printf("   %c", i+65);
    }
    printf("\n");

    for (line = 0; line < height; ++line)
    {
        printf("\t ------------------------------------------\n");
        printf("\t%d", line);
        for (col = 0; col < width; ++col)
        {
            if (board[line * width + col].player != -1 && board[line * width + col].player != 0)
            {
                if(board[line * width + col].isPiece == 1)
                    printf((board[line * width + col].player == 1) > (board[line * width + col].player == 2) ? "| X " : "| O ");
                else if(board[line * width + col].isPiece == 0)
                    printf((board[line * width + col].player == 1) > (board[line * width + col].player == 2) ? "| ψ " : "| ϕ ");
            }
            else
                printf("|   ");
        }
        printf("|\n");
    }
    printf("\t ------------------------------------------\n\n");
}

/**
 * @param board
 		damier
 * @param height
		hauteur du damier
 * @param width
 		largeur du damier
 * @return 1 si le jeu continu sinon 0
 */
int keepPlaying(piece * board, int height, int width)
{
	int line, col;
	int piecesPlayer1 = 0;
	int piecesPlayer2 = 0;
	int unfinished = 1;
	
	for (line = 0; line < height; ++line)
	{
		for (col = 0; col < width; ++col)
		{
			if (board[line * width + col].player == 1)
				piecesPlayer1++; // Compte le nombre de pions du joueur 1
			if (board[line * width + col].player == 2)
				piecesPlayer2++; // Compte le nombre de pions du joueur 2
		}
	}

	if (piecesPlayer2 == 0 || piecesPlayer1 == 0)
		unfinished=0; // Le jeu se termine
	
	return unfinished;
}


/**
 * @param board
 		damier
 * @param height
		hauteur du damier
 * @param width
 		largeur du damier
 * @return le jeton que l'utilisateur a choisi
 */
piece takeInput (piece * board, int width, int height)
{
    int inputY = 0;
    char inputX = 0;
    
    /* Le joueur sélectionne le pion */
    printf("\tEntrez la position de votre pion en abscisse ( LETTRE ) : \n");
    scanf("%s", &inputX);
    inputX = tolower(inputX);
    while((inputX < 'a' || inputX > 'j'))
    {
        inputX = getchar();
        printf("\tErreur ! Entrez à nouveau votre coordonnée ( LETTRE ) : \n");
        scanf("%s", &inputX);
        inputX = tolower(inputX);
    }

    printf("\tEntrez la position de votre pion en ordonnée ( CHIFFRE ) : \n");
    scanf("%d", &inputY);

    while(inputY < 0 || inputY > 9)
    {
        inputY = getchar();
        printf("\tErreur ! Entrez à nouveau votre coordonnée ( CHIFFRE ) : \n");
        scanf("%d", &inputY);
    }
    return board[inputY * width + (inputX - 97)];
}

/**
 * @param c
 		compteur pour savoir qui doit jouer
 * @param player
 		joueur de ce tour
 * @param pieceUser
 		pour enregistrer le jeton du joueur
 * @param board
 		damier
 */
void selectionOfPiece(int c, int * player, piece * pieceUser, piece * board)
{
	if (c % 2 == 0)
		*player = 2;
	else
		*player = 1;

	printf("\t\t\tC'est au joueur %d de jouer\n", *player);


	*pieceUser = takeInput(board, boardSize, boardSize);

	while (pieceUser->player != *player)
	{
		printf("\n\t\t\tERREUR ! Vous ne pouvez pas jouer ce pion !\n\t\t\tIl faut en choisir un autre : \n\n");
		*pieceUser = takeInput(board, boardSize, boardSize);
	}
}

/**
 * @param ptr
 		pointeur qui permet d'ajouter des déplacements possibles dans le tableau
 * @param move
 		indice pour vérifier à gauche ou à droite
 * @param movements
 		tableau de possibilités de déplacements
 * @param moveForY
 		déplacement possible en ordonnée
 * @param moveForX
 		déplacement possible en abscisse
 * @param y
 		position du jeton en ordonnée
 * @param x
 		position du jeton en abscisse
 */
void moveFunction(int *ptr, int * move, char * movements, int moveForY, int moveForX, int y, int x)
{
	movements[(*ptr)++] = y + moveForY + 48;
	movements[(*ptr)++] = x + moveForX + 65;
	*move += 1;
}

/**
 * @param move
 		indice pour vérifier en haut ou en bas
 * @param board
 		damier
 * @param width
 		largeur du damier
 * @param p
 		jeton
 * @param ptrMovementToEat
 		pointeur sur le tableau des possibilités de déplacement pour manger
 * @param ptrMovement
 		pointeur sur le tableau des possibilités de déplacement
 * @param moveToEat
 		indice qui garde le nombre de possibilités de déplacements, pour manger, enregistrés
 * @param toMove
 		indice qui garde le nombre de possibilités de déplacements enregistrés
 * @param movementsToEat
 		tableau de possibilités de déplacements pour manger
 * @param movements
 		tableau de possibilités de déplacements
 */
void checkMovements(int move, piece * board, int width, piece p, int * ptrMovementToEat, int * ptrMovement, int * moveToEat, int * toMove, char * movementsToEat, char * movements)
{
	int moves[] = {-2, 2, -1, 1}, i;
	// Si le jeton peu manger
	 for (i = 0; i < 2; ++i)
	 	if (((board[(p.y + move) * width + (p.x + moves[i])].player == 0 && board[(p.y + (getSign(move))) * width + (p.x + moves[i+2])].player != 0 && board[p.y * width + p.x].player != board[(p.y + (getSign(move))) * width + (p.x + moves[i+2])].player)) && (&board[(p.y + move) * width + (p.x + move)].player >= &board[0 * width + 0].player) && (&board[(p.y + move) * width + (p.x + move)].player <= &board[9 * width + 9].player))
			moveFunction(ptrMovementToEat, moveToEat, movementsToEat, move, moves[i], p.y, p.x);

	// Autres cas (sans manger)
	for (i = 0; i < 2; ++i)
		if ((board[(p.y +(getSign(move))) * width + (p.x + moves[i+2])].player == 0) && (&board[(p.y + (getSign(move))) * width + (p.x + moves[i+2])].player >= &board[0 * width + 0].player) && (&board[(p.y + (getSign(move))) * width + (p.x + moves[i+2])].player <= &board[9 * width + 9].player))
			moveFunction(ptrMovement, toMove, movements, (getSign(move)), moves[i+2], p.y, p.x);
}

/**
 * @param move
 		indice qui contient le nombre de possibilités de déplacements enregistrés
 * @param movements
 		tableau de possibilités de déplacements
 */
void printMove(int move, char * movements)
{
	int i;
	for (i = 0; i < move; ++i)
		printf("\t\t\t%d : %c%c\n", i, movements[i * 2 + 1], movements[i * 2]);
}

/**
 * @param move
		indice qui contient le nombre de possibilités de déplacements enregistrés
 * @param movements
 		tableau de possibilités de déplacements
 * @param y
 		coordonnée en ordonnée
 * @param x
 		coordonnée en abscisse
 * @param selectedMovement
 		le mouvement entré dans le cas d'un test
 */
void recordMovement(int move, char * movements, int * y, int * x, int selectedMovement)
{
	int input = 0;
	if (selectedMovement < 0)
	{	
		scanf("%d", &input);
		while(input > move - 1 || input < 0)
		{
			input = getchar();
			printf("\t\t\tErreur, rentrez à nouveau votre choix :\n");
			scanf("%d", &input);
		}
	}

	else if (selectedMovement >= 0)
	{
		sleep(3);
		printf("%d\n", selectedMovement);
		input = selectedMovement;

		// Pour marquer l'erreur
		if (input > move - 1 || input < 0)
			printf("\t\t\tErreur, rentrez à nouveau votre choix :\n");
		
	}

	// Lorsque le choix correspond aux possibilités, on l'enregistre
	*y = movements[input * 2] - 48;
	*x = movements[input * 2 + 1] - 65;
}

/**
 * @param player
 		joueur 1(X) ou 2(O)
 * @param lastRange
 		Dernière rangée : 0 pour le joueur 2 et 9 pour le joueur 1
 * @param board
 		damier
 * @param width
 		largeur du damier
 * @param y
 		coordonnée en ordonnée
 * @param x
 		coordonnée en abscisse
 */
void becomeDraught(int player, int lastRange, piece * board, int width, int * y, int * x)
{
	if (board[*y * width + *x].player == player)
		if(board[*y * width + *x].y == lastRange)
			board[*y * width + *x].isPiece = 0;
}

/**
 * @param a
 		premier jeton
 * @param b
 		second jeton
 */
void permutation(piece * a, piece * b)
{
	piece temp;

	temp.player = a->player;
	a->player = b->player;
	b->player = temp.player;

	temp.isPiece = a->isPiece;
	a->isPiece = b->isPiece;
	b->isPiece = temp.isPiece;
}

/**
 * @param moveY
 		indice pour vérifier les déplacements en haut ou en bas
 * @param moveX
 		indice pour vérifier à gauche ou à droite
 * @param width
 		largeur du damier
 * @param p
 		jeton
 * @param newY
 		deplacement du joueur en ordonnée
 * @param newX
 		deplacement du joueur en abscisse
 * @return 1 si oui 0 si non
 */
int hasJumpEat(int moveY, int moveX, int width, piece p, int newY, int newX)
{
	if (newY * width + newX == (p.y + moveY) * width + (p.x + moveX))
		return 1;
	return 0;
}

/**
 * @param board
 		damier
 * @param width
 		largeur du damier
 * @param p
 		jeton
 * @param newY
		deplacement du joueur en ordonnée
 * @param newX
 		deplacement du joueur en abscisse
 */
void deletePiece(piece * board, int width, piece p, int newY, int newX)
{
	int moves[][2] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}}, i;
	for (i = 0; i < 4; ++i)
		if (hasJumpEat(moves[i][0], moves[i][1], width, p, newY, newX))
			board[(p.y + (getSign(moves[i][0]))) * width + (p.x + (getSign(moves[i][1])))].player = 0;
}

/**
 * @param board
 		damier
 * @param height
		hauteur du damier
 * @param width
 		largeur du damier
 * @param selectedMovement
 		le mouvement entré dans le cas d'un test
 * @param movementsTest
 		Tableau qui va garder les mouvements proposés à l'utilisateur pour les vérifier
 */
int move(piece p, piece * board, int height, int width, int selectedMovement, char * movementsTest, int *nbMovementsTest)
{
	int toMove = 0, moveToEat = 0, ptrMovement = 0, ptrMovementToEat = 0, newY, newX; 
	char movements[100], movementsToEat[20]; // Va garder nos possibilités pour les proposer à l'utilisateur

	if (p.player == 2) // Pour le tour du joueur 2 (O)
	{
		checkMovements(-2, board, width, p, &ptrMovementToEat, &ptrMovement, &moveToEat, &toMove, movementsToEat, movements);

		// Pour le cas d'une dame
		if (!p.isPiece)
			checkMovements(2, board, width, p, &ptrMovementToEat, &ptrMovement, &moveToEat, &toMove, movementsToEat, movements);
	}

	else if (p.player == 1) // Pour le tour du joueur 1 (X)
	{
		checkMovements(2, board, width, p, &ptrMovementToEat, &ptrMovement, &moveToEat, &toMove, movementsToEat, movements);
			// Pour le cas d'une dame
			if (!p.isPiece)
				checkMovements(-2, board, width, p, &ptrMovementToEat, &ptrMovement, &moveToEat, &toMove, movementsToEat, movements);
	}

	// S'il n'y a aucune possibilité
	if(toMove == 0 && moveToEat == 0)
	{
		printf("\t\t\tAucun mouvement n'est possible !\n");
		return 0;
	}
		
	// Sinon on propose à l'utilisateur les différents mouvements possibles pour son pion
	else
	{
		printf("\n\t\t\tLes mouvements possibles pour ce pion : \n");
		printMove(moveToEat, movementsToEat); // Si le pion mange
		if(!moveToEat) // Mouvement si le pion ne mange pas
			printMove(toMove, movements);

		// Affectation au tableau de test les mouvements proposés à l'utilisateur
		if (moveToEat)
		{
			for (int i = 0; i < moveToEat; ++i)
			{
				movementsTest[i] = movementsToEat[i];
				*nbMovementsTest += 1;
			}
			*nbMovementsTest = moveToEat;
		}
		
		else if(toMove)
		{
			for (int i = 0; i < toMove * 2; ++i)
			{
				movementsTest[i] = movements[i];
			}
			*nbMovementsTest = toMove;
		}
	}
	// Après que l'utilisateur ait choisi son mouvement, on vérifie qu'il est possible
	if (moveToEat) // Si le jeton peut manger
	{
		recordMovement(moveToEat, movementsToEat, &newY, &newX, selectedMovement); // Lorsque le choix correspond aux possibilités, on l'enregistre
		deletePiece(board, width, p, newY, newX); // Suppression du damier du jeton mangé
	}

	// Dans le cas où il n'y avait pas de possibilité de manger
	else 
		recordMovement(toMove, movements, &newY, &newX, selectedMovement);

	permutation(&board[newY * width + newX], &board[p.y * width + p.x]); // On déplace le pion

	// Pour le cas où le déplacement entraîne une transformation en dame
	becomeDraught(2, 0, board, width, &newY, &newX);
	becomeDraught(1, 9, board, width, &newY, &newX);

	printCheckers(board, boardSize, boardSize);

	return 1;
}

/**
 * @param board1
 		premier damier
 * @param board2
 		second damier
 * @param height
		hauteur des damiers
 * @param width
 		largeur des damiers
 */
void compareBoard(piece * board1, piece * board2, int height, int width)
{
	int line, col;

	for (line = 0; line < height; ++line)
	{
		for (col = 0; col < width; ++col)
		{
			if (board1[line * width + col].player != board2[line * width + col].player)
			{
				printf("Erreur de test à la case[%d][%d]! Le résultat attendu était celui ci!\n", line, col);
				printCheckers(board2, boardSize, boardSize);
				return;
			} 
		}
	}
	printf("Test validé ! Le résultat est celui attendu !\n\n");
}


/**
 * @param board
 		damier
 * @param boardResult
 		damier contenant le résultat attendu après le test
  * @param height
 		hauteur du damier
  * @param width
  		largeur du damier
 * @param player
 		joueur 1 ou 2
 * @param isPiece
 		0 pour tester une dame et 1 pour tester un pion
 * @param choice
 		choix testé
 * @param movementsTest 
 		déplacements possibles qui seront enregistrés pour être vérifiés
 * @param nbMovementsTest
 		nombre pour les déplacements possibles
 * @param line
		coordonnée en ordonnée du pion à tester
 * @param col
 		coordonnée en abscisse du pion à tester
 */
void testMovements(piece * board, piece * boardResult, int height, int width, int player, int isPiece, int choice, char * movementsTest, int *nbMovementsTest, int line, int col)
{
	piece pieceUser;
	sleep(3);
	pieceUser = board[line * width + col];
	move(pieceUser, board, height, width, choice, movementsTest, nbMovementsTest);
	compareBoard(board, boardResult, boardSize, boardSize);
}

/**
 * @param movements1
 		premier tableau de déplacements
 * @param movements2
 		deuxième tableau de déplacements
 * @param nbMovements1
 		nombre de possibilités enregistrées dans le premier tableau
 * @param nbMovements2
 		nombre de possibilités enregistrées dans le deuxième tableau
 */
void compareMovements (char * movements1, char * movements2, int nbMovements1, int nbMovements2)
{
	if (nbMovements1 != nbMovements2)
	{
		printf("Erreur ! Les déplacements proposés ne sont pas ceux attendus !\n\n");
		return;
	}

	else if (nbMovements1 == nbMovements2)
	{
		for (int i = 0; i < nbMovements1; ++i)
		{
			if (movements1[i] != movements2[i])
			{
				printf("Erreur ! Les déplacements proposés ne sont pas ceux attendus !\n\n");
				return;
			}
		}
	}
			
	printf("Les déplacements proposés sont bons !\n\n");
}