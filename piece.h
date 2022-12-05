#ifndef PIECE_H
#define PIECE_H

#include <cstdint>
enum Type {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum Color {
    WHITE,
    BLACK
};

struct Position {
    uint8_t x;
    uint8_t y;

    Position() {
        this->x = 255;
        this->y = 255;
    }

    Position(uint8_t x, uint8_t y) {
        this->x = x;
        this->y = y;
    }

    bool operator==(const Position& rhs) {
        return this->x == rhs.x && this->y == rhs.y;
    }

};

class Piece {
public:
    Piece(Type, Color, Position);
    ~Piece();

    Color getColor() const;
    Type getType() const;
    Position getPosition() const;
    bool getMoved() const;

    void setPosition(Position p);
    void incrementMoves();

private:
    Color color;
    Type type;
    Position position;
    int moves;
    char typeToChar(Type type) const;
    char colorToChar(Color color) const;
};

#endif // PIECE_H
