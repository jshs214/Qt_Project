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
    removeAction->setIcon(QIcon(":/images/eraser.png"));
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

    ui->clearButton->setIcon(QIcon(":/images/eraser.png"));
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
    for (const auto& v : qAsConst(clientList)) {
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

/* 고객정보추가를 위한 슬롯 */
void ClientManagerForm::on_addPushButton_clicked()
{
    /* 검색 결과에서 정보 추가 시 경고메시지*/
    if(ui->clientInfoLabel->text() != tr("ClientInfoManager"))
    {
        QMessageBox::warning(this, tr("Error"),
                             QString(tr("This is a search Info.\nGo to ClientInfoManager.")));
        return;
    }
    QString name, number, address;
    int id = makeId( );
    name = ui->nameLineEdit->text();
    number = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();

    /* 고객의 데이터를 다 입력하면 고객 정보추가 */
    if(name.length() && number.length() && address.length()) {
        ClientItem* c = new ClientItem(id, name, number, address);
        clientList.insert(id, c);
        ui->treeWidget->addTopLevelItem(c);

        ui->nameLineEdit->clear();
        ui->phoneNumberLineEdit->clear();
        ui->addressLineEdit->clear();
        /* 채팅서버에서 등록된 고객을 알기 위해 id, 이름을 시그널로 보냄 */
        emit addClient(id, name);
    }
}

/* 고객정보변경을 위한 슬롯 */
void ClientManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    /* 변경할 고객의 데이터를 입력한 데이터로 정보 수정 */
    if(item != nullptr) {
        int key = item->text(0).toInt();    //id 값을 가져와
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

/* 고객정보검색을 위한 슬롯 */
void ClientManagerForm::on_searchPushButton_clicked()
{
    ui->clientInfoLabel->setText(tr("Serach Info"));

    /* 모든 고객 데이터 hidden */
    for (const auto& v : qAsConst(clientList)) {
        ClientItem* c = v;
        c->setHidden(true);
    }

    int i = ui->searchComboBox->currentIndex(); //무엇으로 검색할지 콤보박스의 인덱스를 가져옴
    {   /* 검색과 일치하거나 포함하는 문자열이 있으면 hidden(false) */
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), Qt::MatchContains, i);
        foreach(auto i, items) {
            i->setHidden(false);    //검색된 리스트만 출력되게
        }
    }
}

/* 검색결과 창에서 고객정보관리로 돌아오는 슬롯 */
void ClientManagerForm::on_statePushButton_clicked()
{
    ui->clientInfoLabel->setText(tr("ClientInfoManager"));
    for (const auto& v : qAsConst(clientList)) {
        ClientItem* c = v;
        c->setHidden(false);
    }
}

/* ContextMenu 슬롯 */
void ClientManagerForm::showContextMenu(const QPoint &pos)
{
    if(ui->treeWidget->currentItem() == nullptr)    return;
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

/* 고객정보의 데이터(트리위젯)의 리스트 제거 슬롯 */
void ClientManagerForm::removeItem()
{
    /* 선택된 정보의 리스트를 트리위젯에서 제거 */
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {   // 에외처리
        clientList.remove(item->text(0).toInt());
        /* 채팅서버에서 삭제된 고객을 알기 위해 id를 시그널로 보냄 */
        emit remClient(item->text(0).toInt());
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
        ui->treeWidget->update();
    }
}

/* 등록된 고객정보 클릭 시 관련정보 출력 슬롯*/
void ClientManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->nameLineEdit->setText(item->text(1));
    ui->phoneNumberLineEdit->setText(item->text(2));
    ui->addressLineEdit->setText(item->text(3));
}

/* Order에서 고객 id나 이름을 받아오는 슬롯*/
void ClientManagerForm::receiveClientName(QString str)
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

    auto items = ui->treeWidget->findItems(str, flag,1);     //이름이므로 1
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
        /* id나 이름에 해당하는 데이터를 보내주는 시그널*/
        emit clientDataSent(c);
    }
}

/* 고객 id 값을 받아오는 슬롯 */
void ClientManagerForm::receiveClientKey(int key)
{
    ClientItem* c = clientList[key];

    int id = c->id();
    QString name = c->getName();
    QString number = c->getPhoneNumber();
    QString address = c->getAddress();
    ClientItem* item = new ClientItem(id, name, number, address);
    /* id에 해당하는 데이터를 보내주는 시그널*/
    emit clickClientSent(item);
}

/* 버튼 클릭 시 입력 값 초기화 하는 슬롯 */
void ClientManagerForm::on_clearButton_clicked()
{
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->phoneNumberLineEdit->clear();
    ui->addressLineEdit->clear();
    ui->searchLineEdit->clear();
}
