#ifndef CHESSBOARD_H
#define CHESSBOARD_H


#define BOARD_SIZE 8

#include <QObject>
#include <QDebug>

#include "board/square.h"
#include "player/player.h"

class ChessBoard : public QObject
{
    Q_OBJECT
public:
    explicit ChessBoard(Player *currentPlayer, int gametype, QObject *parent = 0);
    ChessBoard(const ChessBoard &board);

    // TODO move intitialization to constructor
    const int m_direction[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

    Square *getSquare(int x, int y) const;
    Square::State getSquareState(int x, int y);
    int gametype;
    void newBoard();
    bool clicked = false;

    void setPlayers();

    /**
     * @brief countDisks count number of black, white and total disks
     * and store it in the corresponding member variables.
     */
    void countDisks(void);

    int m_numberOfBlackDisks;
    int m_numberOfWhiteDisks;
    int m_numberOfDisks;
    int m_pieceState[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0}};

    bool m_gameOver;


    /**
     * @brief legalMove check if the move at position (x,y) is legal.
     * @param x
     * @param y
     * @return
     */
    bool legalMove(int x0, int y0, int x, int y);

    /**
     * @brief getLegalMoves fill the provided QVector legalMoves with Squares
     * that are allowed to place disks on for the current player.
     * @param legalMoves
     * @return
     */
    bool getLegalMoves(QVector<Square *> *legalMoves);

    QVector<Square* > *m_legalMoves;

    QVector<ChessBoard *> makeLegalMoves();

    /**
     * @brief makeMove actually make a move that is legal.
     * @param x
     * @param y
     */
    void makeMove(int x0, int y0, int x, int y);
    //bool findLegalMoves(bool *legalMoves);

    /**
     * @brief undoMove get the last board from the board stack.
     * @return true if undo was possible.
     */
    bool undoMove();

    /**
     * @brief onBoard checks if a position is on the board
     * @param x
     * @param y
     * @return
     */
    bool onBoard(int x, int y);

    /**
     * @brief getOtherPlayer get the color of opponent
     * @param currentPlayer
     * @return
     */
    Player::Color getOtherPlayer(Player *currentPlayer);



    QVector<QVector<Square* > > m_boardMatrix;
    Player *m_currentPlayer;


signals:
    void signalBoardChanged(int x, int y, Player::Color color);

public slots:
};

#endif // CHESSBOARD_H
