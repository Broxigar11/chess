#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boardstate.h"
#include "piece.h"
#include "qclickablelabel.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow * ui;
    QClickableLabel* board[8][8];
    BoardState* boardState;
    Color currentPlayersTurn = WHITE;

    Position clickedPiecePosition;
    std::vector<Position> possibleMoves;
    bool isClicked = 0;

    Position findSquarePosition(QClickableLabel* square);
    void movePiece(Position from, Position to);
    void initialize_board(Color player1Color);
    void drawPiece(Piece piece);
    void erasePiece(Position position);
    void drawPossibleMoves();
    void erasePossibleMoves();

private slots:
    void SquarePressed();
};
#endif // MAINWINDOW_H
