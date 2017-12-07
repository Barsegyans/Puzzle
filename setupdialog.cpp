#include "SetupDialog.h"
#include "ui_SetupDialog.h"
#include <QDebug>
#include <QPalette>
#include <QFileDialog>
#include <QImageReader>

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),SLOT(on_pushButton_Ok_clicked()));
    connect(ui->pushButton_Browse_2,SIGNAL(clicked(bool)),SLOT(on_pushButton_Browse_clicked()));

}

QSize SetupDialog::puzzleSize()
{
 return ui->frame_3->size;
}

QPixmap SetupDialog::pixmap(){
    return ui->frame_3->pixmap();

}

SetupDialog::~SetupDialog()
{
    delete ui;
}


void SetupDialog::on_pushButton_Browse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),"/home",tr("Images (*.png *.xpm *.jpg)"));
    if (!fileName.isEmpty()){
        ui->lineEdit_2->setText(fileName);
        ui->frame_3->setPicture(fileName);
    }
}

void SetupDialog::on_pushButton_Ok_clicked()
{
    if(!pixmap().isNull()){
    accept();
    }
    else{
          QMessageBox::information(0,"Ошибка","Вы не выбрали правильное изображение!");
    }
}
