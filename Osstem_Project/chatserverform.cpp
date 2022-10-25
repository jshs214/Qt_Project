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

    ui->chattingTreeWidget->QTreeView::setColumnWidth(0, 70);
    ui->chattingTreeWidget->QTreeView::setColumnWidth(1, 100);

    ui->clientTreeWidget->QTreeView::setColumnWidth(0, 70);
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

    connect(ui->inputLineEdit, SIGNAL(returnPressed( )), SLOT(on_sendButton_clicked( )));
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
    QString receiveData = QString::fromStdString(data);

    ui->ipLineEdit->setText(clientConnection->localAddress().toString());

    switch(type) {
    case Chat_Login:
    {
        auto parts = receiveData.split(u',');

        QString name = QString(parts[0]);
        QString id = QString(parts[1]);

        foreach(auto item, ui->clientTreeWidget->findItems(id, Qt::MatchFixedString, 2)) {
            if(item->text(1) == name){
                if(item->text(0) != "On") {
                    item->setText(0, "On");
                    clientSocketHash[id] = clientConnection;
                    clientNameHash[port] = name;
                    clientPortIDHash[port]=id;
                    item->setIcon(0, QIcon(":/images/yellowlight.png"));
                    sendLogInOut(clientConnection, "true");
                }
                return;
            }
        }
        sendLogInOut(clientConnection, "false");

        break;
    }

    case Chat_In:
    {
        auto parts = receiveData.split(u',');

        QString name = QString(parts[0]);
        QString id = QString(parts[1]);

        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(2) == id){
                if(item->text(0) != "Chat") {
                    item->setText(0, "Chat");
                    item->setIcon(0, QIcon(":/images/greenlight.png"));
                    QTreeWidgetItem* chatItem = new QTreeWidgetItem(ui->chattingTreeWidget);
                    chatItem->setText(1,clientNameHash[port]);
                    chatItem->setIcon(0, QIcon(":/images/greenlight.png"));
                    chatItem->setText(2, item->text(2));


                }
            }
        }
        /* Chat_List로 현재 채팅방 참여인원 전달 */
        sendChatList();
        break;
    }
    case Chat_Talk: {
        qDebug("Server ChatTalk On");
        foreach(QTcpSocket *sock, clientSocketHash.values()) {
            if(clientPortIDHash.contains(sock->peerPort()) && sock != clientConnection) { //포트가 있고, 내꺼가 아니면
                foreach(auto item, ui->clientTreeWidget->findItems(clientPortIDHash[sock->peerPort()], Qt::MatchFixedString, 2)) {
                    if(item->text(0) =="Chat"){
                        QByteArray sendArray;
                        sendArray.clear();
                        QDataStream out(&sendArray, QIODevice::WriteOnly);
                        out << Chat_Talk;
                        sendArray.append("<font color=lightsteelblue>");
                        sendArray.append(clientNameHash[port].toStdString().data());
                        sendArray.append("("+clientPortIDHash[port].toStdString()+")");
                        sendArray.append("</font> : ");
                        sendArray.append(receiveData.toStdString().data());
                        sock->write(sendArray);
                    }

                }
            }
        }
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(port));
        item->setText(2, clientPortIDHash[port]);
        item->setText(3, clientNameHash[port]);                                 //name
        item->setText(4, QString(data));
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, QString(data));
        ui->messageTreeWidget->addTopLevelItem(item);

        ui->message->append("<font color=lightsteelblue>" + clientNameHash[port] + "(" + clientPortIDHash[port] + ")"
                            + "</font> : " + receiveData);

        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        logThread->appendData(item);
    }
        break;

    case Chat_Out:
    {
        auto parts = receiveData.split(u',');

        QString name = QString(parts[0]);
        QString id = QString(parts[1]);
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(2) == id){
                if(item->text(0) != "On") {
                    item->setText(0, "On");
                    item->setIcon(0, QIcon(":/images/yellowlight.png"));
                }
            }
        }
        // 접속중인 트리위젯의 데이터 제거
        foreach(auto item, ui->chattingTreeWidget->findItems(id, Qt::MatchFixedString, 2)) {
            ui->chattingTreeWidget->takeTopLevelItem(ui->chattingTreeWidget->indexOfTopLevelItem(item));
        }

        /* Chat_List로 현재 채팅방 참여인원 전달 */
        sendChatList();

        break;
    }
    case Chat_LogOut:
    {
        QString id = clientPortIDHash[port];
        //qDebug()<<id;
        foreach(auto item, ui->clientTreeWidget->findItems(receiveData, Qt::MatchFixedString, 1)) {
            if(item->text(2) == id){
                if(item->text(0) != "Off") {
                    item->setText(0, "Off");
                    item->setIcon(0, QIcon(":/images/redlight.png"));
                }
            }
            clientSocketHash.remove(id);
            clientNameHash.remove(port);
            clientPortIDHash.remove(port);
        }

        foreach(auto item, ui->chattingTreeWidget->findItems(id, Qt::MatchFixedString, 2)) {
            ui->chattingTreeWidget->takeTopLevelItem(ui->chattingTreeWidget->indexOfTopLevelItem(item));
        }
        sendChatList();
        break;
    }
    default:
        break;
    }
}

void ChatServerForm::removeClient()
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    if(clientConnection != nullptr){
        QString id =  clientPortIDHash[clientConnection->peerPort()];
        foreach(auto item, ui->clientTreeWidget->findItems(id, Qt::MatchFixedString, 2)) {
            item->setText(0, "Off");
            item->setIcon(0, QIcon(":/images/redlight.png"));
        }
        clientSocketHash.remove(id);
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

}

void ChatServerForm::remClient(int id)    //고객관리창에서 데이터 삭제 시 활동 중리스트 삭제
{
    foreach(auto item, ui->clientTreeWidget->findItems(QString::number(id), Qt::MatchFixedString, 2)) {
        ui->clientTreeWidget->takeTopLevelItem(ui->clientTreeWidget->indexOfTopLevelItem(item));
    }
}

void ChatServerForm::on_clientTreeWidget_customContextMenuRequested(const QPoint &pos)
{
    if(ui->clientTreeWidget->currentItem() == nullptr)  return; //예외처리
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

    //QString name = ui->clientTreeWidget->currentItem()->text(1);
    QString id = ui->clientTreeWidget->currentItem()->text(2);
    QTcpSocket* sock = clientSocketHash[id];
    sock->write(sendArray);

    ui->clientTreeWidget->currentItem()->setText(0, "On");
    ui->clientTreeWidget->currentItem()->setIcon(0, QIcon(":/images/yellowlight.png"));

    foreach(auto item, ui->chattingTreeWidget->findItems(id, Qt::MatchFixedString, 2)) {
        ui->chattingTreeWidget->takeTopLevelItem(ui->chattingTreeWidget->indexOfTopLevelItem(item));
    }

}

void ChatServerForm::sendLogInOut(QTcpSocket* sock , const char* data)
{
    QByteArray dataArray;           // 소켓으로 보낼 데이터를 채우고
    QDataStream out(&dataArray, QIODevice::WriteOnly);
    out << Chat_Login;
    out.writeRawData(data, 1020);
    sock->write(dataArray);
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
    QString id = ui->clientTreeWidget->currentItem()->text(2);

    QTcpSocket* sock = clientSocketHash[id];
    sock->write(sendArray);

    ui->clientTreeWidget->currentItem()->setText(0, "Chat");
    ui->clientTreeWidget->currentItem()->setIcon(0, QIcon(":/images/greenlight.png"));
    QTreeWidgetItem* chatItem = new QTreeWidgetItem(ui->chattingTreeWidget);
    chatItem->setText(1,name);
    chatItem->setIcon(0, QIcon(":/images/greenlight.png"));
    chatItem->setText(2,id);

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
    QString filename, name, id;

    if (byteReceived == 0) {        // 파일 전송 시작 : 파일에 대한 정보를 이용해서 QFile 객체 생성
        progressDialog->reset();
        progressDialog->show();

        QString ip = receivedSocket->peerAddress().toString();
        quint16 port = receivedSocket->peerPort();

        //qDebug() << ip << " : " << port;

        QDataStream in(receivedSocket);
        in >> totalSize >> byteReceived >> filename >> name >> id;
        progressDialog->setMaximum(totalSize);

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(port));
        item->setText(2,  id);
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



void ChatServerForm::on_sendButton_clicked()
{
    QString str = ui->inputLineEdit->text( );
    if(str.length( )) {
        ui->message->append("<font color=red>Manager</font> : " + str);
        foreach(QTcpSocket *sock, clientSocketHash.values()) {
            foreach(auto item, ui->clientTreeWidget->findItems(clientPortIDHash[sock->peerPort()], Qt::MatchFixedString, 2)) {
                if(item->text(0) =="Chat"){

                    QByteArray sendArray;
                    sendArray.clear();
                    QDataStream out(&sendArray, QIODevice::WriteOnly);
                    out << Chat_Talk;
                    sendArray.append("<font color=red>");
                    sendArray.append("Manager");
                    sendArray.append("</font> : ");
                    sendArray.append(str.toStdString().data());
                    sock->write(sendArray);
                    //qDebug() << sock->peerPort();
                }
            }
        }
    }

    QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
    item->setText(0, chatServer->serverAddress().toString());
    item->setText(1, QString::number(chatServer->serverPort()));
    item->setText(2, "Manager");
    item->setText(3, "Manager");
    item->setText(4, str);
    item->setText(5, QDateTime::currentDateTime().toString());
    item->setToolTip(4, str);
    ui->messageTreeWidget->addTopLevelItem(item);

    for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
        ui->messageTreeWidget->resizeColumnToContents(i);

    logThread->appendData(item);

    ui->inputLineEdit->clear();
}
void ChatServerForm::sendChatList()
{
    QByteArray dataArray;           // 소켓으로 보낼 데이터를 채우고
    QDataStream out(&dataArray, QIODevice::WriteOnly);
    out << Chat_List;

    foreach(auto item, ui->clientTreeWidget->findItems("Chat", Qt::MatchFixedString, 0)) {
        QString name = item->text(1);
        QString id = item->text(2);
        dataArray.append(name.toStdString()+"("+id.toStdString()+")");
        dataArray.append(",");

    }
    foreach(QTcpSocket *sock, clientSocketHash.values()) {
        foreach(auto item, ui->clientTreeWidget->findItems(clientPortIDHash[sock->peerPort()], Qt::MatchFixedString, 2)) {
            Q_UNUSED(item);
                sock->write(dataArray);

        }
    }
}



