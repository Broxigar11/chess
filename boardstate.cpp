#include "boardstate.h"
#include <vector>

BoardState::BoardState(Color player1Color)
{
    this->player1Color = player1Color;
    placePieces();
}

std::vector<Position> BoardState::getLegalMoves(Position position) {
    uint8_t piece_i = findPieceByPosition(position);
    std::vector<Position> legalMoves;
    switch (pieces.at(piece_i).getType()) {
    case PAWN: {
        legalMoves = getPawnMoves(piece_i);
        break;
    }
    case KNIGHT: {
        legalMoves = getKnightMoves(piece_i);
        break;
    }
    case ROOK: {
        legalMoves = getRookMoves(piece_i);
        break;
    }
    case BISHOP: {
        legalMoves = getBishopMoves(piece_i);
        break;
    }
    case QUEEN: {
        legalMoves = getQueenMoves(piece_i);
        break;
    }
    case KING: {
        legalMoves = getKingMoves(piece_i);
        break;
    }
    }
    return legalMoves;
};

Piece BoardState::movePiece(Position from, Position to){
    uint8_t movedPiece = findPieceByPosition(from);
    uint8_t capturedI = findPieceByPosition(to);
    pieces.at(movedPiece).setPosition(to);
    pieces.at(movedPiece).incrementMoves();
    Piece piece = pieces.at(movedPiece);
    if(capturedI < 50) {
        pieces.erase(pieces.begin() + capturedI);
    }
    return piece;
};

std::vector<Position> BoardState::getPawnMoves(uint8_t piece_i) {
    std::vector<Position> moves;
    Piece piece = pieces.at(piece_i);
    Color color = piece.getColor();
    Position position = piece.getPosition();
    int8_t direction = getDirection(color);

    if (position.x != 0) {
        Position observedPosition = Position(position.x - 1, position.y + direction);
        if (isPositionOccupied(observedPosition)
                && isPieceAtPositionCapturableWithPiece(piece, observedPosition)) {
            moves.push_back(observedPosition);
        }
    }
    if (position.x != 7) {
        Position observedPosition = Position(position.x + 1, position.y + direction);
        if (isPositionOccupied(observedPosition)
                && isPieceAtPositionCapturableWithPiece(piece, observedPosition)) {
            moves.push_back(observedPosition);
        }
    }
    Position observedPosition = Position(position.x, position.y + direction);
    if (!isPositionOccupied(observedPosition)) {
        moves.push_back(observedPosition);
    }
    // asdawdasdwadsadawd
    Position observedPosition2 = Position(position.x, position.y + direction*2);
    if (!piece.wasMoved()) {
        moves.push_back(observedPosition2);
    }

    return moves;
}

std::vector<Position> BoardState::getKnightMoves(uint8_t piece_i) {
    std::vector<Position> moves;
    Piece piece = pieces.at(piece_i);
    Position position = piece.getPosition();

    int8_t X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int8_t Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    for (uint8_t i = 0; i < 8; i++) {
        Position observedPosition = Position(position.x + X[i], position.y + Y[i]);

        if (!isPositionOutOfBounds(observedPosition) && (!isPositionOccupied(observedPosition)
                   || isPieceAtPositionCapturableWithPiece(piece, observedPosition))) {
            moves.push_back(observedPosition);
        }
    }

    return moves;
};

std::vector<Position> BoardState::getRookMoves(uint8_t piece_i) {
    std::vector<Position> moves;
    Piece piece = pieces.at(piece_i);
    Position position = piece.getPosition();

    for(int8_t i = position.x-1; i >= 0; i--) {
        Position observedPosition = Position(i, position.y);
        if (!isPositionOccupied(observedPosition)) {
            moves.push_back(observedPosition);
        } else if (isPieceAtPositionCapturableWithPiece(piece, observedPosition)) {
            moves.push_back(observedPosition);
            break;
        } else {
            break;
        }
    }
    for(int8_t i = position.x+1; i < 8; i++) {
        Position observedPosition = Position(i, position.y);
        if (!isPositionOccupied(observedPosition)) {
            moves.push_back(observedPosition);
        } else if (isPieceAtPositionCapturableWithPiece(piece, observedPosition)) {
            moves.push_back(observedPosition);
            break;
        } else {
            break;
        }
    }
    for(int8_t j = position.y-1; j >= 0; j--) {
        Position observedPosition = Position(position.x, j);
        if (!isPositionOccupied(observedPosition)) {
            moves.push_back(observedPosition);
        } else if (isPieceAtPositionCapturableWithPiece(piece, observedPosition)) {
            moves.push_back(observedPosition);
            break;
        } else {
            break;
        }
    }
    for(int8_t j = position.x+1; j < 8; j++) {
        Position observedPosition = Position(position.x, j);
        if (!isPositionOccupied(observedPosition)) {
            moves.push_back(observedPosition);
        } else if (isPieceAtPositionCapturableWithPiece(piece, observedPosition)) {
            moves.push_back(observedPosition);
            break;
        } else {
            break;
        }
    }

    return moves;
};

std::vector<Position> BoardState::getBishopMoves(uint8_t piece_i) {
    std::vector<Position> moves;
    Piece piece = pieces.at(piece_i);
    Position position = piece.getPosition();

    for(int8_t i = 1; i <= (position.x < position.y ? position.x : position.y); i++) {
        Position observedPosition = Position(position.x-i, position.y-i);
        if (!isPositionOccupied(observedPosition)) {
            moves.push_back(observedPosition);
        } else if (isPieceAtPositionCapturableWithPiece(piece, observedPosition)) {
            moves.push_back(observedPosition);
            break;
        } else {
            break;
        }
    }
    for(int8_t i = 1; i <= 7 - (position.x > position.y ? position.x : position.y); i++) {
        Position observedPosition = Position(position.x+i, position.y+i);
        if (!isPositionOccupied(observedPosition)) {
            moves.push_back(observedPosition);
        } else if (isPieceAtPositionCapturableWithPiece(piece, observedPosition)) {
            moves.push_back(observedPosition);
            break;
        } else {
            break;
        }
    }
    for(int8_t i = 1; i <= (7-position.x < position.y ? 7-position.x : position.y); i++) {
        Position observedPosition = Position(position.x+i, position.y-i);
        if (!isPositionOccupied(observedPosition)) {
            moves.push_back(observedPosition);
        } else if (isPieceAtPositionCapturableWithPiece(piece, observedPosition)) {
            moves.push_back(observedPosition);
            break;
        } else {
            break;
        }
    }
    for(int8_t i = 1; i <= (position.x < 7-position.y ? position.x : 7-position.y); i++) {
       Position observedPosition = Position(position.x-i, position.y+i);
        if (!isPositionOccupied(observedPosition)) {
            moves.push_back(observedPosition);
        } else if (isPieceAtPositionCapturableWithPiece(piece, observedPosition)) {
            moves.push_back(observedPosition);
            break;
        } else {
            break;
        }
    }
    return moves;
};

std::vector<Position> BoardState::getQueenMoves(uint8_t piece_i) {
    std::vector<Position> moves = getRookMoves(piece_i);
    std::vector<Position> bishopMoves = getBishopMoves(piece_i);
    moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
    return moves;
};

std::vector<Position> BoardState::getKingMoves(uint8_t piece_i) {
    std::vector<Position> moves;
    return moves;
};


bool BoardState::isPositionOccupied(Position position) {
    return findPieceByPosition(position) < 50;
}

bool BoardState::isActualPlayersPiece(Color color, Position position) {
    uint8_t i = findPieceByPosition(position);
    return i < 50 && pieces.at(i).getColor() == color;
};

bool BoardState::isPieceAtPositionCapturableWithPiece(Piece piece, Position position) {
    return piece.getColor() != pieces.at(findPieceByPosition(position)).getColor();
};

uint8_t BoardState::findPieceByPosition(Position position) {
    for (int8_t i = 0; i < pieces.size(); i++) {
        if (pieces.at(i).getPosition().x == position.x
                && pieces.at(i).getPosition().y == position.y) {
            return i;
        }
    }

    return 200;
};


void BoardState::placePieces() {
    uint8_t blackPosition;
    uint8_t whitePosition;
    uint8_t blackPawnPosition;
    uint8_t whitePawnPosition;
    if(player1Color == BLACK) {
        blackPosition = 7;
        whitePosition = 0;
        blackPawnPosition = 6;
        whitePawnPosition = 1;
    } else {
        blackPosition = 0;
        whitePosition = 7;
        blackPawnPosition = 1;
        whitePawnPosition = 6;
    }

    pieces.push_back(Piece(ROOK, BLACK, Position(0, blackPosition)));
    pieces.push_back(Piece(KNIGHT, BLACK, Position(1, blackPosition)));
    pieces.push_back(Piece(BISHOP, BLACK, Position(2, blackPosition)));
    pieces.push_back(Piece(KING, BLACK, Position(3, blackPosition)));
    pieces.push_back(Piece(QUEEN, BLACK, Position(4, blackPosition)));
    pieces.push_back(Piece(BISHOP, BLACK, Position(5, blackPosition)));
    pieces.push_back(Piece(KNIGHT, BLACK, Position(6, blackPosition)));
    pieces.push_back(Piece(ROOK, BLACK, Position(7, blackPosition)));
    for(int8_t i = 0; i < 8; i++) {
        pieces.push_back(Piece(PAWN, BLACK, Position(i, blackPawnPosition)));
    }

    pieces.push_back(Piece(ROOK, WHITE, Position(0, whitePosition)));
    pieces.push_back(Piece(KNIGHT, WHITE, Position(1, whitePosition)));
    pieces.push_back(Piece(BISHOP, WHITE, Position(2, whitePosition)));
    pieces.push_back(Piece(KING, WHITE, Position(3, whitePosition)));
    pieces.push_back(Piece(QUEEN, WHITE, Position(4, whitePosition)));
    pieces.push_back(Piece(BISHOP, WHITE, Position(5, whitePosition)));
    pieces.push_back(Piece(KNIGHT, WHITE, Position(6, whitePosition)));
    pieces.push_back(Piece(ROOK, WHITE, Position(7, whitePosition)));
    for(int8_t i = 0; i < 8; i++) {
        pieces.push_back(Piece(PAWN, WHITE, Position(i, whitePawnPosition)));
    }
}

int8_t BoardState::getDirection(Color color) {
    return color == player1Color ? -1 : 1;
};

bool BoardState::isPositionOutOfBounds(Position position) {
    return !(position.x >= 0 && position.y >= 0 && position.x < 8 && position.y < 8);
};

