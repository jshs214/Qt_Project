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

    /* ContextMenu의 remove 액션, 리스트의 데이터 삭제 */
    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));
    menu = new QMenu;
    menu->addAction(removeAction);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));

    /* 전화번호 입력 시 00(0)-000(0)-000(0)만 입력 받을 수 있도록 */
    QRegularExpressionValidator* regExpValidator = new QRegularExpressionValidator(this);
    regExpValidator->setRegularExpression(QRegularExpression("^\\d{2,3}-\\d{3,4}-\\d{4}$"));
    ui->phoneNumberLineEdit->setValidator(regExpValidator);

}
/* 파일의 데이터 입력하는 메서드 */
void ClientManagerForm::loadData()
{
    QFile file("clientlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    /* 파일의 데이터를 ','로 파싱해서 입력 */
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            ClientItem* c = new ClientItem(id, row[1], row[2], row[3]);
            ui->treeWidget->addTopLevelItem(c);
            clientList.insert(id, c);

            /* 채팅서버에서 등록된 고객을 알기 위해 id, 이름을 시그널로 보냄 */
            emit addClient(id, c->getName());
        }
    }
    file.close( );
}

/* 소멸자에서 파일 출력 */
ClientManagerForm::~ClientManagerForm()
{
    delete ui;

    QFile file("clientlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    /* 파일의 데이터를 ','로 파싱해서 저장 */
    QTextStream out(&file);
    for (const auto& v : clientList) {
        ClientItem* c = v;
        out << c->id() << ", " << c->getName() << ", ";
        out << c->getPhoneNumber() << ", ";
        out << c->getAddress() << "\n";
    }
    file.close( );
}

/* ID(키 값) 생성 메서드*/
int ClientManagerForm::makeId( )
{
    if(clientList.size( ) == 0) {    // ID가 중복되면 +1
        return 1000;
    } else {
        auto id = clientList.lastKey();
        return ++id;
    }
}

/* 고객정보의 데이터(트리위젯)의 리스트 제거 슬롯 */
void ClientManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {   // 에외처리
        clientList.remove(item->text(0).toInt());
        emit remClient(item->text(0).toInt());  /* 채팅서버에서 삭제된 고객을 알기 위해 id를 시그널로 보냄 */
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
        ui->treeWidget->update();
    }
}

void ClientManagerForm::showContextMenu(const QPoint &pos)
{
    if(ui->treeWidget->currentItem() == nullptr)    return;
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ClientManagerForm::on_searchPushButton_clicked()
{
    ui->clientInfoLabel->setText("Serach Info");

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
    if(ui->clientInfoLabel->text() != "ClientInfoManager")
    {
        QMessageBox::warning(this, "Error",
                             QString("This is a search Info.\nGo to ClientInfoManager."));
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
        emit addClient(id, name);
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

void ClientManagerForm::receiveClientName(QString str)  //Order에서 id나 이름을 받아 emit
{
    QMap<int,ClientItem*> searchList;

    auto flag =  Qt::MatchCaseSensitive|Qt::MatchContains;

    auto id = ui->treeWidget->findItems(str, flag,0);        //키값비교, 0
    foreach(auto i, id) {
        ClientItem* c = static_cast<ClientItem*>(i);
        int id = c->id();
        QString name = c->getName();
        QString number = c->getPhoneNumber();
        QString address = c->getAddress();
        ClientItem* item = new ClientItem(id, name, number, address);
        searchList.insert(c->id(), item);
    }

    auto items = ui->treeWidget->findItems(str, flag,1);        //이름이므로 1
    foreach(auto i, items) {
        ClientItem* c = static_cast<ClientItem*>(i);
        int id = c->id();
        QString name = c->getName();
        QString number = c->getPhoneNumber();
        QString address = c->getAddress();
        ClientItem* item = new ClientItem(id, name, number, address);
        searchList.insert(c->id(), item);
    }

    for(const auto&v : searchList){
        ClientItem* c = v;
        emit clientDataSent(c);
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

void ClientManagerForm::on_ClientManagement_clicked()
{
    ui->clientInfoLabel->setText("ClientInfoManager");
    for (const auto& v : clientList) {
        ClientItem* c = v;
        c->setHidden(false);
    }
}

void ClientManagerForm::on_clearButton_clicked()
{
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->phoneNumberLineEdit->clear();
    ui->addressLineEdit->clear();
    ui->searchLineEdit->clear();
}

