#include "dames.h"

int main(int argc, char const *argv[])
{
	int nbMovementsTest = 0;
	piece board[boardSize][boardSize];
	piece boardResult[boardSize][boardSize];
	char movementsTest[100], movementsTestExpected[100];

	printf("\n\t\t\t\t========  BIENVENUE AU JEU DE DAMES  ========\n\n");

	// Premier état possible
	initCheckers(*board, boardSize, boardSize, 1);
	initCheckers(*boardResult, boardSize, boardSize, 1);
	board[1][0].player = 1;
	board[0][5].player = 1;
	board[3][0].player = 1;
	board[4][5].player = 1;
	board[4][9].player = 1;
	board[5][2].player = 1;
	board[8][5].player = 1;
	board[8][9].player = 1;
	board[1][8].player = 2;
	board[3][2].player = 2;
	board[2][5].player = 2;
	board[5][2].player = 2;

	boardResult[1][0].player = 1;
	boardResult[0][5].player = 1;
	boardResult[3][0].player = 1;
	boardResult[4][5].player = 1;
	boardResult[4][9].player = 1;
	boardResult[5][2].player = 1;
	boardResult[8][5].player = 1;
	boardResult[8][9].player = 1;
	boardResult[1][8].player = 2;
	boardResult[3][2].player = 2;
	boardResult[2][5].player = 2;
	boardResult[5][2].player = 2;

	printCheckers(*board, boardSize, boardSize);

	// Tests

	printf("Transformation du joueur 2 (O) en dame :\n");
	boardResult[1][8].player = 0;
	boardResult[0][7].player = 2;
	boardResult[0][7].isPiece = 0;
	testMovements(*board, *boardResult,boardSize, boardSize, 2, 1, 0, movementsTest, &nbMovementsTest, 1, 8);

	// Enregistrement des déplacements possibles attendus
	movementsTestExpected[0] = '0';
	movementsTestExpected[1] = 'H';
	movementsTestExpected[2] = '0';
	movementsTestExpected[3] = 'J';

	compareMovements(movementsTest, movementsTestExpected, nbMovementsTest, 2);
	
	printf("Transformation du joueur 1 (X) en dame:\n");
	boardResult[8][5].player = 0;
	boardResult[9][4].player = 1;
	boardResult[9][4].isPiece = 0;
	testMovements(*board, *boardResult,boardSize, boardSize, 1, 1, 0, movementsTest, &nbMovementsTest, 8, 5);

	// Enregistrement des déplacements possibles attendus
	movementsTestExpected[0] = '9';
	movementsTestExpected[1] = 'E';
	movementsTestExpected[2] = '9';
	movementsTestExpected[3] = 'G';

	compareMovements(movementsTest, movementsTestExpected, nbMovementsTest, 2);

	printf("Déplacement normal d'un pion du joueur 2 (O) :\n");
	boardResult[2][5].player = 0;
	boardResult[1][6].player = 2;
	testMovements(*board, *boardResult,boardSize, boardSize, 2, 1, 1, movementsTest, &nbMovementsTest, 2, 5);

	// Enregistrement des déplacements possibles attendus
	movementsTestExpected[0] = '1';
	movementsTestExpected[1] = 'E';
	movementsTestExpected[2] = '1';
	movementsTestExpected[3] = 'G';

	compareMovements(movementsTest, movementsTestExpected, nbMovementsTest, 2);

	printf("Déplacement d'un pion du joueur 1 (X) pour manger un pion du joueur 2 (0) :\n");
	boardResult[0][5].player = 0;
	boardResult[1][6].player = 0;
	boardResult[2][7].player = 1;
	testMovements(*board, *boardResult,boardSize, boardSize, 1, 1, 0, movementsTest, &nbMovementsTest, 0, 5);

	// Enregistrement des déplacements possibles attendus
	movementsTestExpected[0] = '2';
	movementsTestExpected[1] = 'H';

	compareMovements(movementsTest, movementsTestExpected, nbMovementsTest, 1);


	printf("Déplacement d'une dame du joueur 2 (0) :\n");
	boardResult[0][7].player = 0;
	boardResult[1][6].player = 2;
	boardResult[1][6].isPiece = 0;
	testMovements(*board, *boardResult,boardSize, boardSize, 1, 0, 0, movementsTest, &nbMovementsTest, 0, 7);

	// Enregistrement des déplacements possibles attendus
	movementsTestExpected[0] = '1';
	movementsTestExpected[1] = 'G';
	movementsTestExpected[2] = '1';
	movementsTestExpected[3] = 'I';

	compareMovements(movementsTest, movementsTestExpected, nbMovementsTest, 2);

	printf("Déplacement d'une dame du joueur 1 (X) :\n");
	boardResult[9][4].player = 0;
	boardResult[8][5].player = 1;
	boardResult[8][5].isPiece = 0;
	testMovements(*board, *boardResult,boardSize, boardSize, 1, 1, 1, movementsTest, &nbMovementsTest, 9, 4);

	// Enregistrement des déplacements possibles attendus
	movementsTestExpected[0] = '8';
	movementsTestExpected[1] = 'D';
	movementsTestExpected[2] = '8';
	movementsTestExpected[3] = 'F';

	compareMovements(movementsTest, movementsTestExpected, nbMovementsTest, 2);


	printf("Une dame du joueur 2 (0) mange un pion du joueur 1 (X) :\n");
	boardResult[1][6].player = 0;
	boardResult[2][7].player = 0;
	boardResult[3][8].player = 2;
	boardResult[3][8].isPiece = 0;
	testMovements(*board, *boardResult,boardSize, boardSize, 1, 0, 0, movementsTest, &nbMovementsTest, 1, 6);

	// Enregistrement des déplacements possibles attendus
	movementsTestExpected[0] = '3';
	movementsTestExpected[1] = 'I';

	compareMovements(movementsTest, movementsTestExpected, nbMovementsTest, 1);


	printf("Déplacement normal d'un pion du joueur 1 (X) \n");
	boardResult[3][0].player = 0;
	boardResult[4][1].player = 1;
	testMovements(*board, *boardResult,boardSize, boardSize, 1, 0, 0, movementsTest, &nbMovementsTest, 3, 0);

	// Enregistrement des déplacements possibles attendus
	movementsTestExpected[0] = '4';
	movementsTestExpected[1] = 'B';

	compareMovements(movementsTest, movementsTestExpected, nbMovementsTest, 1);


	// Deuxième état possible
	printf("Le jeton 1 mange le dernier jeton 2 et gagne la partie.\n");
	initCheckers(*board, boardSize, boardSize, 1);
	initCheckers(*boardResult, boardSize, boardSize, 1);

	board[2][3].player = 1;
	board[3][2].player = 2;
	printCheckers(*board, boardSize, boardSize);
	boardResult[4][1].player = 1;
	boardResult[3][2].player = 0;
	while(keepPlaying(*board, boardSize, boardSize))
		testMovements(*board, *boardResult,boardSize, boardSize, 1, 1, 0, movementsTest, &nbMovementsTest, 2, 3);
	
	// Enregistrement des déplacements possibles attendus
	movementsTestExpected[0] = '4';
	movementsTestExpected[1] = 'B';

	compareMovements(movementsTest, movementsTestExpected, nbMovementsTest, 1);


	printf("\n\tLa partie est finie.\n");

	return 0;
}