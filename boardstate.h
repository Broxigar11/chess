#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "piece.h"
#include <vector>

class BoardState
{
public:
    BoardState(Color player1Color);

    std::vector<Position> getLegalMoves(Position position);

private:
    std::vector<Piece> pieces;
    Color player1Color;

    std::vector<Position> getPawnMoves(uint8_t);
    std::vector<Position> getKnightMoves(uint8_t);
    std::vector<Position> getRookMoves(uint8_t);
    std::vector<Position> getBishopMoves(uint8_t);
    std::vector<Position> getQueenMoves(uint8_t);
    std::vector<Position> getKingMoves(uint8_t);

    int8_t getDirection(Color color);

    bool isPositionOccupied(Position position);

    bool isPieceAtPositionCapturableWithPiece(Piece piece, Position position);

    uint8_t findPieceByPosition(Position position);

    void placePieces();



};

#endif // BOARDSTATE_H
