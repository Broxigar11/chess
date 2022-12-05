#include "boardstate.h"
#include <vector>

std::vector<Piece> pieces;

BoardState::BoardState()
{
    placePieces();
}

void BoardState::placePieces() {
    pieces.push_back(Piece(ROOK, WHITE, Position(0, 0)));
    pieces.push_back(Piece(KNIGHT, WHITE, Position(1, 0)));
    pieces.push_back(Piece(BISHOP, WHITE, Position(2, 0)));
    pieces.push_back(Piece(KING, WHITE, Position(3, 0)));
    pieces.push_back(Piece(QUEEN, WHITE, Position(4, 0)));
    pieces.push_back(Piece(BISHOP, WHITE, Position(5, 0)));
    pieces.push_back(Piece(KNIGHT, WHITE, Position(6, 0)));
    pieces.push_back(Piece(ROOK, WHITE, Position(7, 0)));
    for(int i = 0; i < 8; i++) {
        pieces.push_back(Piece(PAWN, WHITE, Position(i, 1)));
    }
    pieces.push_back(Piece(ROOK, BLACK, Position(0, 7)));
    pieces.push_back(Piece(KNIGHT, BLACK, Position(1, 7)));
    pieces.push_back(Piece(BISHOP, BLACK, Position(2, 7)));
    pieces.push_back(Piece(KING, BLACK, Position(3, 7)));
    pieces.push_back(Piece(QUEEN, BLACK, Position(4, 7)));
    pieces.push_back(Piece(BISHOP, BLACK, Position(5, 7)));
    pieces.push_back(Piece(KNIGHT, BLACK, Position(6, 7)));
    pieces.push_back(Piece(ROOK, BLACK, Position(7, 7)));
    for(int i = 0; i < 8; i++) {
        pieces.push_back(Piece(PAWN, BLACK, Position(i, 6)));
    }
}
