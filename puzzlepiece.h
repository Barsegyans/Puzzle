#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPathItem>
#include <QSize>
#include <QPen>
#include <QVector>
#include <QPainter>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QApplication>

class PuzzlePiece : public QGraphicsPathItem
{
    qreal size=50;
    QPixmap m_pix;
    QSize sceneSize;
    QPoint m_coord;
    QVector <PuzzlePiece *> m_neighbors = QVector<PuzzlePiece *>(4,0);
public:
    enum ConnectorPosition { None, Out, In };
    enum Direction{ North, East, South, West};
    ConnectorPosition conPos[4];
    PuzzlePiece(QWidget *parent = 0);
    PuzzlePiece(ConnectorPosition north, ConnectorPosition east, ConnectorPosition south, ConnectorPosition west);
    void constructShape(QPainterPath &painter);
    void setPixmap(QPixmap pix);
    QPixmap pixmap();
    void setCoordinates(QPoint coord);
    QPoint getCoordinates();
    void setSceneSize(QSize sz);
    QSize getSceneSize();


    void link(PuzzlePiece* neighbor, Direction dir);
    //void mouseMoveEvent(QMouseEvent * event);
    void checkNeighbors(QSet<QPoint> &checked);
    void findneighbor(Direction direction);
    PuzzlePiece::Direction get_reverse(PuzzlePiece::Direction dir);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(QGraphicsPathItem::GraphicsItemChange change, const QVariant &value);

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

};

#endif // PUZZLEPIECE_H
