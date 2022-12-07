#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Color player1Color = BLACK;
    MainWindow::boardState = new BoardState(player1Color);

    initialize_board(player1Color);

    qInfo() << boardState->isPositionOccupied(Position(0, 0));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize_board(Color player1Color){
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            QString squareName = QString(QChar(i+65)) + QString(QChar(56-j));
            board[i][j] = (QClickableLabel* )MainWindow::findChild<QClickableLabel *>(squareName);
            connect(board[i][j], SIGNAL(clicked()), this, SLOT(SquarePressed()));
        }
    }

    Type types[8] = {
        ROOK, KNIGHT, BISHOP, KING,
        QUEEN, BISHOP, KNIGHT, ROOK
    };

    uint8_t blackPieceI;
    uint8_t blackPawnI;
    uint8_t whitePieceI;
    uint8_t whitePawnI;

    if (player1Color == BLACK) {
        blackPieceI = 7;
        blackPawnI = 6;
        whitePieceI = 0;
        whitePawnI = 1;
    } else {
        blackPieceI = 0;
        blackPawnI = 1;
        whitePieceI = 7;
        whitePawnI = 6;
    }

    for (uint8_t i = 0; i < 8; i++) {
        drawPiece(Piece(types[i], BLACK, Position(i, blackPieceI)));
        drawPiece(Piece(PAWN, BLACK, Position(i, blackPawnI)));
        drawPiece(Piece(types[i], WHITE, Position(i, whitePieceI)));
        drawPiece(Piece(PAWN, WHITE, Position(i, whitePawnI)));
    }

}


Position MainWindow::findSquarePosition(QClickableLabel* square) {
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            if (square == board[i][j]) {
                return Position(i, j);
            }
        }
    }
    return Position(10, 10);
}

void MainWindow::movePiece(Position from, Position to) {
    Piece piece = boardState->movePiece(from, to);
    drawPiece(piece);
    erasePiece(from);
    currentPlayersTurn = currentPlayersTurn == WHITE ? BLACK : WHITE;
}

void MainWindow::drawPiece(Piece piece) {
    QString imagePath = ":/resources/pieces/";
    imagePath += piece.getColor()==BLACK ? "b_" : "w_";
    switch (piece.getType()) {
    case PAWN:
        imagePath += "pawn";
        break;
    case ROOK:
        imagePath += "rook";
        break;
    case KNIGHT:
        imagePath += "knight";
        break;
    case BISHOP:
        imagePath += "bishop";
        break;
    case QUEEN:
        imagePath += "queen";
        break;
    case KING:
        imagePath += "king";
        break;
    }
    imagePath += ".png";

    Position position = piece.getPosition();
    QImage image(imagePath);

    board[position.x][position.y]
            ->setPixmap(QPixmap::fromImage(image)
                        .scaled(39,39, Qt::KeepAspectRatio, Qt::FastTransformation));
}

void MainWindow::erasePiece(Position position) {
    QPixmap pixmap;
    board[position.x][position.y]->setPixmap(pixmap);
}

void MainWindow::drawPossibleMoves() {
    for (Position position : possibleMoves) {
        if (!boardState->isPositionOccupied(position)) {
            board[position.x][position.y]->setStyleSheet("background-color: #31b261");
        } else {
            board[position.x][position.y]->setStyleSheet("background-color: #7b140c");
        }
    }
}

void MainWindow::erasePossibleMoves() {
    for (Position position : possibleMoves) {
        board[position.x][position.y]->setStyleSheet("");
    }
}

void MainWindow::SquarePressed() {
    QClickableLabel* thisSquare = (QClickableLabel*)sender();
    Position thisPosition = findSquarePosition(thisSquare);

    if (isClicked) {
        if (std::count(possibleMoves.begin(), possibleMoves.end(), thisPosition) > 0) {
            erasePossibleMoves();
            movePiece(clickedPiecePosition, thisPosition);
            isClicked = false;
            possibleMoves.clear();
        } else {
            if (boardState->isActualPlayersPiece(currentPlayersTurn, thisPosition)) {
                erasePossibleMoves();
                possibleMoves.clear();
                clickedPiecePosition = thisPosition;
                possibleMoves = boardState->getLegalMoves(thisPosition);
                drawPossibleMoves();
            } else {
                isClicked = false;
                erasePossibleMoves();
                possibleMoves.clear();
            }
        }
    } else if (boardState->isActualPlayersPiece(currentPlayersTurn, thisPosition)) {
        isClicked = true;
        clickedPiecePosition = thisPosition;
        possibleMoves = boardState->getLegalMoves(thisPosition);
        qInfo() << possibleMoves.size();
        drawPossibleMoves();
    }
}
