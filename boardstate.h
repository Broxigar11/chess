#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "piece.h"
#include <vector>

class BoardState
{
public:
    BoardState();
    std::vector<Position> getLegalMoves(Position position);

private:
    std::vector<Piece> pieces;
    uint8_t findPieceByPosition(Position position);
    bool isMovableHorizontalyAndVerticaly(Type type);
    bool isMovableDiagonaly(Type type);
    bool isKnight(Type type);
    bool isPawn(Type type);
    bool isKing(Type type);
    void placePieces();
};

#endif // BOARDSTATE_H
