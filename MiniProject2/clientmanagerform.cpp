#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"
#include "clientitem.h"

#include <QFile>
#include <QMenu>
#include <QMessageBox>

ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{
    ui->setupUi(this);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));


    QFile file("clientlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            ClientItem* c = new ClientItem(id, row[1], row[2], row[3]);
            ui->treeWidget->addTopLevelItem(c);
            clientList.insert(id, c);
        }
    }
    file.close( );
}

ClientManagerForm::~ClientManagerForm()
{
    delete ui;

    QFile file("clientlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : clientList) {
        ClientItem* c = v;
        out << c->id() << ", " << c->getName() << ", ";
        out << c->getPhoneNumber() << ", ";
        out << c->getAddress() << "\n";
    }
    file.close( );
}

int ClientManagerForm::makeId( )
{
    if(clientList.size( ) == 0) {
        return 1000;
    } else {
        auto id = clientList.lastKey();
        return ++id;
    }
}

void ClientManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        clientList.remove(item->text(0).toInt());
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));

        ui->treeWidget->update();
    }
}

void ClientManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ClientManagerForm::on_searchPushButton_clicked()
{
    ui->label->setText("검색 결과");

    int i = ui->searchComboBox->currentIndex();
    for (const auto& v : clientList) {
        ClientItem* c = v;
        c->setHidden(true); //고객리스트 히든
    }
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), flag, i);
        foreach(auto i, items) {
            i->setHidden(false);    //검색된 리스트만 출력되게
            ClientItem* c = static_cast<ClientItem*>(i);
            c->id();
            QString name = c->getName();
            QString number = c->getPhoneNumber();
            QString address = c->getAddress();

        }
    }
}

void ClientManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        ClientItem* c = clientList[key];
        QString name, number, address;
        name = ui->nameLineEdit->text();
        number = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        c->setName(name);
        c->setPhoneNumber(number);
        c->setAddress(address);
        clientList[key] = c;
    }
}

void ClientManagerForm::on_addPushButton_clicked()
{
    if(ui->label->text() != "고객정보관리")
    {
        QMessageBox::information(this, "오류",
                                 QString("검색창입니다.\n%고객정보관리창으로 이동하세요."));
        return;
    }
    QString name, number, address;
    int id = makeId( );
    name = ui->nameLineEdit->text();
    number = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();
    if(name.length() && number.length() && address.length()) {
        ClientItem* c = new ClientItem(id, name, number, address);
        clientList.insert(id, c);
        ui->treeWidget->addTopLevelItem(c);

        ui->nameLineEdit->clear();
        ui->phoneNumberLineEdit->clear();
        ui->addressLineEdit->clear();
    }
}

void ClientManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->nameLineEdit->setText(item->text(1));
    ui->phoneNumberLineEdit->setText(item->text(2));
    ui->addressLineEdit->setText(item->text(3));
}


void ClientManagerForm::on_pushButton_clicked()
{
    qApp->quit();
}

void ClientManagerForm::receiveClientName(QString str)  //Order에서 이름을 받아 emit
{
    auto flag =  Qt::MatchCaseSensitive|Qt::MatchContains;
    {
        auto items = ui->treeWidget->findItems(str, flag,1);        //이름이므로 1
        foreach(auto i, items) {
            ClientItem* c = static_cast<ClientItem*>(i);
            int id = c->id();
            QString name = c->getName();
            QString number = c->getPhoneNumber();
            QString address = c->getAddress();
            ClientItem* item = new ClientItem(id, name, number, address);

            emit clientdataSent(item);
        }
    }
}

void ClientManagerForm::receiveClientKey(int key)   //키값에 해당하는 리스트 행 시그널.
{
    ClientItem* c = clientList[key];

    int id = c->id();
    QString name = c->getName();
    QString number = c->getPhoneNumber();
    QString address = c->getAddress();
    ClientItem* item = new ClientItem(id, name, number, address);

    emit clickClientSent(item);
}

void ClientManagerForm::on_clearbutton_clicked()
{
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->phoneNumberLineEdit->clear();
    ui->addressLineEdit->clear();
    ui->searchLineEdit->clear();
}


void ClientManagerForm::on_ClientManagement_clicked()
{
    ui->label->setText("고객정보관리");
    for (const auto& v : clientList) {
        ClientItem* c = v;
        c->setHidden(false);
    }
}

