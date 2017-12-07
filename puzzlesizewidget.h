#ifndef PUZZLESIZEWIDGET_H
#define PUZZLESIZEWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>

class PuzzleSizeWidget : public QFrame
{
    Q_OBJECT
    QSize m_min=QSize(1,1);
    QSize m_max=QSize(8,8);

public:
    PuzzleSizeWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    QSize value() const;
    QSize size=QSize(5,5);
    void mousePressEvent( QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void setValue(const QSize &s);
    QPixmap pixmap();
    void setPicture(QString pix);
    QPixmap m_pixmap;

    Q_PROPERTY(QSize value READ value WRITE setValue)
    QSize cellSize() const;
    void renderValue(QPainter *p);
    void renderGrid(QPainter *p);
signals:
    void valueChanged(const QSize&);
    void horizontalValueChanged(int);
    void verticalValueChanged(int);
};

#endif // PUZZLESIZEWIDGET_H
