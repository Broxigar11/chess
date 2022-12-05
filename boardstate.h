#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "piece.h"
#include <vector>

class BoardState
{
public:
    BoardState();

private:
    std::vector<Piece> pieces;
    void placePieces();
};

#endif // BOARDSTATE_H
