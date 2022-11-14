#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ChessRules(void)
{
	printf( "White is always first to move and players take turns alternately moving one piece at a time. Movement is required. If a player's turn is to move, he is not in check but has no legal moves, this situation is called Stalemate and it ends the game in a draw. Stalemate also occurs when a player makes the same move three times.\n\tEach type of piece has its own method of movement. Go to the glossary to check the moves of each of the pieces. A piece may be moved to another position or may capture an opponent's piece, replacing on its square (en passant being the only exception, check  special moves section). With the exception of the knight, a piece may not move over or through any of the other pieces.\n\t When a king is threatened with capture but can protect himself or escape, it's called check. If a king is in check, then the player must make a move that eliminates the threat of capture and cannot leave the king in check.\n\tCheckmate happens when a king is placed in check and there is no legal move to escape. Checkmate ends the game and the side whose king was checkmated loses.\n ");

	return;	


}
