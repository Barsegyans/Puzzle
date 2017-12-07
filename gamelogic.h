#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QWidget>
#include "puzzlepiece.h"
#include<QTime>
#include <QGraphicsScene>
#include <QPixmap>

class GameLogic : public QGraphicsScene
{
public:
    GameLogic(QSize size, QPixmap img);
    void setup(QSize size, QPixmap pixmap);
    PuzzlePiece::ConnectorPosition reverse(PuzzlePiece::ConnectorPosition pos);
};

#endif // GAMELOGIC_H
