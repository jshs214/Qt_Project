 #include "chatserverform.h"
#include "ui_chatserverform.h"

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

ChatServerForm::ChatServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatServerForm)
{
    ui->setupUi(this);

    ui->clientTreeWidget->QTreeView::setColumnWidth(0,30);
    ui->clientTreeWidget->QTreeView::setColumnWidth(1,60);
    ui->clientTreeWidget->QTreeView::setColumnWidth(2,60);
    ui->clientTreeWidget->QTreeView::setColumnWidth(3,90);


    QList<int> sizes;
    sizes << 300 << 500;
    ui->splitter->setSizes(sizes);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection( )), SLOT(clientConnect( )));
    if (!tcpServer->listen(QHostAddress::Any, 8000)) {
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(tcpServer->errorString( )));
        close( );
        return;
    }

    QAction* inviteAction = new QAction(tr("&Invite"));
    inviteAction->setObjectName("Invite");
    connect(inviteAction, SIGNAL(triggered()), SLOT(inviteClient()));

    QAction* removeAction = new QAction(tr("&Kick out"));
    connect(removeAction, SIGNAL(triggered()), SLOT(kickOut()));

    menu = new QMenu;
    menu->addAction(inviteAction);
    menu->addAction(removeAction);
    ui->clientTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    qDebug() << tr("The server is running on port %1.").arg(tcpServer->serverPort( ));
    ui->stateLineedit->setText(tr("The server is running on port %1.").arg(tcpServer->serverPort()));
}

ChatServerForm::~ChatServerForm()
{
    delete ui;

    tcpServer->close( );
}

void ChatServerForm::clientConnect( )
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection( );
    connect(clientConnection, SIGNAL(readyRead( )), SLOT(receiveData( )));
    connect(clientConnection, SIGNAL(disconnected( )), SLOT(removeClient()));
    qDebug("new connection is established...");
}

void ChatServerForm::receiveData( )
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    QByteArray bytearray = clientConnection->read(BLOCK_SIZE);

    chatProtocolType data;
    QDataStream in(&bytearray, QIODevice::ReadOnly);
    in >> data.type;
    in.readRawData(data.data, 1020);

    QString ip = clientConnection->peerAddress().toString();
    QString name = QString::fromStdString(data.data);

    QString port = QString::number(clientConnection->peerPort());
    qDebug()<<ip<<name<<port;

    ui->ipLineEdit->setText(ip);

    switch(data.type) {
    case Chat_Login:

        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(0) != "  ") {
                item->setText(0, "  ");
                item->setIcon(0, QIcon(":/images/grennlight.png"));

                clientList.append(clientConnection);        // QList<QTcpSocket*> clientList;
                clientNameHash[ip] = name;

                // // // // // // //
                QTreeWidgetItem* chatItem = new QTreeWidgetItem(ui->chattingTreeWidget);
                chatItem->setText(1,clientNameHash[ip]);
                chatItem->setIcon(0, QIcon(":/images/grennlight.png"));
                //
            }

        }

        break;

    case Chat_In:

        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(0) != "  ") {
                item->setText(0, "  ");
                item->setIcon(0, QIcon(":/images/grennlight.png"));

                //
                QTreeWidgetItem* chatItem = new QTreeWidgetItem(ui->chattingTreeWidget);
                chatItem->setText(1,clientNameHash[ip]);
                chatItem->setIcon(0, QIcon(":/images/grennlight.png"));
            }
        }

        break;

    case Chat_Talk: {   //채팅 할 때,
        foreach(QTcpSocket *sock, clientList) {
            if(sock != clientConnection) {
                QByteArray data("<font color=red>");
                data.append(name.toStdString().data());
                data.append("</font> : ");
                data.append(bytearray);
                sock->write(data);
            }
        }

        if(clientNameHash[ip] == nullptr)   return; //

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, clientConnection->peerAddress().toString());
        item->setText(1, QString::number(clientConnection->peerPort()));
        item->setText(2, QString::number(clientIDHash[clientNameHash[ip]]));
        item->setText(3, clientNameHash[ip]);
        item->setText(4, QString(data.data));
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, QString(data.data));


        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        ui->messageTreeWidget->addTopLevelItem(item);
    }
        break;

    case Chat_Close:

        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) == "  ") {
                item->setText(0, " ");
                item->setIcon(0, QIcon(":/images/redlight.png"));
            }
        }
        //
        foreach(auto item, ui->chattingTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            ui->chattingTreeWidget->takeTopLevelItem(ui->chattingTreeWidget->indexOfTopLevelItem(item));
        }

        break;

    case Chat_LogOut:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) == "  ") {
                item->setText(0, " ");
                item->setIcon(0, QIcon(":/images/redlight.png"));
                clientList.removeOne(clientConnection);        // QList<QTcpSocket*> clientList;
            }
        }
        //ui->inviteComboBox->addItem(name);
        foreach(auto item, ui->chattingTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            ui->chattingTreeWidget->takeTopLevelItem(ui->chattingTreeWidget->indexOfTopLevelItem(item));
        }

        break;

    default:    break;
    }
    //    qDebug() << bytearray;
}

void ChatServerForm::removeClient()
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    clientList.removeOne(clientConnection);
    clientConnection->deleteLater();

    QString name = clientNameHash[clientConnection->peerAddress().toString()];
    foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
        item->setText(0, " ");
        item->setIcon(0, QIcon(":/images/redlight.png"));
    }

    //
    foreach(auto item, ui->chattingTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
        ui->chattingTreeWidget->takeTopLevelItem(ui->chattingTreeWidget->indexOfTopLevelItem(item));
    }

}

void ChatServerForm::addClient(int id, QString name, QString number, QString address)
{
    clientIDList << id;
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->clientTreeWidget);
    item->setText(0, " ");
    flag = false;
    item->setIcon(0, QIcon(":/images/redlight.png"));
    item->setText(1, name);
    item->setText(2, QString::number(id));
    item->setText(3, number);
    item->setText(4, address);

    ui->clientTreeWidget->addTopLevelItem(item);
    clientIDHash[name] = id;
    ui->clientTreeWidget->resizeColumnToContents(0);
}

void ChatServerForm::on_clientTreeWidget_customContextMenuRequested(const QPoint &pos)
{
    foreach(QAction *action, menu->actions()) {
        if(action->objectName() == "Invite")
            action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) != "  ");
        else
            action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) == "  ");
    }
    QPoint globalPos = ui->clientTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ChatServerForm::kickOut()
{
    QString name = ui->clientTreeWidget->currentItem()->text(1);
    QString ip = clientNameHash.key(name);

    chatProtocolType data;
    data.type = Chat_KickOut;
    qstrcpy(data.data, "");
    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << data.type;
    out.writeRawData(data.data, 1020);

    foreach(QTcpSocket* sock, clientList) {
        if(sock->peerAddress().toString() == ip){
            //sock->disconnectFromHost();
            sock->write(sendArray);
        }
    }
    //QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
    ui->clientTreeWidget->currentItem()->setText(0, " ");
    ui->clientTreeWidget->currentItem()->setIcon(0, QIcon(":/images/redlight.png"));


    foreach(auto item, ui->chattingTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
        ui->chattingTreeWidget->takeTopLevelItem(ui->chattingTreeWidget->indexOfTopLevelItem(item));
    }


    //clientIDList.append(clientIDHash[name]);
    //    ui->inviteComboBox->addItem(name);

}

void ChatServerForm::inviteClient()
{
    if(ui->clientTreeWidget->topLevelItemCount()) {
        QString name = ui->clientTreeWidget->currentItem()->text(1);
        QString ip = clientNameHash.key(name, "");

        chatProtocolType data;
        data.type = Chat_Invite;
        qstrcpy(data.data, "");
        QByteArray sendArray;
        QDataStream out(&sendArray, QIODevice::WriteOnly);
        out << data.type;
        out.writeRawData(data.data, 1020);

        foreach(QTcpSocket* sock, clientList) {
            if(sock->peerAddress().toString() == ip){
                sock->write(sendArray);
                //                clientList.append(sock);        // QList<QTcpSocket*> clientList;
                foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
                    if(item->text(1) != "  ") {
                        item->setText(0, "  ");
                        item->setIcon(0, QIcon(":/images/grennlight.png"));
                        clientList.append(sock);        // QList<QTcpSocket*> clientList;
                        // clientNameHash[ip] = name;

                        QTreeWidgetItem* chatItem = new QTreeWidgetItem(ui->chattingTreeWidget);
                        chatItem->setText(1,clientNameHash[ip]);
                        chatItem->setIcon(0, QIcon(":/images/grennlight.png"));
                    }
                }
            }
        }
    }
}
