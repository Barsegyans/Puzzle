#include "puzzlepiece.h"
#include <QDebug>

PuzzlePiece::PuzzlePiece(ConnectorPosition north, ConnectorPosition east,
                         ConnectorPosition south, ConnectorPosition west)
{
    conPos[0]=north;
    conPos[1]=east;
    conPos[2]=south;
    conPos[3]=west;
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    QPainterPath painter;
    constructShape(painter);
    setPath(painter);
}

void PuzzlePiece::constructShape(QPainterPath &painter)
{
    painter.moveTo(-1*size/2,-1*size/2);


    if(conPos[0]==None){
        painter.lineTo(size/2,-1*size/2);
    }else if(conPos[0]==In){
        painter.lineTo(-1*size/5, -1*size/2);
        painter.arcTo(-1*size/5,-3*size/4, 2*size/5, 2*size/5,180,180);
        painter.lineTo(size/2, -1*size/2);
    }else{
        painter.lineTo(-1*size/5, -1*size/2);
        painter.arcTo(-1*size/5,-3*size/4, size/2, size/2,180,-180);
        painter.lineTo(size/2, -1*size/2);
    }

    if(conPos[1]==None){
        painter.lineTo(size/2,size/2);
    }else if(conPos[1]==In){
        painter.lineTo(size/2, -1*size/5);
        painter.arcTo(3*size/10,-1*size/5, 2*size/5, 2*size/5 ,90,180);
        painter.lineTo(size/2, size/2);
    }else{
        painter.lineTo(size/2, -1*size/5);
        painter.arcTo(3*size/10,-1*size/5, 2*size/5, 2*size/5 ,90,-180);
        painter.lineTo(size/2, size/2);
    }

    if(conPos[2]==None){
        painter.lineTo(-1*size/2,size/2);
    }else if(conPos[2]==In){
        painter.lineTo(size/5,size/2);
        painter.arcTo(-1*size/5,3*size/10, 2*size/5, 2*size/5,0,180);
        painter.lineTo(-1*size/2, size/2);
    }else{
        painter.lineTo(size/5,size/2);
        painter.arcTo(-1*size/5,3*size/10, 2*size/5, 2*size/5,0,-180);
        painter.lineTo(-1*size/2, size/2);
    }

    if(conPos[3]==None){
        painter.lineTo(-1*size/2,-1*size/2);
    }else if(conPos[3]==In){
        painter.lineTo(-1*size/2, size/5);
        painter.arcTo(-7*size/10,-1*size/5, 2*size/5, 2*size/5 ,-90,180);
        painter.lineTo(-1*size/2,-1*size/2);
    }else{
        painter.lineTo(-1*size/2, size/5);
        painter.arcTo(-7*size/10,-1*size/5, 2*size/5, 2*size/5 ,-90,-180);
        painter.lineTo(-1*size/2,-1*size/2);
    }


    painter.closeSubpath();
}



QPixmap PuzzlePiece::pixmap()
{
    return m_pix;
}
void PuzzlePiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setClipPath(path());
    QRect rect = boundingRect().toRect();

    painter->setPen(QPen(Qt::black, 3));
    painter->drawPixmap(rect, m_pix.scaled(rect.width(),rect.height()));
    painter->drawPath(path());
}
void PuzzlePiece::setPixmap(QPixmap pix)
{
    m_pix=pix;

    update();
}
void PuzzlePiece::setCoordinates(QPoint coord)
{
    m_coord = coord;
}

QPoint PuzzlePiece::getCoordinates()
{
    return m_coord;
}

 void PuzzlePiece::link(PuzzlePiece *neighbor, PuzzlePiece::Direction dir)
{
    m_neighbors[dir]=neighbor;

}

void PuzzlePiece::checkNeighbors(QSet<QPoint> &checked)
{
    if(checked.contains(m_coord))  return; // условия прерывания рекурсии
    checked.insert(m_coord); // запомнить посещенный элемент
    findneighbor(North); // найти N соседа
    findneighbor(East); // найти E соседа
    findneighbor(South); // найти S соседа
    findneighbor(West); // найти W соседа
    // рекурсивные вызовы:
    if(m_neighbors[North])
    m_neighbors[North]->checkNeighbors(checked);
    if(m_neighbors[East])
    m_neighbors[East]->checkNeighbors(checked);
    if(m_neighbors[South])
    m_neighbors[South]->checkNeighbors(checked);
    if(m_neighbors[West])
        m_neighbors[West]->checkNeighbors(checked);
}

void PuzzlePiece::findneighbor(PuzzlePiece::Direction direction)
{
    if (m_neighbors[direction])
        return;
    PuzzlePiece* neib;

    switch(direction)
    {
        case PuzzlePiece::North:
        {
            neib = (PuzzlePiece*)(scene()->itemAt(pos().x(),pos().y()-50,QTransform()));
            if(!neib) return;
            if((neib->getCoordinates().x() == getCoordinates().x()-1) && (neib->getCoordinates().y() == getCoordinates().y()))
            {
                link(neib, direction);
                neib->link(this, get_reverse(direction));
                neib->setPos(pos().x(),pos().y()-50);
            }

            break;
        }
        case PuzzlePiece::East:
        {
            neib = (PuzzlePiece*)(scene()->itemAt(pos().x()+50,pos().y(),QTransform()));
            if(!neib) return;
            if((neib->getCoordinates().x() == getCoordinates().x()) && (neib->getCoordinates().y() == getCoordinates().y()+1))
            {
                link(neib, direction);
                neib->link(this, get_reverse(direction));
                neib->setPos(pos().x()+50,pos().y());
            }
            break;
        }
        case PuzzlePiece::South:
        {
            neib = (PuzzlePiece*)(scene()->itemAt(pos().x(),pos().y()+50,QTransform()));
            if(!neib) return;
            if((neib->getCoordinates().x() == getCoordinates().x()+1) && (neib->getCoordinates().y() == getCoordinates().y()))
            {
                link(neib, direction);
                neib->link(this, get_reverse(direction));
                neib->setPos(pos().x(),pos().y()+50);
            }

            break;
        }
        case PuzzlePiece::West:
        {
            neib = (PuzzlePiece*)(scene()->itemAt(pos().x()-50,pos().y(),QTransform()));
            if(!neib) return;
            if((neib->getCoordinates().x() == getCoordinates().x()) && (neib->getCoordinates().y() == getCoordinates().y()-1))
            {
                link(neib, direction);
                neib->link(this, get_reverse(direction));
                neib->setPos(pos().x()-50,pos().y());
            }

            break;
        }
    }

}
PuzzlePiece::Direction PuzzlePiece::get_reverse(PuzzlePiece::Direction dir)
{
    switch(dir)
    {
        case PuzzlePiece::North: return PuzzlePiece::South;
        case PuzzlePiece::South: return PuzzlePiece::North;
        case PuzzlePiece::East: return PuzzlePiece::West;
        case PuzzlePiece::West: return PuzzlePiece::East;
    }
    return PuzzlePiece::North;
}


inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}

void PuzzlePiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    QSet<QPoint> checked;
    checkNeighbors(checked);
    int p_num = sceneSize.width()*sceneSize.height();
    if(checked.count() == p_num)
    {
        QMessageBox::information(0, "The end","We have a winner!!!", QMessageBox::Close);

    }

    QGraphicsPathItem::mouseReleaseEvent(event);
}

QVariant PuzzlePiece::itemChange(QGraphicsPathItem::GraphicsItemChange change, const QVariant &value)
{
    if (change==ItemPositionHasChanged)
       {
           QPoint new_pos=value.toPoint();
           if (m_neighbors[North]) m_neighbors[North]->setPos(new_pos.x(),new_pos.y()-50);
           if (m_neighbors[East]) m_neighbors[East]->setPos(new_pos.x()+50,new_pos.y());
           if (m_neighbors[South]) m_neighbors[South]->setPos(new_pos.x(),new_pos.y()+50);
           if (m_neighbors[West]) m_neighbors[West]->setPos(new_pos.x()-50,new_pos.y());

       }
    return QGraphicsPathItem::itemChange(change, value);
}

void PuzzlePiece::setSceneSize(QSize sz)
{
    sceneSize=sz;
}

QSize PuzzlePiece::getSceneSize()
{
    return sceneSize;
}


