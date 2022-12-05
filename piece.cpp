#include "piece.h"

Piece::Piece(Type t, Color c, Position p) {
    type = t;
    color = c;
    position = p;
    moves = 0;
}

Piece::~Piece(){

}

Color Piece::getColor() const {
    return color;
}

Type Piece::getType() const {
    return type;
}

Position Piece::getPosition() const {
    return position;
}

bool Piece::getMoved() const {
    return moves > 0;
}

void Piece::setPosition(Position p) {
    position.x = p.x;
    position.y = p.y;
}

void Piece::incrementMoves() {
    moves++;
}

/* Enum converters */
char Piece::typeToChar(Type type) const {
    switch(type) {
        case PAWN: return 'P';
        case KNIGHT: return 'N';
        case BISHOP: return 'B';
        case ROOK: return 'R';
        case QUEEN: return 'Q';
        case KING: return 'K';
        default: return ' ';
    }
}

char Piece::colorToChar(Color color) const {
    switch(color) {
        case WHITE: return 'W';
        case BLACK: return 'B';
        default: return ' ';
    }
}
