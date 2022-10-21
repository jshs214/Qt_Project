#include "chatserverform.h"
#include "ui_chatserverform.h"
#include "logthread.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QDebug>
#include <QMenu>
#include <QFile>
#include <QFileInfo>
#include <QProgressDialog>

ChatServerForm::ChatServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatServerForm), totalSize(0), byteReceived(0)
{
    ui->setupUi(this);
    QList<int> sizes;
    sizes << 200 << 500;
    ui->splitter->setSizes(sizes);

    ui->clientTreeWidget->QTreeView::setColumnWidth(0, 100);
    ui->clientTreeWidget->QTreeView::setColumnWidth(1, 100);

    chatServer = new QTcpServer(this);
    connect(chatServer, SIGNAL(newConnection( )), SLOT(clientConnect( )));
    if (!chatServer->listen(QHostAddress::Any, PORT_NUMBER)) {
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(chatServer->errorString( )));
        close( );
        return;
    }

    fileServer = new QTcpServer(this);
    connect(fileServer, SIGNAL(newConnection()), SLOT(acceptConnection()));
    if (!fileServer->listen(QHostAddress::Any, PORT_NUMBER+1)) {
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(fileServer->errorString( )));
        close( );
        return;
    }

    qDebug("Start listening ...");

    QAction* inviteAction = new QAction(tr("&Invite"));
    inviteAction->setObjectName("Invite");
    connect(inviteAction, SIGNAL(triggered()), SLOT(inviteClient()));

    QAction* removeAction = new QAction(tr("&Kick out"));
    connect(removeAction, SIGNAL(triggered()), SLOT(kickOut()));

    menu = new QMenu;
    menu->addAction(inviteAction);
    menu->addAction(removeAction);
    ui->clientTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    progressDialog = new QProgressDialog(0);
    progressDialog->setAutoClose(true);
    progressDialog->reset();

    logThread = new LogThread(this);
    logThread->start();

    connect(ui->saveButton, SIGNAL(clicked()), logThread, SLOT(saveData()));

    qDebug() << tr("The server is running on port %1.").arg(chatServer->serverPort( ));
    ui->stateLineedit->setText(tr("The server is running on port %1.").arg(chatServer->serverPort()));
}

ChatServerForm::~ChatServerForm()
{
    delete ui;

    logThread->terminate();
    chatServer->close( );
    fileServer->close( );
}

void ChatServerForm::clientConnect( )
{
    QTcpSocket *clientConnection = chatServer->nextPendingConnection( );
    connect(clientConnection, SIGNAL(readyRead( )), SLOT(receiveData( )));
    connect(clientConnection, SIGNAL(disconnected( )), SLOT(removeClient()));
    qDebug("new connection is established...");
}

void ChatServerForm::receiveData( )
{    
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    QByteArray bytearray = clientConnection->read(BLOCK_SIZE);

    Chat_Status type;       // 채팅의 목적
    char data[1020];        // 전송되는 메시지/데이터
    memset(data, 0, 1020);

    QDataStream in(&bytearray, QIODevice::ReadOnly);
    in.device()->seek(0);
    in >> type;
    in.readRawData(data, 1020);

    QString ip = clientConnection->peerAddress().toString();
    quint16 port = clientConnection->peerPort();
    QString name = QString::fromStdString(data);

    ui->ipLineEdit->setText(ip);

    qDebug() << ip << " : " << type;

    switch(type) {
    case Chat_Login:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(0) != "On") {
                item->setText(0, "On");
                clientSocketHash[name] = clientConnection;
                item->setIcon(0, QIcon(":/images/yellowlight.png"));
                return;
            }
        }
        clientConnection->disconnectFromHost(); //고객리스트에 없는 이름이면 연결 해제
        break;

    case Chat_In:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(0) != "Chat") {
                item->setText(0, "Chat");
                item->setIcon(0, QIcon(":/images/greenlight.png"));
            }
            clientNameHash[port] = name;
            // 이미 chat in 이면 중복되지않게 생성 x
            foreach(auto citem, ui->chattingTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
                Q_UNUSED(citem);
                return;
            }
            QTreeWidgetItem* chatItem = new QTreeWidgetItem(ui->chattingTreeWidget);
            chatItem->setText(1,clientNameHash[port]);
            chatItem->setIcon(0, QIcon(":/images/greenlight.png"));
        }
        break;

    case Chat_Talk: {
        foreach(QTcpSocket *sock, clientSocketHash.values()) {
            if(clientNameHash.contains(sock->peerPort()) && sock != clientConnection) {
                QByteArray sendArray;
                sendArray.clear();
                QDataStream out(&sendArray, QIODevice::WriteOnly);
                out << Chat_Talk;
                sendArray.append("<font color=lightsteelblue>");
                sendArray.append(clientNameHash[port].toStdString().data());
                sendArray.append("</font> : ");
                sendArray.append(name.toStdString().data());
                sock->write(sendArray);
                qDebug() << sock->peerPort();
            }
        }

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(port));
        item->setText(2, QString::number(clientIDHash[clientNameHash[port]]));
        item->setText(3, clientNameHash[port]);
        item->setText(4, QString(data));
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, QString(data));
        ui->messageTreeWidget->addTopLevelItem(item);

        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        logThread->appendData(item);
    }
        break;

    case Chat_Out:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) != "On") {
                item->setText(0, "On");
            }
            clientNameHash.remove(port);
        }
        //
        foreach(auto item, ui->chattingTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            ui->chattingTreeWidget->takeTopLevelItem(ui->chattingTreeWidget->indexOfTopLevelItem(item));
        }
        break;
    case Chat_LogOut:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) != "Off") {
                item->setText(0, "Off");
                item->setIcon(0, QIcon(":/images/redlight.png"));
            }
            clientSocketHash.remove(name);
        }
        foreach(auto item, ui->chattingTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            ui->chattingTreeWidget->takeTopLevelItem(ui->chattingTreeWidget->indexOfTopLevelItem(item));
        }
        break;

    default:
        break;
    }
}

void ChatServerForm::removeClient()
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    if(clientConnection != nullptr){
        QString name = clientNameHash[clientConnection->peerPort()];
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            item->setText(0, "Off");
            item->setIcon(0, QIcon(":/images/redlight.png"));
        }
        clientSocketHash.remove(name);
        clientConnection->deleteLater();
    }

}

void ChatServerForm::addClient(int id, QString name)    //고객관리창에서 데이터 추가 시 리스트 추가
{
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->clientTreeWidget);
    item->setText(0, "Off");
    item->setIcon(0, QIcon(":/images/redlight.png"));
    item->setText(1, name);
    item->setText(2, QString::number(id));

    ui->clientTreeWidget->addTopLevelItem(item);
    clientIDHash[name] = id;
    ui->clientTreeWidget->resizeColumnToContents(0);

}
void ChatServerForm::remClient(QString name)    //고객관리창에서 데이터 삭제 시 리스트 삭제
{
    foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
        ui->clientTreeWidget->takeTopLevelItem(ui->clientTreeWidget->indexOfTopLevelItem(item));
    }
}

void ChatServerForm::on_clientTreeWidget_customContextMenuRequested(const QPoint &pos)
{
    foreach(QAction *action, menu->actions()) {
        if(action->objectName() == "Invite")
            action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) == "On");
        else    // "Kick Out"
            action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) == "Chat");
    }
    QPoint globalPos = ui->clientTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}
/* 클라이언트 강퇴하기 */
void ChatServerForm::kickOut()
{

    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << Chat_KickOut;
    out.writeRawData("", 1020);

    QString name = ui->clientTreeWidget->currentItem()->text(1);
    QTcpSocket* sock = clientSocketHash[name];

    sock->write(sendArray);
    ui->clientTreeWidget->currentItem()->setText(0, "On");
    ui->clientTreeWidget->currentItem()->setIcon(0, QIcon(":/images/yellowlight.png"));

    foreach(auto item, ui->chattingTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
        ui->chattingTreeWidget->takeTopLevelItem(ui->chattingTreeWidget->indexOfTopLevelItem(item));
    }

}
/* 클라이언트 초대하기 */
void ChatServerForm::inviteClient()
{
    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << Chat_Invite;
    out.writeRawData("", 1020);

    /* 소켓은 현재 선택된 아이템에 표시된 이름과 해쉬로 부터 가져온다. */
    QString name = ui->clientTreeWidget->currentItem()->text(1);
    QTcpSocket* sock = clientSocketHash[name];
    sock->write(sendArray);

    ui->clientTreeWidget->currentItem()->setText(0, "Chat");
    ui->clientTreeWidget->currentItem()->setIcon(0, QIcon(":/images/greenlight.png"));
    QTreeWidgetItem* chatItem = new QTreeWidgetItem(ui->chattingTreeWidget);
    chatItem->setText(1,name);
    chatItem->setIcon(0, QIcon(":/images/greenlight.png"));
}

/* 파일 전송을 위한 소켓 생성 */
void ChatServerForm::acceptConnection()
{
    qDebug("Connected, preparing to receive files!");

    QTcpSocket* receivedSocket = fileServer->nextPendingConnection();
    connect(receivedSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
}

/* 파일 전송 */
void ChatServerForm::readClient()
{
    qDebug("Receiving file ...");
    QTcpSocket* receivedSocket = dynamic_cast<QTcpSocket *>(sender( ));
    QString filename, name;

    if (byteReceived == 0) {        // 파일 전송 시작 : 파일에 대한 정보를 이용해서 QFile 객체 생성
        progressDialog->reset();
        progressDialog->show();

        QString ip = receivedSocket->peerAddress().toString();
        quint16 port = receivedSocket->peerPort();
        qDebug() << ip << " : " << port;

        QDataStream in(receivedSocket);
        in >> totalSize >> byteReceived >> filename >> name;
        progressDialog->setMaximum(totalSize);

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(port));
        item->setText(2, QString::number(clientIDHash[name]));
        item->setText(3, name);
        item->setText(4, filename);
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, filename);

        /* 컨텐츠의 길이로 QTreeWidget의 헤더의 크기를 고정 */
        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        ui->messageTreeWidget->addTopLevelItem(item);
        logThread->appendData(item);

        QFileInfo info(filename);
        QString currentFileName = info.fileName();
        file = new QFile(currentFileName);
        file->open(QFile::WriteOnly);
    }
    else { // Officially read the file content
        inBlock = receivedSocket->readAll();

        byteReceived += inBlock.size();
        file->write(inBlock);
        file->flush();
    }

    progressDialog->setValue(byteReceived);

    if (byteReceived == totalSize) {
        qDebug() << QString("%1 receive completed").arg(filename);

        inBlock.clear();
        byteReceived = 0;
        totalSize = 0;
        progressDialog->reset();
        progressDialog->hide();
        file->close();
        delete file;
    }
}
