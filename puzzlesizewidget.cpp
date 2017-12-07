#include "puzzlesizewidget.h"

PuzzleSizeWidget::PuzzleSizeWidget(QWidget *parent) : QFrame(parent)
{
    connect(this , SIGNAL(valueChanged(QSize)),this, SLOT(repaint()));
}

QSize PuzzleSizeWidget::value() const {
return size;
}

void PuzzleSizeWidget::setValue(const QSize &s) {
if(size == s || size.height()<m_min.height()|| size.width()<m_min.width()
        || size.height()>m_max.height()|| size.width()>m_max.width() )
    return;
size = s;
emit valueChanged(s);
/*if(old.width() != s.width())
    emit horizontalValueChanged(s.width());
if(old.height() != s.height())
    emit verticalValueChanged(s.height());*/
update();
}

void PuzzleSizeWidget::setPicture(QString pix)
{
    if (m_pixmap.load(pix)) {
       update();
    }
}

void PuzzleSizeWidget::paintEvent(QPaintEvent * event){
QPainter painter(this);
renderValue(&painter);
renderGrid(&painter);
}
QSize PuzzleSizeWidget::cellSize() const {
int w = width();
int h = height();
int mw =m_max.width();
int mh =m_max.height();
int extent = qMin(w/mw, h/mh);
return QSize(extent,extent).expandedTo(QApplication::globalStrut()).expandedTo(QSize(4,4));
}
void PuzzleSizeWidget::renderValue(QPainter *p){

    QSize size(cellSize().width()*value().width(), cellSize().height()*value().height());

    if(!m_pixmap.isNull())
    {
        p->drawPixmap(0,0,m_pixmap.scaled(size));
    }
    else{
        p->setBrush(Qt::darkRed);
        p->drawRect(0,0,size.width(), size.height());
    }
}
void PuzzleSizeWidget::renderGrid(QPainter *p){
     p->setBrush(Qt::NoBrush);
    for(int i=0;i<m_max.width();i++){
        for(int j=0;j<m_max.height();j++){
            p->drawRect(i*cellSize().width(), j*cellSize().height(), cellSize().width(), cellSize().height());
    }
}
}
void PuzzleSizeWidget::mousePressEvent(QMouseEvent *e){
       if(e->button() == Qt::LeftButton)
       {
           if(e->pos().x() < m_max.width()*cellSize().width()
                   && e->pos().y() < m_max.height()*cellSize().height()
                   && e->pos().x() > m_min.width()*cellSize().width()
                   && e->pos().y() > m_min.height()*cellSize().height())
           {
               int x = e->pos().x()/cellSize().width();
               int y = e->pos().y()/cellSize().height();
               setValue(QSize(x+1,y+1));
           }
       }
       else
           return;
}
void PuzzleSizeWidget::mouseMoveEvent(QMouseEvent *e){
    if(e->pos().x() < m_max.width()*cellSize().width()
            && e->pos().y() < m_max.height()*cellSize().height()
            && e->pos().x() > m_min.width()*cellSize().width()
            && e->pos().y() > m_min.height()*cellSize().height())
    {
        int x = e->pos().x()/cellSize().width();
        int y = e->pos().y()/cellSize().height();
        setValue(QSize(x+1,y+1));
    }
    else
        return;
}

QPixmap PuzzleSizeWidget::pixmap()
{

    QSize sz(50*size.width(), 50*size.height());
    return m_pixmap.scaled(sz);
}
