#include "clientmanager.h"
#include "ui_clientmanager.h"

ClientManager::ClientManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManager)
{
    ui->setupUi(this);
}

ClientManager::~ClientManager()
{
    delete ui;
}
