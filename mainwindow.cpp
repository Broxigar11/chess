#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define GET_VARIABLE_NAME(Variable) (#Variable)

QLabel* board[8][8];


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initialize_board();


    QImage image(":/resources/pieces/b_rook.png");

    ui->A1->setPixmap(QPixmap::fromImage(image).scaled(39,39, Qt::KeepAspectRatio, Qt::FastTransformation));


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize_board(){
    board[0][0] = ui->A8;
    board[0][1] = ui->A7;
    board[0][2] = ui->A6;
    board[0][3] = ui->A5;
    board[0][4] = ui->A4;
    board[0][5] = ui->A3;
    board[0][6] = ui->A2;
    board[0][7] = ui->A1;
    board[1][0] = ui->B8;
    board[1][1] = ui->B7;
    board[1][2] = ui->B6;
    board[1][3] = ui->B5;
    board[1][4] = ui->B4;
    board[1][5] = ui->B3;
    board[1][6] = ui->B2;
    board[1][7] = ui->B1;
    board[2][0] = ui->C8;
    board[2][1] = ui->C7;
    board[2][2] = ui->C6;
    board[2][3] = ui->C5;
    board[2][4] = ui->C4;
    board[2][5] = ui->C3;
    board[2][6] = ui->C2;
    board[2][7] = ui->C1;
    board[3][0] = ui->D8;
    board[3][1] = ui->D7;
    board[3][2] = ui->D6;
    board[3][3] = ui->D5;
    board[3][4] = ui->D4;
    board[3][5] = ui->D3;
    board[3][6] = ui->D2;
    board[3][7] = ui->D1;
    board[4][0] = ui->E8;
    board[4][1] = ui->E7;
    board[4][2] = ui->E6;
    board[4][3] = ui->E5;
    board[4][4] = ui->E4;
    board[4][5] = ui->E3;
    board[4][6] = ui->E2;
    board[4][7] = ui->E1;
    board[5][0] = ui->F8;
    board[5][1] = ui->F7;
    board[5][2] = ui->F6;
    board[5][3] = ui->F5;
    board[5][4] = ui->F4;
    board[5][5] = ui->F3;
    board[5][6] = ui->F2;
    board[5][7] = ui->F1;
    board[6][0] = ui->G8;
    board[6][1] = ui->G7;
    board[6][2] = ui->G6;
    board[6][3] = ui->G5;
    board[6][4] = ui->G4;
    board[6][5] = ui->G3;
    board[6][6] = ui->G2;
    board[6][7] = ui->H1;
    board[7][0] = ui->H8;
    board[7][1] = ui->H7;
    board[7][2] = ui->H6;
    board[7][3] = ui->H5;
    board[7][4] = ui->H4;
    board[7][5] = ui->H3;
    board[7][6] = ui->H2;
    board[7][7] = ui->H1;
}
