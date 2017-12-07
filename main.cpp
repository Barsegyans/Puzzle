#include "setupdialog.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetupDialog dial;
    QGraphicsView gv;
    if(dial.exec() == QDialog::Accepted)
    {
        GameLogic gl(dial.puzzleSize(),dial.pixmap());

        gv.setScene(&gl);
        gv.show();
        return a.exec();
    }

    return QApplication::exec();
}
