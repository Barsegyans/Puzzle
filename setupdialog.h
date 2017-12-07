#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include <QSize>
#include <QGraphicsView>
#include "gamelogic.h"
#include <QMessageBox>

namespace Ui {
class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = 0);
    QString m_imageFilePath;
    QSize m_puzzleSize=QSize(5,5);
    QSize puzzleSize();
    QPixmap pixmap();
    ~SetupDialog();
private slots:
    void on_pushButton_Browse_clicked();
    void on_pushButton_Ok_clicked();


private:
    Ui::SetupDialog *ui;
};

#endif // SETUPDIALOG_H
