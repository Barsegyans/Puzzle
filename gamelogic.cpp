#include "gamelogic.h"
#include<QDebug>
GameLogic::GameLogic(QSize size, QPixmap img)
{

    setup(size, img);
}

void GameLogic::setup(QSize size, QPixmap pixmap)
{
    qsrand(QTime::currentTime().msec());
    clear();
    qDebug()<<size;
    PuzzlePiece::ConnectorPosition left;
    PuzzlePiece::ConnectorPosition buff[size.width()];
    for(int i=0;i<size.width();i++){
        buff[i]=PuzzlePiece::None;
    }
    for(int i = 0; i < size.height(); i++)
    {
        left = PuzzlePiece::None;
        for(int j = 0; j < size.width(); ++j)
        {
            PuzzlePiece::ConnectorPosition puz[4];
            puz[0] = buff[j];
            puz[1] = qrand() % 2 ? PuzzlePiece::In : PuzzlePiece::Out; //E
            puz[2] = qrand() % 2 ? PuzzlePiece::In : PuzzlePiece::Out; //S
            puz[3] = left;
            buff[j]= reverse(puz[2]);
            left =reverse(puz[1]);

            if(j==size.width()-1)
                puz[1] = PuzzlePiece::None;
            if(i==size.height()-1)
                puz[2] = PuzzlePiece::None;
            PuzzlePiece *piece = new PuzzlePiece(puz[0], puz[1], puz[2], puz[3]);
            addItem(piece);

            QRect rect = piece->boundingRect().toRect();
            int cellSize = 50;
            rect.translate(cellSize/2+j*cellSize, cellSize/2+i*cellSize);
            QPixmap pix = pixmap.copy(rect);
            piece->setPixmap(pix);
            piece->setCoordinates(QPoint(i,j));
            piece->setSceneSize(size);
            //qDebug()<<QPoint(qrand() % (size.width())*cellSize, qrand() % (size.height())*cellSize);
            piece->setPos(QPoint(qrand() % (size.width())*cellSize, qrand() % (size.height())*cellSize));
        }

    }
}
PuzzlePiece::ConnectorPosition GameLogic::reverse(PuzzlePiece::ConnectorPosition pos)
{
    switch(pos)
    {
        case PuzzlePiece::None: return PuzzlePiece::None;
        case PuzzlePiece::In: return PuzzlePiece::Out;
        case PuzzlePiece::Out: return PuzzlePiece::In;
    }
    return PuzzlePiece::None;
}



