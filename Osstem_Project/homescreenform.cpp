#include "homescreenform.h"
#include "ui_homescreenform.h"
#include <QPalette>

HomeScreenForm::HomeScreenForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreenForm)
{
    ui->setupUi(this);
    QPixmap bg(":/images/OsstemImage.jpg");

           QPalette p(palette());
           //p.setBrush(QPalette::Background, bg);

           setAutoFillBackground(true);
           setPalette(p);
}

HomeScreenForm::~HomeScreenForm()
{
    delete ui;
}
