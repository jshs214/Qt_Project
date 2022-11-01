#include "mainscreenform.h"
#include "ui_mainscreenform.h"
#include <QPixmap>

MainScreenForm::MainScreenForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainScreenForm)
{
    ui->setupUi(this);

    QPixmap pix(":/images/OsstemImage.png");

    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));


}

MainScreenForm::~MainScreenForm()
{
    delete ui;
}
