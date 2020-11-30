	#include "dames.h"

int main(int argc, char const *argv[])
{
	int turn = 0, player = 0, hasMoved = 0, nbMovementsTest = 0;
	piece pieceUser, board[boardSize][boardSize];
	char movementTest[0];

	printf("\n\t\t\t\t========  BIENVENUE AU JEU DE DAMES  ========\n\n");

	initCheckers(*board, boardSize, boardSize, 0);

	printCheckers(*board, boardSize, boardSize);

	// Le jeu se termine lorsque l'un des joueurs n'a plus de jetons
	while(keepPlaying(*board, boardSize, boardSize))
	{
		selectionOfPiece(turn, &player, &pieceUser, *board);

		hasMoved = move(pieceUser, *board, boardSize, boardSize, -1, movementTest, &nbMovementsTest);

		while (!hasMoved)
		{
			selectionOfPiece(turn, &player, &pieceUser, *board);

			hasMoved = move(pieceUser, *board, boardSize, boardSize, -1, movementTest, &nbMovementsTest);
		}
		turn++;
	}

	printf("\n\tLa partie est finie.\n");

	return 0;
}